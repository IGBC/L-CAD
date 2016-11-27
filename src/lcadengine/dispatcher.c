/*
 * This file is part of the L-CAD project
 * Copyright (c) 2016  Ashley Brown, Katharina Sabel
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see http://www.gnu.org/licenses/.
 */

//Comment out the line below to disable threading.
//#define MULTITHREADING

#include "dispatcher.h"

#include <stdlib.h>
#include <string.h>

#include "logicSolver.h"

#ifdef MULTITHREADING
// TODO: fix threading
#endif

#define LOGMODULE "DISPATCHER"
#include "utils/lcadLogger.h"

#ifndef MAX_DELAY
    #define MAX_DELAY 100
#endif

#define GLI genericLogicInterface

/* Macro Generates the address of a thing for the stuff */
#define JPadr(ctx, offset, slot) ((((ctx->timestep + offset) % (MAX_DELAY + 1)) * ctx->n) + slot)
#define TIME(ctx, offset) ((ctx->timestep + offset) % (MAX_DELAY + 1))

struct {
    GLI *unit;
    size_t src;
    unsigned long timestep;
    dispatcher *ctx;
} typedef job;

struct {
    size_t ID;
    logicType newState;
} typedef diff;

struct s_dispatcher {
#ifdef MULTITHREADING
    // TODO: fix threading
#endif
    unsigned long timestep;
	size_t n;
    graph *LG;
    // Array containing all jobs for all upcoming timesteps.
    job *jobpool;
    // Array containing number of used slots in each given timestep.
    size_t *jobpoolCount; // size = (MAX_DELAY + 1)
    diff *diffBuffer;
    size_t diffBufferCount;

    //pool containing update locks.
    bool *lockPool;
};

void workerDoWork(job *j);
logicType solveSyncronous(job *j);
logicType solveRecursive(job *j);
void generateJob(dispatcher *ctx, GLI *unit, unsigned int offset, int src);
void setUnitState(dispatcher *ctx, GLI *unit, logicType state, size_t src);

dispatcher *dispatcherCreate(graph *logicGraph, int threads) {
    dispatcher* ctx = (dispatcher*) malloc(sizeof(dispatcher));

    // Fill in details;
    ctx->LG = logicGraph;

    //TODO: Lock Graph for editing;

    ctx->timestep = 0;
    ctx->n = graphGetNodeCount(logicGraph);

#ifdef MULTITHREADING
    // TODO: fix threading

#else
    threads = 0;
    LOG(WARNING, "MULTITHREADING DISABLED IN ENGINE AT COMPILE TIME");
#endif


    // Make a big thing to store Jobs in. (n * MD grid)
    ctx->jobpool = (job*) malloc(ctx->n * (MAX_DELAY + 1) * sizeof(job));
    memset((void*)ctx->jobpool, 0, ctx->n * (MAX_DELAY + 1) * sizeof(job));

    // Make a list of jobs in each timestep.
    ctx->jobpoolCount = (unsigned long*) malloc((MAX_DELAY + 1) * sizeof(unsigned long));
    memset((void*)ctx->jobpoolCount, 0, (MAX_DELAY + 1) * sizeof(unsigned long));

    // Make a buffer to store the difference in the graph from a timeStep.
    ctx->diffBuffer = (diff*) malloc(ctx->n * sizeof(job));
    memset((void*)ctx->diffBuffer, 0, ctx->n * sizeof(job));
    ctx->diffBufferCount = 0;

    // Lock pool prevents creating duplicate jobs.
    ctx->lockPool = (bool*) malloc(ctx->n * (MAX_DELAY + 1) * sizeof(bool));
    memset((void*)ctx->lockPool, 0, ctx->n * (MAX_DELAY + 1) * sizeof(bool));

    bool* tagPos = ctx->lockPool;

    // set the tag to point at lock memory for each gate.
    fastlist* nodelist = graphGetGLIList(logicGraph);
    for (size_t i = 0; i < fastlistSize(nodelist); i++) {
    	genericLogicInterface *g = (genericLogicInterface*) fastlistGetIndex(nodelist, i);
    	g->lockTag = tagPos;
    	tagPos += (MAX_DELAY + 1);

    	//// HAKX  ////

    	// Hack init system, alternate gate states
    	//g->state = i % 2;

    	//// /HAKX ////

    }

    // Set up complete
    LOG(INFO1, "Created Dispatcher %i nodes, %i threads", ctx->n, threads);
    return ctx;
}

void dispatcherDelete(dispatcher *ctx) {
    // Free everything
	// Graph Should be in a safe state;
#ifdef MULTITHREADING
	// TODO: fix threading
#endif
    free(ctx->lockPool);
    free(ctx->jobpool);
    free(ctx->jobpoolCount);
    free(ctx->diffBuffer);
    free(ctx);
    LOG(INFO1, "Destroyed Dispatcher");
}

int dispatcherStep(dispatcher *ctx) {
    // Move context into the next step.
    ctx->timestep++;
    
    // Loopy Stuff
    size_t i;
    
    // Constanty stuff
    unsigned long time = ctx->timestep % (MAX_DELAY + 1);

	LOG(INFO1, "T:%i Stepping Dispatcher. Jobs: %i, Time: %i", ctx->timestep, ctx->jobpoolCount[time], time);
	
    // Adds each job to the threadpool's queue for execution.
    for (i = 0; i < ctx->jobpoolCount[time]; i++) {
        job *j = &ctx->jobpool[JPadr(ctx, 0, i)];
#ifdef MULTITHREADING
        // TODO: fix threading
    }
#else
        // No threading, have to do the work manually :(
    	workerDoWork(j);
	}
#endif

    // here the diff buffer is populated. 
    
    // apply the diff patches to the graph.
    for (i = 0; i < ctx->diffBufferCount; i++) {
        diff *d = &ctx->diffBuffer[i];
        GLI *g = graphGetGLI(ctx->LG, d->ID);
        g->state = d->newState;
    }

    // In both of these memset commands only the used memory is cleared, 
    // so as to not to waste time clearing blank memory. 
    
    // Clear the Job pool for this step;
    // memset((void*)ctx->jobpool[JPadr(ctx, 0, 0)], 0, ctx->jobpoolCount[time] * sizeof(job));
    ctx->jobpoolCount[time] = 0;
    
    // Clear the diffBuffer now that the patches are applied.
    memset(ctx->diffBuffer, 0, ctx->diffBufferCount * sizeof(diff));
    ctx->diffBufferCount = 0;

    //clear lockPool
    memset(&ctx->lockPool[JPadr(ctx, 0, 0)], 0, ctx->n * sizeof(bool));

    return 0;
}

int dispatcherAddJob(dispatcher *ctx, size_t ID, unsigned int delay) {
    if (delay == 0) return -1;
    if (delay > MAX_DELAY) return -2;
    GLI *gli = graphGetGLI(ctx->LG, ID); 
    generateJob(ctx, gli, delay, -1);
    return 0;
};

void workerDoWork(job *j) {
	logicType val;
	// update syncronously or async depending on if we know the value or not.
	if (logic_isUnknown(j->unit)){
		val = solveRecursive(j);
	} else {
		val = solveSyncronous(j);
	}

    LOG(TRACE, "T:%i U:%i UPDATE: oldstate=%i, newstate=%i", j->ctx->timestep, j->unit->ID, j->unit->state, val);

	// Update gate
    setUnitState(j->ctx, j->unit, val, j->src);

    //clear some lock thing???
    j->unit->lockTag[TIME(j->ctx, 0)] = false;

}

logicType solveSyncronous(job *j) {
	// Get Inputs;
    fastlist *inputs = graphGetConnectionsByDrn(j->ctx->LG, j->unit->ID);  
    size_t count = fastlistSize(inputs);
    size_t i;
    size_t sum = 0;
    for (i = 0; i < count; i++) {
        // get The source gate for the connection.
        connection *conn = (connection*) fastlistGetIndex(inputs, i);
        // add the gate to the input sum.
        sum += conn->srcEp->state;
    }
    
    // Return state;
    return solver_sumComparitor(j->unit, sum, count);
}

logicType solveRecursive(job *j) {
	LOG(TRACE, "Recursive Solve ID = %i", j->unit->ID);
	if (logic_isUnknown(j->unit)) {
		if (j->unit->seen) {
			// We're going in circles, solution is to assign it a value and work forwards.
			j->unit->state = false;
			return j->unit->state;
		}
		j->unit->seen = true;
		// Get Inputs;
		fastlist *inputs = graphGetConnectionsByDrn(j->ctx->LG, j->unit->ID);
		size_t count = fastlistSize(inputs);
		size_t i;
		size_t sum = 0;
		for (i = 0; i < count; i++) {
		    // get The source gate for the connection.
		    connection *conn = (connection*) fastlistGetIndex(inputs, i);
		    // add the gate to the input sum.
		    job nextJob = { conn->srcEp, j->unit->state, j->timestep, j->ctx };
		    sum += solveRecursive(&nextJob);
		}

		// set state;
		j->unit->state = solver_sumComparitor(j->unit, sum, count);

		// clear mutex;
		j->unit->seen = false;
	}
	// if the state is known the recursion collapses down.
	return j->unit->state;
}

void generateJob(dispatcher *ctx, GLI *unit, unsigned int offset, int src) {
    // If job is too far in the future throw it away.
	if (offset > MAX_DELAY) {
        LOG(ERROR, "T: %i - Job submitted with offset of %i; dropping", ctx->timestep, offset);
        LOG(CRITICAL, "Simulation will now be inaccurate");
        return;
    }

    // Check if there is already a job for this gate at this time;
    if (unit->lockTag[TIME(ctx, offset)]) {
    	LOG(DEBUG, "T: %i - Duplicate update job dropped for %i from %i", ctx->timestep, unit->ID, src);
    	return;
    }

    // Create Job

    // Find out when this job is
    unsigned long time = TIME(ctx, offset);
    // Get the address of the job
    unsigned long j = ctx->jobpoolCount[time]++;
    // Fill in the details
	ctx->jobpool[JPadr(ctx, offset, j)].unit = unit;
	ctx->jobpool[JPadr(ctx, offset, j)].src = src;
    ctx->jobpool[JPadr(ctx, offset, j)].ctx = ctx;
    ctx->jobpool[JPadr(ctx, offset, j)].timestep = time;

    // Register a job at this time with this gate
    unit->lockTag[TIME(ctx, offset)] = true;
    LOG(DEBUG, "T:%i - Created job @ %i for %i from %i (address: %i)", ctx->timestep, ctx->timestep + offset, unit->ID, src, JPadr(ctx, offset, unit->ID));
    return;
}

void setUnitState(dispatcher *ctx, GLI *unit, logicType state, size_t src){
	if ((state != unit->state) // If state has changed:
	    	|| (unit->inputMode == INPUT) //OR if gate is an input
	    ) {
		if (unit->inputMode != INPUT) {
			// Register change with diff buffer;
			ctx->diffBuffer[ctx->diffBufferCount].ID = unit->ID;
			ctx->diffBuffer[ctx->diffBufferCount].newState = state;
			// Only fiddle with this when we're done playing with it.
			ctx->diffBufferCount++;

			//update rendering fields
		}

		unit->lastUpdated = ctx->timestep;
		unit->updatedBy = src;

		// Get and update Outputs;
		fastlist *outputs = graphGetConnectionsBySrc(ctx->LG, unit->ID);
		size_t count = fastlistSize(outputs);
		for (size_t i = 0; i < count; i++) {
			// Get The source gate for the connection.
			connection *conn = (connection *) fastlistGetIndex(outputs, i);
			// Generate Job;
			generateJob(ctx, conn->drnEp, 1, unit->ID); // TODO: include delay.
		}
	}
}

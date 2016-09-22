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

#include "dispatcher.h"

#include <stdlib.h>
#include <string.h>

#include "utils/thpool.h"

#define LOGMODULE "DISPATCHER"
#include "utils/lcadLogger.h"

#ifndef MAX_DELAY
    #define MAX_DELAY 100
#endif

#define GLI genericLogicInterface

/* Macro Generates the address of a thing for the stuff */
#define JPadr(ctx, offset, slot) ((((ctx->timestep + offset) % (MAX_DELAY + 1)) * ctx->n) + slot)

struct {
    GLI *unit;
    long timestep;
    dispatcher *ctx;
} typedef job;

struct {
    unsigned long ID;
    bool newState;
} typedef diff;

struct s_dispatcher {
    threadpool pool;
    unsigned long timestep, n;
    graph *LG;
    // Array containing all jobs for all upcoming timesteps.
    job *jobpool;
    // Array containing number of used slots in each given timestep.
    unsigned long *jobpoolCount; // size = (MAX_DELAY + 1)
    diff *diffBuffer;
    unsigned long diffBufferCount;

    //pool containing update locks.
    bool *lockPool;
};

void worker_do_work(job *j);

void generate_job(dispatcher *ctx, GLI *unit, unsigned int offset, int src) {
    // If job is too far in the future throw it away.
	if (offset > MAX_DELAY) {
        LOG(ERROR, "T: %i - Job submitted with offset of %i; dropping", ctx->timestep, offset);
        LOG(CRITICAL, "Simulation will now be inaccurate");
        return;
    }

    // Check if there is already a job for this gate at this time;
    if (ctx->lockPool[JPadr(ctx, offset, unit->ID)]) {
    	LOG(DEBUG, "T: %i - Duplicate update job dropped for %i", ctx->timestep, unit->ID);
    	return;
    }

    // Create Job

    // Find out when this job is
    unsigned long time = (ctx->timestep + offset) % (MAX_DELAY + 1);
    // Get the address of the job
    unsigned long j = ctx->jobpoolCount[time]++;
    // Fill in the details
	ctx->jobpool[JPadr(ctx, offset, j)].unit = unit;
    ctx->jobpool[JPadr(ctx, offset, j)].ctx = ctx;
    ctx->jobpool[JPadr(ctx, offset, j)].timestep = time;

    // Register a job at this time with this gate
    ctx->lockPool[JPadr(ctx, offset, unit->ID)] = true;
    LOG(DEBUG, "T:%i - Created job @ %i for %i (address: %i)", ctx->timestep, ctx->timestep + offset, unit->ID, JPadr(ctx, offset, unit->ID));
    return;
}

dispatcher *dispatcherCreate(graph *logicGraph, int threads) {
    dispatcher* ctx = (dispatcher*) malloc(sizeof(dispatcher));

    // Fill in details;
    ctx->LG = logicGraph;

    //TODO: Lock Graph for editing;

    ctx->timestep = 0;
    ctx->pool = thpool_init(threads);
    ctx->n = graphGetNodeCount(logicGraph);

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

    // Set up complete
    LOG(INFO1, "Created Dispatcher %i nodes, %i threads", ctx->n, threads);
    return ctx;
}

void dispatcherDelete(dispatcher *ctx) {
    // Free everything
	// Graph Should be in a safe state;
	thpool_destroy(ctx->pool);
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
    unsigned long i;
    
    // Constanty stuff
    unsigned long time = ctx->timestep % (MAX_DELAY + 1);
    
	LOG(INFO1, "T:%i Stepping Dispatcher. Jobs: %i, Time: %i", ctx->timestep, ctx->jobpoolCount[time], time);
    //printf("Step %i: ctx->jobpoolCount[%i] = %li\n", ctx->timestep, time, ctx->jobpoolCount[time]);

	
    // Adds each job to the threadpool's queue for execution.
    for (i = 0; i < ctx->jobpoolCount[time]; i++) {
        job *j = &ctx->jobpool[JPadr(ctx, 0, i)];
		worker_do_work(j);
		// thpool_add_work(ctx->pool, (void*) worker_do_work, (void*) j);
    }
    
    // Wait for the step execution to complete.
    // thpool_wait(ctx->pool);
    
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

int dispatcherAddJob(dispatcher *ctx, unsigned long ID, unsigned int delay) {
    if (delay == 0) return -1;
    if (delay > MAX_DELAY) return -2;
    GLI *gli = graphGetGLI(ctx->LG, ID); 
    generate_job(ctx, gli, delay, -1);
    return 0;
};

void worker_do_work(job *j) {
    // Get Inputs;
    fastlist *inputs = graphGetConnectionsByDrn(j->ctx->LG, j->unit->ID);  
    unsigned long count = fastlistSize(inputs);
    unsigned long i;
    unsigned long sum = 0;
    for (i = 0; i < count; i++) {
        // get The source gate for the connection.
        connection *conn = (connection*) fastlistGetIndex(inputs, i);
        // add the gate to the input sum.
        sum += conn->srcEp->state;
    }
    
    // Compare state;
    bool output = false;
    switch (j->unit->inputMode) {
        case AND:   if (sum == count) output = true; break; 
        case UNITY: // Behaves like a 1 input OR
        case OUTPUT: // Behaves like a 1 input OR
        case OR:    if (sum > 0)      output = true; break;
        case XOR:   if (sum == 1)     output = true; break;
        case INPUT: output = j->unit->state; break;
        default: break;
    }
    if (j->unit->inputNegate) output = !output;
    
    if ((output != j->unit->state) // If state has changed:
    	|| (j->unit->inputMode == INPUT) //OR if gate is an input
    ) {
		if (j->unit->inputMode != INPUT) {
			// Register change with diff buffer;
			j->ctx->diffBuffer[j->ctx->diffBufferCount].ID = j->unit->ID;
			j->ctx->diffBuffer[j->ctx->diffBufferCount].newState = output;
			// Only fiddle with this when we're done playing with it.
			j->ctx->diffBufferCount++;
		}

        // Get Outputs;
        fastlist *outputs = graphGetConnectionsBySrc(j->ctx->LG, j->unit->ID);
		count = fastlistSize(outputs);
		for (i = 0; i < count; i++) {
			// get The source gate for the connection.
			connection *conn = (connection *) fastlistGetIndex(outputs, i);
			// Generate Job;
			generate_job(j->ctx, conn->drnEp, 1, j->unit->ID); // TODO: include delay.
		}
    }
}

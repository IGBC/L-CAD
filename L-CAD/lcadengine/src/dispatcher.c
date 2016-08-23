#define MAX_DELAY 100

#include <lcadengine/dispatcher.h>

#include <stdlib.h>

#include "utils/thpool.h"
#include "utils/fastlist.h"

#define GLI genericLogicInterface

struct {
    GLI* unit;
    long timestep;
    dispatcher *ctx;
} typedef job;

struct s_dispatcher {
    threadpool pool;
    unsigned long timestep, n;
    graph *LG;
    job **jobpool;
    unsigned long *jobpoolCount;
};

inline void generate_job(dispatcher *ctx, GLI *unit, unsigned int offset);
void worker_do_work(job j);

dispatcher *create_dispatcher(graph *logicGraph, int threads) {
    dispatcher* ctx = (dispatcher*) malloc(sizeof(dispatcher));
    ctx->LG = logicGraph;
    //TODO: Lock Graph for editing;
    ctx->timestep = 0;
    ctx->pool = thpool_init(threads);
    ctx->n = get_node_count(logicGraph);
    // make a big thing to store Jobs in.
    
    //TODO: Memset both of these to 0;
    ctx->jobpool = (job**) malloc(ctx->n * (MAX_DELAY + 1) * sizeof(job));
    ctx->jobpoolCount = (unsigned long*) malloc((MAX_DELAY + 1) * sizeof(unsigned long)); 
}

void delete_dispatcher(dispatcher *ctx) {
    thpool_destroy(ctx->pool);
    free(ctx->jobpool);
}

int step_dispatcher(dispatcher *ctx) {
    ctx->timestep++;
}

void worker_do_work(job j) {
    // Get Inputs;
    fastlist *inputs = get_conns_by_drn(j.ctx->LG, j.unit->ID);  
    unsigned long count = fastlist_size(inputs);
    unsigned long i;
    unsigned long sum = 0;
    for (i = 0; i < count; i++) {
        // get The source gate for the connection.
        connection *conn = (connection*) fastlist_get(inputs, i);
        GLI *in = conn->srcEp;
        // add the gate to the input sum.
        sum += in->state;
    }
    
    // Compare state;
    bool output = false;
    switch (j.unit->inputMode) {
        case AND:   if (sum == count) output = true; break; 
        case UNITY: // Behaves like a 1 input OR
        case OR:    if (sum > 0)      output = true; break;
        case XOR:   if (sum == 1)     output = true; break;
        case RAND: 
        default: break;
    }
    if (j.unit->inputNegate) output != output;
    
    // If state has changed:
    if (output != j.unit->state) {
        //TODO: Save output to buffer;
        
        // Get Outputs;
        fastlist *outputs = get_conns_by_src(j.ctx->LG, j.unit->ID);
        count = fastlist_size(outputs);
        for (i = 0; i < count; i++) {
            // get The source gate for the connection.
            connection *conn = (connection*) fastlist_get(outputs, i);
            GLI *out = conn->drnEp;
            // Generate Job;
            generate_job(j.ctx, out, 1); // TODO: include delay.
        }
    }
}

inline void generate_job(dispatcher *ctx, GLI *unit, unsigned int offset) {
    if (offset > MAX_DELAY) {
        //TODO: Error.
    }
    unsigned long time = ctx->timestep + offset;
    unsigned long i = time % MAX_DELAY;
    unsigned long j = ctx->jobpoolCount[i]++;
    ctx->jobpool[i][j].unit = unit;
    ctx->jobpool[i][j].ctx = ctx;
    ctx->jobpool[i][j].timestep = time;
}


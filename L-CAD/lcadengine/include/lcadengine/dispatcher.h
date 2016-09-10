#ifndef DISPATCHER_H_INCLUDED
#define DISPATCHER_H_INCLUDED

#include <lcadengine/logicGraph.h>

struct s_dispatcher;
typedef struct s_dispatcher dispatcher;

dispatcher *dispatcherCreate(graph *logicGraph, int threads);
void dispatcherDelete(dispatcher *ctx);
int dispatcherStep(dispatcher *ctx);
int dispatcherAddJob(dispatcher *ctx, unsigned long ID, unsigned int delay);


#endif

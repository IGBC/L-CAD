#ifndef DISPATCHER_H_INCLUDED
#define DISPATCHER_H_INCLUDED

#include <lcadengine/logicGraph.h>

struct s_dispatcher;
typedef struct s_dispatcher dispatcher;

dispatcher *create_dispatcher(graph *logicGraph, int threads);
void delete_dispatcher(dispatcher *ctx);
int step_dispatcher(dispatcher *ctx);

#endif

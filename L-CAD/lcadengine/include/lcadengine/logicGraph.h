#ifndef LOGICGRAPH_H_INCLUDED
#define LOGICGRAPH_H_INCLUDED

#include <stdbool.h>
#include <lcadengine/fastlist.h>

typedef enum {AND, OR, XOR, UNITY, RAND} gateInputType;

struct {
	unsigned long ID; /* Sequential ID of Gate */
	bool state; /* Current Output state for this GLI */
	unsigned int delay; /* Propagation delay of this gate */
	gateInputType inputMode; /* AND OR etc.... */
	bool inputNegate; /* N in front of the mode */
} typedef genericLogicInterface;

struct {
	unsigned long ID; /* ID of this connection */
	genericLogicInterface *srcEp; /* pointer to the GLI of the source */
	genericLogicInterface *drnEp; /* pointer to the GLI of the drain */
	unsigned long srcID; /* ID of the source */
	unsigned long drnID; /* ID of the drain */
} typedef connection;

struct s_graph;
typedef struct s_graph graph;

graph *graphCreate();
void graphDelete(graph *ctx);

unsigned long graphAddGLI(graph *ctx, gateInputType type, bool nin, unsigned int delay);
void graphRemoveGLI(graph *ctx, unsigned long ID);

unsigned long graphAddConnection(graph *ctx, unsigned long Src, unsigned long Snk);
void graphRemoveConnection(graph *ctx, unsigned long ID);

genericLogicInterface *graphGetGLI(graph *ctx, unsigned long ID);

connection *graphGetConnectionByID(graph *ctx, unsigned long ID);
fastlist *graphGetConnectionsBySrc(graph *ctx, unsigned long srcID);
fastlist *graphGetConnectionsByDrn(graph *ctx, unsigned long drnID);

unsigned long graphGetNodeCount(graph *ctx);

void graphPrint(graph* ctx);
#endif

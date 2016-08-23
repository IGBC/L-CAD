#ifndef LOGICGRAPH_H_INCLUDED
#define LOGICGRAPH_H_INCLUDED

#include <stdbool.h>

#include "utils/fastlist.h"

typedef enum {AND, OR, XOR, UNITY, RAND} gateInputType;

struct {
	unsigned long ID; /* Sequential ID of Gate */
	bool state; /* Current Output state for this GLI */
	unsigned int delay; /* Propication delay of this gate */
	gateInputType inputMode; /* AND OR etc.... */
	bool inputNegate; /* N infront of the mode */
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

graph *create_graph();
void delete_graph(graph *ctx);

unsigned long add_gli(graph *ctx, gateInputType type, bool nin, unsigned int delay);
void remove_gli(graph *ctx, unsigned long ID);

unsigned long add_conn(graph *ctx, unsigned long Src, unsigned long Snk);
void remove_conn(graph *ctx, unsigned long ID);

genericLogicInterface *get_gli(graph *ctx, unsigned long ID);

connection *get_conn_by_id(graph *ctx, unsigned long ID);
fastlist *get_conns_by_src(graph *ctx, unsigned long srcID);
fastlist *get_conns_by_drn(graph *ctx, unsigned long drnID);

unsigned long get_node_count(graph *ctx);
#endif

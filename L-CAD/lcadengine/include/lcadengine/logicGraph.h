#ifndef LOGICGRAPH_H_INCLUDED
#define LOGICGRAPH_H_INCLUDED
#include <stdint.h>
#include <stdbool.h>

#include "utils/fastlist.h"

typedef enum {AND, OR, XOR, UNITY, RAND} gateInputType;

struct {
	uint64_t ID; /* Sequential ID of Gate */
	bool state; /* Current Output state for this GLI */
	uint8_t delay; /* Propication delay of this gate */
	gateInputType inputMode; /* AND OR etc.... */
	bool inputNegate; /* N infront of the mode */
} typedef genericLogicInterface;

struct {
	uint64_t ID; /* ID of this connection */
	genericLogicInterface *srcEp; /* pointer to the GLI of the source */
	genericLogicInterface *drnEp; /* pointer to the GLI of the drain */
	uint64_t srcID; /* ID of the source */
	uint64_t drnID; /* ID of the drain */
} typedef connection;

struct s_graph;
typedef struct s_graph graph;

graph *create_graph();
void delete_graph(graph *ctx);

uint64_t add_gli(graph *ctx, gateInputType type, bool nin, uint8_t delay);
void remove_gli(graph *ctx, uint64_t ID);

uint64_t add_conn(graph *ctx, uint64_t Src, uint64_t Snk);
void remove_conn(graph *ctx, uint64_t ID);

genericLogicInterface *get_gli(graph *ctx, uint64_t ID);

connection *get_conn_by_id(graph *ctx, uint64_t ID);
fastlist *get_conns_by_src(graph *ctx, uint64_t srcID);
fastlist *get_conns_by_drn(graph *ctx, uint64_t drnID);

unsigned long get_node_count(graph *ctx);
#endif

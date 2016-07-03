#include <stdint.h>
#include <stdbool.h>

#include <lcadengine/utils/hashmap.h> 

typedef enum {AND, OR, XOR, UNITY, RAND} gateInputType;

/* Because Forward Declaration*/
typedef struct s_genericLogicInterface genericLogicInterface;

struct s_genericLogicInterface {
	uint64_t ID; /* Sequential ID of Gate */
	bool state; /* Current Output state for this GLI */
	uint8_t delay; /* Propication delay of this gate */
	gateInputType inputMode; /* AND OR etc.... */
	bool inputNegate; /* N infront of the mode */
};
struct {
	uint64_t ID; /* ID of this connection */
	genericLogicInterface *srcEp; /* pointer to the GLI of the source */
	genericLogicInterface *drnEp; /* pointer to the GLI of the drain */
	uint64_t srcID; /* ID of the source */
	uint64_t drnID; /* ID of the drain */
} typedef connection;

struct s_context;
typedef struct s_context context;

context *create_context();
void delete_context(context *ctx);

uint64_t add_gli(context *ctx, gateInputType type, bool nin, uint8_t delay);
void remove_gli(context *ctx, uint64_t ID);
genericLogicInterface get_gli(context *ctx, uint64_t ID);

uint64_t add_conn(context *ctx, uint64_t Src, uint64_t Snk);
void remove_conn(context *ctx, uint64_t ID);
//TODO: Work out how to get connections.


#include <lcadengine/utils/hashmap.h> 

typedef enum {AND, OR, XOR, UNITY, RAND} gateInputType;

struct {
	uint64_t ID;
	bool state;
	uint8_t delay;
	gateInputType inputMode;
	bool inputNegate;
	gate *outEp;
	gate *inEp;
} typedef genericLogicInterface;

struct {
	uint64_t ID;
	gate *srcEp;
	gate *snkEp;
} typedef connection;

struct context {
	hashmap *IDMap, *inEpMap, *outEpMap;
	hashmap *connMap;
}	

struct context *create_context();
void delete_context(context *ctx);

uint64_t add_gli(context *ctx, gateInputType type, bool nin, uint8_t delay);
void remove_gli(context *ctx, uint64_t ID);
genricLogicInterface get_gli(context *ctx, uint64_t ID);

uint64_t add_conn(context *ctx, uint64_t Src, uint64_t Snk);
void remove_conn(context *ctx, uint64_t ID);
//TODO: Work out how to get connections.


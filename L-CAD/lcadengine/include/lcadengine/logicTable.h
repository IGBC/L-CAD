#include <stdint.h>
#include <stdbool.h>

#include <lcadengine/utils/hashmap.h> 

typedef enum {AND, OR, XOR, UNITY, RAND} gateInputType;

typedef struct s_genericLogicInterface genericLogicInterface;

struct s_genericLogicInterface {
	uint64_t ID;
	bool state;
	uint8_t delay;
	gateInputType inputMode;
	bool inputNegate;
	genericLogicInterface *outEp;
	genericLogicInterface *inEp;
};
struct {
	uint64_t ID;
	genericLogicInterface *srcEp;
	genericLogicInterface *snkEp;
} typedef connection;

struct{
	hashmap *IDMap, *inEpMap, *outEpMap;
	hashmap *connMap;
} typedef context; 

context *create_context();
void delete_context(context *ctx);

uint64_t add_gli(context *ctx, gateInputType type, bool nin, uint8_t delay);
void remove_gli(context *ctx, uint64_t ID);
genericLogicInterface get_gli(context *ctx, uint64_t ID);

uint64_t add_conn(context *ctx, uint64_t Src, uint64_t Snk);
void remove_conn(context *ctx, uint64_t ID);
//TODO: Work out how to get connections.


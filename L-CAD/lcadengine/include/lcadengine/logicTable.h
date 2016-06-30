#include <lcadengine/utils/hashmap.h> 

typedef enum {AND, OR, XOR, UNITY, RAND} gateInputType;

struct {
	uint64_t ID;
	bool state;
	int delay;
	gateInputType inputMode;
	bool inputNegate;
	gate *outEp;
	gate *inEp;
} typedef genericLogicInterface;

struct {
	gate *srcEp;
	gate *snkEp;
} typedef connection;

struct context {
	hashmap *IDMap, *inEpMap, *outEpMap;
	hashmap *connMap;
}	

void create_context();
void delete_context();

uint64_t add_gli();
void remove_gli(uint64_t ID);
genricLogicInterface get_gli(uint64_t ID);

uint64_t add_conn();
void remove_conn(uint64_t ID);
//TODO: Work out how to get connections.


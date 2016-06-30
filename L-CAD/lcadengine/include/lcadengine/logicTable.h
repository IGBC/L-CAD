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

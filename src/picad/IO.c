#include "IO.h"
#include <stdlib.h>
#include "wires.h"


IO_Item *setupPin(uint8_t pin, IO_Mode mode) {
    IO_Item *store = (IO_Item*) malloc(sizeof(IO_Item));
    if (!store) {
        return NULL;
    }	
    switch (mode) {
        case IOM_OUT:
            pinMode(pin, OUTPUT);
            break;
        case IOM_IN:
            pinMode(pin, INPUT);
            pullUpDnControl(pin, PUD_OFF);
            break;
        case IOM_IN_UP:
            pinMode(pin, INPUT);
            pullUpDnControl(pin, PUD_UP);
            break;
        case IOM_IN_DOWN:
            pinMode(pin, INPUT);
            pullUpDnControl(pin, PUD_DOWN);
            break;
    }
	store->address = pin;
	store->mode = mode;
	return store;
}

void cleanPin(IO_Item *pin) {
    pinMode(pin->address, INPUT);
    pullUpDnControl(pin->address, PUD_OFF);
    free(pin);
}

bool readInput(IO_Item *input) {
	return (bool) digitalRead(input->address);
}

void writeOutput(IO_Item *output, bool state) {
	if (output->mode == IOM_OUT) {
        digitalWrite(output->address, (int) state);
    }
}


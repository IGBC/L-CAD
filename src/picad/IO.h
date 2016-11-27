#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include "stdint.h"
#include <stdbool.h>
#include <stdlib.h>

typedef enum { IOM_OUT, IOM_IN, IOM_IN_UP, IOM_IN_DOWN } IO_Mode;

struct {
	uint8_t address;
    size_t ID;
	IO_Mode mode;
} typedef IO_Item;

IO_Item *setupPin(uint8_t pin, IO_Mode mode);
void cleanPin(IO_Item *pin);

bool readInput(IO_Item *input);
void writeOutput(IO_Item *output, bool state);

#endif

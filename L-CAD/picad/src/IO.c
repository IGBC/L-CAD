IO_Item *setupPin(uint8_t pin, IO_Mode mode) {
	if (/* wiring pi stuff */) {
		IO_Item *store = (IO_Item*) malloc(sizeof(IO_Item);
		if (store) {
			store->address = pin;
			store->mode = mode;
		}
		return store;
	} else {
        	return NULL;
	}
}

bool readInput(IO_Item *input) {
	if (input->mode != IOM_OUT) {
		/* wiring pi magic */
	} else {
		return false;
	}
}

void writeOutput(IO_Item *output, bool state);
	if (input->mode == IOM_OUT) {                                                                    │
                /* wiring pi magic */                                                                    │                // Update outputs
        }
}


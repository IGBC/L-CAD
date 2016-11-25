#include "logicGraph.h"
#include "dispatcher.h"
#include "IO.h"


int main(int argc, char *argv[]) {
	// Read File

	graph *g;

	// Load engine
	int cores = (int) sysconf(_SC_NPROCESSORS_ONLN);
	dispatcher *d = dispatcherCreate(g, cores);

	for(;;) { // Run until someone presses ^C
		// Read inputs

		// Run sim one step
		dispatcherStep(d);

		// Update outputs
	}

	dispatcherDelete(d);
	graphDelete(g);

	// kill all humans

	return 0;
}

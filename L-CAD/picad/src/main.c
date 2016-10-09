#include "logicGraph.h"
#include "dispatcher.h"

int main(int argc, char *argv[]) {
	// Read File

	graph *g;

	// Load engine

	int cores = (int) sysconf(_SC_NPROCESSORS_ONLN);

	dispatcher *d = dispatcherCreate(g, cores);

	for(;;) { // Run until someone presses ^C
		// Read inputs

		// Run sim one step

		// Update outputs
	}

	dispatcherDelete(d);
	graphDelete(g);

	// kill all humans

	// return
}

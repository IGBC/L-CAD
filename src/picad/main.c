#include "../lcadengine/logicGraph.h"
#include "../lcadengine/dispatcher.h"
#include "IO.h"
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>

static volatile int keepRunning = 1;

void intHandler(int dummy) {
    keepRunning = 0;
    signal(SIGINT, intHandler);
}

int useconds(void) {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return 1000000 * tv.tv_sec + tv.tv_usec;
}

int main(int argc, char *argv[]) {
    
	// TODO: Read File
    
    // TODO: Get this.
    // speed of simulation (in µs)
    int delay = 1000; //(1ms)

	graph *g;

	// Load engine
	dispatcher *d = dispatcherCreate(g, 0);
        
    // Run until someone presses ^C
    signal(SIGINT, intHandler);
	while(keepRunning) {
        //get time 
        int start = useconds();
        // TODO: Read inputs

		// Run simulation one step
		dispatcherStep(d);

		// TODO: Update outputs

        //get time again
        int end = useconds();
        int time = end - start;
        if (time > delay) {
            printf("Can't Keep Up. Delay set to %iµs, update took %iµs", delay, time);
        } else {
            usleep((delay - time));
        }        
	}

	dispatcherDelete(d);
	graphDelete(g);

    // TODO: Cleanup GPIO 

	// TODO: kill all humans

	return 0;
}

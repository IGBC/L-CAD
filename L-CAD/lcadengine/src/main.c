
#include <lcadengine/logicGraph.h>
#include <lcadengine/dispatcher.h>
#include <lcadengine/graphLoader.h>
#include <stdio.h>

void simulate_adder() {
    graph *g = graphCreate();

    unsigned long a = graphAddGLI(g, INPUT, true, 101, 0);
    unsigned long b = graphAddGLI(g, INPUT, false, 102,  0);
    unsigned long c = graphAddGLI(g, INPUT, false, 103, 0);

    unsigned long xor1 = graphAddGLI(g, XOR, false, 4, 0);
    unsigned long andAB = graphAddGLI(g, AND, false, 5, 0);
    unsigned long and1C = graphAddGLI(g, AND, false, 6, 0);

    unsigned long out = graphAddGLI(g, XOR, false, 7, 0);
    unsigned long cOut = graphAddGLI(g, OR, false, 8, 0);

    unsigned long OUT = graphAddGLI(g, OUTPUT, false, 200, 0);
    unsigned long COUT = graphAddGLI(g, OUTPUT, false, 201, 0);

    /* Setup connections */
    graphAddConnection(g, a, xor1);
    graphAddConnection(g, b, xor1);

    graphAddConnection(g, xor1, out);
    graphAddConnection(g, c, out);

    graphAddConnection(g, xor1, and1C);
    graphAddConnection(g, c, and1C);

    graphAddConnection(g, a, andAB);
    graphAddConnection(g, b, andAB);

    graphAddConnection(g, andAB, cOut);
    graphAddConnection(g, and1C, cOut);

    graphAddConnection(g, out, OUT);
    graphAddConnection(g, cOut, COUT);

    dispatcher *d = dispatcherCreate(g, 4);

    graphGetGLI(g, a)->state = true;
    graphGetGLI(g, b)->state = true;
    graphGetGLI(g, c)->state = true;

    dispatcherAddJob(d, a, 1);
    dispatcherAddJob(d, b, 1);
    dispatcherAddJob(d, c, 1);

    for (int i = 0; i < 10; i++) {
        graphPrint(g);
    	dispatcherStep(d);
    }

    dispatcherDelete(d);
    graphDelete(g);
}


void calculate_truth_table(gateInputType t, bool n) {
    graph *g = graphCreate();
    unsigned long in1 = graphAddGLI(g, UNITY, false, 101, 0);
    unsigned long in2 = graphAddGLI(g, UNITY, false, 102, 0);
    unsigned long in3 = graphAddGLI(g, UNITY, false, 103, 0);
    unsigned long ID = graphAddGLI(g, t, n, 1, 0);
    graphAddConnection(g, in1, ID);
    graphAddConnection(g, in2, ID);
    graphAddConnection(g, in3, ID);
    graphGetGLI(g, ID)->state = true;
    dispatcher *d = dispatcherCreate(g, 4);
    //printf("output values are: %i, %i, %i\n",(int *) graphGetGLI(g, in1)->state, (int *) graphGetGLI(g, in2)->state, (int *) graphGetGLI(g, ID)->state);

    graphGetGLI(g, in1)->state = false;
    graphGetGLI(g, in2)->state = false;
    graphGetGLI(g, in3)->state = false;
    dispatcherAddJob(d, ID, 1);
    dispatcherStep(d);
    printf("output values are: %i, %i, %i = %i\n",(int *) graphGetGLI(g, in1)->state, (int *) graphGetGLI(g, in2)->state, (int *) graphGetGLI(g, in3)->state, (int *) graphGetGLI(g, ID)->state);

    graphGetGLI(g, in1)->state = false;
    graphGetGLI(g, in2)->state = false;
    graphGetGLI(g, in3)->state = true;
    dispatcherAddJob(d, ID, 1);
    dispatcherStep(d);
    printf("output values are: %i, %i, %i = %i\n",(int *) graphGetGLI(g, in1)->state, (int *) graphGetGLI(g, in2)->state, (int *) graphGetGLI(g, in3)->state, (int *) graphGetGLI(g, ID)->state);



    graphGetGLI(g, in1)->state = false;
    graphGetGLI(g, in2)->state = true;
    graphGetGLI(g, in3)->state = false;
    dispatcherAddJob(d, ID, 1);
    dispatcherStep(d);
    printf("output values are: %i, %i, %i = %i\n",(int *) graphGetGLI(g, in1)->state, (int *) graphGetGLI(g, in2)->state, (int *) graphGetGLI(g, in3)->state, (int *) graphGetGLI(g, ID)->state);



    graphGetGLI(g, in1)->state = false;
    graphGetGLI(g, in2)->state = true;
    graphGetGLI(g, in3)->state = true;
    dispatcherAddJob(d, ID, 1);
    dispatcherStep(d);
    printf("output values are: %i, %i, %i = %i\n",(int *) graphGetGLI(g, in1)->state, (int *) graphGetGLI(g, in2)->state, (int *) graphGetGLI(g, in3)->state, (int *) graphGetGLI(g, ID)->state);



    graphGetGLI(g, in1)->state = true;
    graphGetGLI(g, in2)->state = false;
    graphGetGLI(g, in3)->state = false;
    dispatcherAddJob(d, ID, 1);
    dispatcherStep(d);
    printf("output values are: %i, %i, %i = %i\n",(int *) graphGetGLI(g, in1)->state, (int *) graphGetGLI(g, in2)->state, (int *) graphGetGLI(g, in3)->state, (int *) graphGetGLI(g, ID)->state);



    graphGetGLI(g, in1)->state = true;
    graphGetGLI(g, in2)->state = false;
    graphGetGLI(g, in3)->state = true;
    dispatcherAddJob(d, ID, 1);
    dispatcherStep(d);
    printf("output values are: %i, %i, %i = %i\n",(int *) graphGetGLI(g, in1)->state, (int *) graphGetGLI(g, in2)->state, (int *) graphGetGLI(g, in3)->state, (int *) graphGetGLI(g, ID)->state);



    graphGetGLI(g, in1)->state = true;
    graphGetGLI(g, in2)->state = true;
    graphGetGLI(g, in3)->state = false;
    dispatcherAddJob(d, ID, 1);
    dispatcherStep(d);
    printf("output values are: %i, %i, %i = %i\n",(int *) graphGetGLI(g, in1)->state, (int *) graphGetGLI(g, in2)->state, (int *) graphGetGLI(g, in3)->state, (int *) graphGetGLI(g, ID)->state);



    graphGetGLI(g, in1)->state = true;
    graphGetGLI(g, in2)->state = true;
    graphGetGLI(g, in3)->state = true;
    dispatcherAddJob(d, ID, 1);
    dispatcherStep(d);
    printf("output values are: %i, %i, %i = %i\n",(int *) graphGetGLI(g, in1)->state, (int *) graphGetGLI(g, in2)->state, (int *) graphGetGLI(g, in3)->state, (int *) graphGetGLI(g, ID)->state);

    dispatcherDelete(d);
    graphDelete(g);
}


int main() {
    printf("+= Sizeof =+\n| char:  %i |\n| short: %i |\n| int:   %i |\n| long:  %i |\n| void*: %i |\n+----------+\n",sizeof(char), sizeof(short), sizeof(int), sizeof(long), sizeof(void*)); 
   // simulate_adder();
    
//    printf("\n\n=== AND ===\n");
//    calculate_truth_table(AND, false);
//
//    printf("\n\n=== NAND ===\n");
//    calculate_truth_table(AND, true);
//
//    printf("\n\n=== OR ===\n");
//    calculate_truth_table(OR, false);
//
//    printf("\n\n=== NOR ===\n");
//    calculate_truth_table(OR, true);
//
//    printf("\n\n=== XOR ===\n");
//    calculate_truth_table(XOR, false);
//
//    printf("\n\n=== NXOR ===\n");
//    calculate_truth_table(XOR, true);

    graph *g = loaderLoad("0 NOT 0\n 1 NAND 0 1\n 2 IN");

//"0 IN \n \
#100 NOT 0 \n \
1 OUT 14 #Q1\n \
#2 OUT 24 #Q2\n \
#3 OUT 34 #Q2\n \
#4 OUT 44 #Q4\n \
\n \
11 NAND 15 0\n \
12 NOT 15\n \
13 NAND 12 0\n \
14 NAND 11 15 #Q\n \
15 NAND 13 14 #!Q\n \
\n \
#21 NAND 25 0\n \
#22 NOT 25\n \
#23 NAND 22 0\n \
#24 NAND 21 25 #Q\n \
#25 NAND 23 24 #!Q\n \
\n \
#31 NAND 35 0\n \
#32 NOT 35\n \
#33 NAND 32 0\n \
#34 NAND 31 35 #Q\n \
#35 NAND 33 34 #!Q\n \
\n \
#41 NAND 45 0\n \
#42 NOT 45\n \
#43 NAND 42 0\n \
#44 NAND 41 45 #Q\n \
#45 NAND 43 44 #!Q");
    graphPrint(g);

	dispatcher *d = dispatcherCreate(g, 4);
	int v = 0;	

	graphGetGLI(g, 0)->state = (bool)v;
	dispatcherAddJob(d, 0, 1);

	for(int i = 0; i < 16; i++) {
		printf("%i :\n", i);
		//v = 1 - v;
		//graphGetGLI(g, 0)->state = (bool)v;
		//dispatcherAddJob(d, 0, 1);

		for(int j = 0; j < 1; j++) {
			//printf(" %i,", j);
			dispatcherStep(d);
		}
		printf("\n");
		graphPrint(g);
	}
	    
	//graphDelete(g);

    return 0;    
}

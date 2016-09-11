
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

    graph *g = loaderLoad("#inputs\n101 IN\n 102 IN\n 1 NOR 2 3\n2 !OR 1 4\n3 NAND 101 102\n4 !AND 102 5\n5 NOT 101\n 201 OUT 1");
    graphPrint(g);
    graphDelete(g);



    return 0;    
}

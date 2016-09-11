
#include <lcadengine/logicGraph.h>
#include <lcadengine/dispatcher.h>
#include <stdio.h>

int boobs = 0;

#define PRINT_STATE \
    {int stateA = (int) graphGetGLI(g, a)->state; \
    int stateB = (int) graphGetGLI(g, b)->state; \
    int stateC = (int) graphGetGLI(g, c)->state; \
    int stateCOut = (int) graphGetGLI(g, cOut)->state; \
    int stateOut = (int) graphGetGLI(g, out)->state; \
    int stateAnd1c = (int) graphGetGLI(g, and1C)->state; \
    int stateAndAB = (int) graphGetGLI(g, andAB)->state; \
    int stateXor1 = (int) graphGetGLI(g, xor1)->state; \
    printf("=== Current State %i ===\n", boobs++); \
    printf("stateA: %i\n", stateA); \
    printf("stateB: %i\n", stateB); \
    printf("stateC: %i\n", stateC); \
    printf("stateCOut: %i\n", stateCOut); \
    printf("stateOut: %i\n", stateOut); \
    printf("stateAnd1c: %i\n", stateAnd1c); \
    printf("stateAndAB: %i\n", stateAndAB); \
    printf("stateXor1: %i\n", stateXor1);}


void simulate_adder() {
    graph *g = graphCreate();

    unsigned long A = graphAddGLI(g, UNITY, false, 0);
    unsigned long B = graphAddGLI(g, UNITY, false, 0);
    unsigned long C = graphAddGLI(g, UNITY, false, 0);

    unsigned long a = graphAddGLI(g, UNITY, false, 0);
    unsigned long b = graphAddGLI(g, UNITY, false, 0);
    unsigned long c = graphAddGLI(g, UNITY, false, 0);

    graphAddConnection(g, A, a);
    graphAddConnection(g, B, b);
    graphAddConnection(g, C, c);

    unsigned long xor1 = graphAddGLI(g, XOR, false, 0);
    unsigned long andAB = graphAddGLI(g, AND, false, 0);
    unsigned long and1C = graphAddGLI(g, AND, false, 0);

    unsigned long out = graphAddGLI(g, XOR, false, 0);
    unsigned long cOut = graphAddGLI(g, OR, false, 0);

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

    dispatcher *d = dispatcherCreate(g, 4);

    graphGetGLI(g, A)->state = false;
    graphGetGLI(g, B)->state = true;
    graphGetGLI(g, C)->state = true;

    dispatcherAddJob(d, a, 1);
    dispatcherAddJob(d, b, 1);
    dispatcherAddJob(d, c, 1);

    for (int i = 0; i < 10; i++) {
        //PRINT_STATE
        graphPrint(g);
    	dispatcherStep(d);
    }

    dispatcherDelete(d);
    graphDelete(g);
}


void calculate_truth_table(gateInputType t, bool n) {
    graph *g = graphCreate();
    unsigned long in1 = graphAddGLI(g, UNITY, false, 0);
    unsigned long in2 = graphAddGLI(g, UNITY, false, 0);
    unsigned long in3 = graphAddGLI(g, UNITY, false, 0);
    unsigned long ID = graphAddGLI(g, t, n, 0);
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
    simulate_adder();
    
    printf("\n\n=== AND ===\n");
    calculate_truth_table(AND, false);

    printf("\n\n=== NAND ===\n");
    calculate_truth_table(AND, true);

    printf("\n\n=== OR ===\n");
    calculate_truth_table(OR, false);
    
    printf("\n\n=== NOR ===\n");
    calculate_truth_table(OR, true);

    printf("\n\n=== XOR ===\n");
    calculate_truth_table(XOR, false);
    
    printf("\n\n=== NXOR ===\n");
    calculate_truth_table(XOR, true);

    graph *g = graphCreate();

    unsigned long A = graphAddGLI(g, UNITY, false, 0);
    unsigned long B = graphAddGLI(g, UNITY, false, 0);

    unsigned long a = graphAddGLI(g, UNITY, false, 0);
    unsigned long b = graphAddGLI(g, INPUT, false, 0);

    printf("connection A-a: %i\n", graphAddConnection(g, A, a));
    printf("connection B-a: %i\n", graphAddConnection(g, B, a));
    printf("connection B-b: %i\n", graphAddConnection(g, B, a));

    graphDelete(g);

    return 0;    
}


#include <lcadengine/logicGraph.h>
#include <lcadengine/dispatcher.h>
#include <stdio.h>

int boobs = 0;

#define PRINT_STATE \
    {int stateA = (int) get_gli(g, a)->state; \
    int stateB = (int) get_gli(g, b)->state; \
    int stateC = (int) get_gli(g, c)->state; \
    int stateCOut = (int) get_gli(g, cOut)->state; \
    int stateOut = (int) get_gli(g, out)->state; \
    int stateAnd1c = (int) get_gli(g, and1C)->state; \
    int stateAndAB = (int) get_gli(g, andAB)->state; \
    int stateXor1 = (int) get_gli(g, xor1)->state; \
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
    graph *g = create_graph();

    unsigned long A = add_gli(g, UNITY, false, 0);
    unsigned long B = add_gli(g, UNITY, false, 0);
    unsigned long C = add_gli(g, UNITY, false, 0);

    unsigned long a = add_gli(g, UNITY, false, 0);
    unsigned long b = add_gli(g, UNITY, false, 0);
    unsigned long c = add_gli(g, UNITY, false, 0);

    add_conn(g, A, a);
    add_conn(g, B, b);
    add_conn(g, C, c);

    unsigned long xor1 = add_gli(g, XOR, false, 0);
    unsigned long andAB = add_gli(g, AND, false, 0);
    unsigned long and1C = add_gli(g, AND, false, 0);

    unsigned long out = add_gli(g, XOR, false, 0);
    unsigned long cOut = add_gli(g, OR, false, 0);

    /* Setup connections */
    add_conn(g, a, xor1);
    add_conn(g, b, xor1);

    add_conn(g, xor1, out);
    add_conn(g, c, out);

    add_conn(g, xor1, and1C);
    add_conn(g, c, and1C);

    add_conn(g, a, andAB);
    add_conn(g, b, andAB);

    add_conn(g, andAB, cOut);
    add_conn(g, and1C, cOut);

    dispatcher *d = create_dispatcher(g, 4);

    get_gli(g, A)->state = false;
    get_gli(g, B)->state = true;
    get_gli(g, C)->state = true;

    dispatcher_add_job(d, a, 1);
    dispatcher_add_job(d, b, 1);
    dispatcher_add_job(d, c, 1);

    for (int i = 0; i < 10; i++) {
        PRINT_STATE
        step_dispatcher(d);
    }

    delete_dispatcher(d);
    delete_graph(g);
}


void calculate_truth_table(gateInputType t, bool n) {
    graph *g = create_graph();
    unsigned long in1 = add_gli(g, UNITY, false, 0);
    unsigned long in2 = add_gli(g, UNITY, false, 0);
    unsigned long in3 = add_gli(g, UNITY, false, 0);
    unsigned long ID = add_gli(g, t, n, 0);
    add_conn(g, in1, ID);
    add_conn(g, in2, ID);
    add_conn(g, in3, ID);
    get_gli(g, ID)->state = true;
    dispatcher *d = create_dispatcher(g, 4);
    //printf("output values are: %i, %i, %i\n",(int *) get_gli(g, in1)->state, (int *) get_gli(g, in2)->state, (int *) get_gli(g, ID)->state);

    get_gli(g, in1)->state = false;
    get_gli(g, in2)->state = false;
    get_gli(g, in3)->state = false;
    dispatcher_add_job(d, ID, 1);
    step_dispatcher(d);
    printf("output values are: %i, %i, %i = %i\n",(int *) get_gli(g, in1)->state, (int *) get_gli(g, in2)->state, (int *) get_gli(g, in3)->state, (int *) get_gli(g, ID)->state);

    get_gli(g, in1)->state = false;
    get_gli(g, in2)->state = false;
    get_gli(g, in3)->state = true;
    dispatcher_add_job(d, ID, 1);
    step_dispatcher(d);
    printf("output values are: %i, %i, %i = %i\n",(int *) get_gli(g, in1)->state, (int *) get_gli(g, in2)->state, (int *) get_gli(g, in3)->state, (int *) get_gli(g, ID)->state);



    get_gli(g, in1)->state = false;
    get_gli(g, in2)->state = true;
    get_gli(g, in3)->state = false;
    dispatcher_add_job(d, ID, 1);
    step_dispatcher(d);
    printf("output values are: %i, %i, %i = %i\n",(int *) get_gli(g, in1)->state, (int *) get_gli(g, in2)->state, (int *) get_gli(g, in3)->state, (int *) get_gli(g, ID)->state);



    get_gli(g, in1)->state = false;
    get_gli(g, in2)->state = true;
    get_gli(g, in3)->state = true;
    dispatcher_add_job(d, ID, 1);
    step_dispatcher(d);
    printf("output values are: %i, %i, %i = %i\n",(int *) get_gli(g, in1)->state, (int *) get_gli(g, in2)->state, (int *) get_gli(g, in3)->state, (int *) get_gli(g, ID)->state);



    get_gli(g, in1)->state = true;
    get_gli(g, in2)->state = false;
    get_gli(g, in3)->state = false;
    dispatcher_add_job(d, ID, 1);
    step_dispatcher(d);
    printf("output values are: %i, %i, %i = %i\n",(int *) get_gli(g, in1)->state, (int *) get_gli(g, in2)->state, (int *) get_gli(g, in3)->state, (int *) get_gli(g, ID)->state);



    get_gli(g, in1)->state = true;
    get_gli(g, in2)->state = false;
    get_gli(g, in3)->state = true;
    dispatcher_add_job(d, ID, 1);
    step_dispatcher(d);
    printf("output values are: %i, %i, %i = %i\n",(int *) get_gli(g, in1)->state, (int *) get_gli(g, in2)->state, (int *) get_gli(g, in3)->state, (int *) get_gli(g, ID)->state);



    get_gli(g, in1)->state = true;
    get_gli(g, in2)->state = true;
    get_gli(g, in3)->state = false;
    dispatcher_add_job(d, ID, 1);
    step_dispatcher(d);
    printf("output values are: %i, %i, %i = %i\n",(int *) get_gli(g, in1)->state, (int *) get_gli(g, in2)->state, (int *) get_gli(g, in3)->state, (int *) get_gli(g, ID)->state);



    get_gli(g, in1)->state = true;
    get_gli(g, in2)->state = true;
    get_gli(g, in3)->state = true;
    dispatcher_add_job(d, ID, 1);
    step_dispatcher(d);
    printf("output values are: %i, %i, %i = %i\n",(int *) get_gli(g, in1)->state, (int *) get_gli(g, in2)->state, (int *) get_gli(g, in3)->state, (int *) get_gli(g, ID)->state);

    delete_dispatcher(d);
    delete_graph(g);
}


int main() {
    //simulate_adder();

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

    return 0;    
}

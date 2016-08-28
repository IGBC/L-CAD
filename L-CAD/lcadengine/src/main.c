
#include <lcadengine/logicGraph.h>
#include <lcadengine/dispatcher.h>

int main() {
    // populate graph with one nor gate.
    graph *g = create_graph();
    unsigned long in1 = add_gli(g, UNITY, false, 0);
    unsigned long in2 = add_gli(g, UNITY, false, 0);
    unsigned long in3 = add_gli(g, UNITY, false, 0);
    unsigned long ID = add_gli(g, RAND, false, 0);
    add_conn(g, in1, ID);
    add_conn(g, in2, ID);
    add_conn(g, in3, ID);
    //get_gli(g, ID)->state = true;
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
    return 0;    
}

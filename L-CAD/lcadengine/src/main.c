
#include <lcadengine/logicGraph.h>
#include <lcadengine/dispatcher.h>

int main() {
    // populate graph with one nor gate.
    graph *g = create_graph();
    unsigned long ID = add_gli(g, OR, true, 0);
    dispatcher *d = create_dispatcher(g, 4);
    step_dispatcher(d);
    delete_dispatcher(d);
    delete_graph(g);    
}

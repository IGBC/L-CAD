#include <lcadengine/Simulation.h>
Simulation::Simulation() {
    nextID = 0;
    //TODO: Build dispatcher.
}

Simulation::~Simulation() {
    
}


uint64_t Simulation::newConnection(GenericLogicInterface *inEP, GenericLogicInterface *outEP) {
    LogicConnection *connection;
    try {
        connection = new LogicConnection();
    }
    catch (ConnectionfailedException e) {
	//TODO: Log this or something
	throw e;
    }
    inEP.connect(connection);
    uint64_t ID = nextID++;
    edgelist.insert(ID, connection);
    return ID;
      
}

#include <lcadengine/GenericLogicInterface.h>

GenericLogicInterface::GenericLogicInterface(int maxInputs, int propDelay, WorkDispatcherInterface &dispatcher) {
    //BOOBS (I was horny when I wrote this)
    this->maxInputs = maxInputs;
    this->propDelay = propDelay;
    this->dispatcher = dispatcher;
    
    update();
}

GenericLogicInterface::~GenericLogicInterface() {
    //TODO: Free anything that was assigned
}

void GenericLogicInterface::connect(LogicConnection &connection) {
    outputList.insert(connection);
    update();
}

void GenericLogicInterface::acceptConnection(LogicConnection &connection) {
    // if we have too many inputs already
    // and maxInputs is not a negative (reserved) value
    if ((inputList.size() >= maxInputs) && (maxInputs >= 0)) {
        //Cannot Create new connection as gate is full
	throw new std::exception("Connection Failed");
    }
    //register this as a new input
    inputList.insert(connection);
    update();
}

void GenericLogicInterface::destroyConnection(LogicConnection &connection) {
    inputList.remove(connection);
    outputList.remove(connection);
    update();
}

void GenericLogicInterface::update() {
    // For every item in this list:
    for (std::list<int>::iterator it=outputList.begin(); it != outputList.end(); ++it) {
        // add update job for when this gate's propergation delay is finished.
	dispatcher.addJob(propDelay);
    }
}

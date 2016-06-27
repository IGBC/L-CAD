#ifndef GENERICLOGICINTERFACE_H
#define GENERICLOGICINTERFACE_H

#include <list>

#include "./LogicConnection.h"
#include "./workers/WorkDispatcherInterface.h"
class GenericLogicInterface {
public:
    GenericLogicInterface(int maxInputs, WorkDispatcherInterface &dispatcher);
    ~GenericLogicInterface();

    void update();
    void isState();
    void connect(LogicConnection &connection);
    void acceptConnection(LogicConnection &connection); // throws ConnectionfailedException;
    void destroyConnection(LogicConnection &connection);

protected:
    
    std::list<&LogicConnection> inputList;
    std::list<&LogicConnection> outputList;
    
    const int maxInputs;
    const WorkDispatcherInterface &dispatcher;
    int propDelay; // Propergation delay of the gate
    
};

#endif // GENERICLOGICINTERFACE_H

//TODO: Create connection failed Exeption
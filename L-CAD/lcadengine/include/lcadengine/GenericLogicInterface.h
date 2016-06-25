#ifndef GENERICLOGICINTERFACE_H
#define GENERICLOGICINTERFACE_H

#import "./LogicConnection.h"

class GenericLogicInterface {
public:
	GenericLogicInterface() {};
	~GenericLogicInterface() {};

	virtual void update();
	virtual void isState();
	virtual void connect(LogicConnection connection);
	virtual void acceptConnection(LogicConnection connection) throws ConnectionfailedException;
	virtual void destroyConnection(LogicConnection connection);

};

#endif // GENERICLOGICINTERFACE_H

//TODO: Create connection failed Exeption
#ifndef LOGICCONNECTION_H
#define LOGICCONNECTION_H

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "./GenericLogicInterface.h"

class LogicConnection {
public:
	LogicConnection(GenericLogicInterface INEP, GenericLogicInterface OUTEP);
	~LogicConnection() {};

	const GenericLogicInterface INEP;
	const GenericLogicInterface OUTEP;

	void destroy();

};

#endif // LOGICCONNECTION_H
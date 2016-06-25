#ifndef SIMULATION_H
#define SIMULATION_H

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "./GenericLogicInterface.h"
#include "./LogicConnection.h"
#include "./Workers/WorkDispatcherInterface"

class Simulation {
public:
	Simulation() {};
	~Simulation() {};
	boost::uuids::uuid newConnection(GenericLogicInterface inEP, GenericLogicInterface outEP);

private:
	std::map<boost::uuids::uuid, GenericLogicInterface> nodelist = {};
	std::map<boost::uuids::uuid, LogicConnection> nodelist = {};
	WorkDispatcherInterface dispatcher;

};

#endif // SIMULATION_H
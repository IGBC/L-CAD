#ifndef SIMULATION_H
#define SIMULATION_H

#include <map>

#include "./GenericLogicInterface.h"
#include "./LogicConnection.h"
#include "./workers/WorkDispatcherInterface.h"

class Simulation {
public:
	Simulation();
	~Simulation();
	uint64_t newConnection(GenericLogicInterface *inEP, GenericLogicInterface *outEP);

private:
	std::map<uint64_t, GenericLogicInterface> nodelist = {};
	std::map<uint64_t, LogicConnection> edgelist = {};
	WorkDispatcherInterface *dispatcher;

	uint64_t nextID = 0;
};

#endif // SIMULATION_H
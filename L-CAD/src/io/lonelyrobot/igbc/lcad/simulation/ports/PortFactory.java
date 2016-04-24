package io.lonelyrobot.igbc.lcad.simulation.ports;

import io.lonelyrobot.igbc.lcad.simulation.workers.WorkDispatcherInterface;

public class PortFactory {
	/**
	 * Reference to work dispatcher to be given to logic gates
	 */
	private WorkDispatcherInterface dispatcher;
	
	public PortFactory(WorkDispatcherInterface dispatcher) {
		this.dispatcher = dispatcher;	
	}
	
	public LogicPortGate build(LogicPortInterface port){
		return new LogicPortGate(port.isOutput() ? 1 : 0, dispatcher, port);
	}
}
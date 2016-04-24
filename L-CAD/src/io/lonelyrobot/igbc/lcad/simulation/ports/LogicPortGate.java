package io.lonelyrobot.igbc.lcad.simulation.ports;

import java.util.Iterator;

import io.lonelyrobot.igbc.lcad.simulation.GenericLogicInterfaceHandler;
import io.lonelyrobot.igbc.lcad.simulation.LogicConnection;
import io.lonelyrobot.igbc.lcad.simulation.workers.WorkDispatcherInterface;

public class LogicPortGate extends GenericLogicInterfaceHandler {

	private LogicPortInterface port;
	
	public LogicPortGate(int maxInputs, WorkDispatcherInterface dispatcher, LogicPortInterface port) {
		super(maxInputs, dispatcher);
		this.port = port;
	}

	@Override
	public boolean isState() {
		return port.read();
	}
	
	@Override
	public void update(){
		//Can't write to an input
		if (port.isOutput()){
			//Sane Default if no inputs, then false.
			boolean output = false;
			// Make iterator of input list to access values
			Iterator<LogicConnection> itr = inputList.iterator();
			//if inputList has first item
			if (itr.hasNext()){
				//get state of first input
				output = itr.next().INEP.isState();
			}
			// write result to port
			port.write(output);
		}
	}
}

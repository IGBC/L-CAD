package io.lonelyrobot.igbc.lcad.simulation;

import java.util.Date;
import java.util.List;

import io.lonelyrobot.igbc.lcad.simulation.workers.WorkDispatcherInterface;

/**
 * Base implementation of {@link GenericLogicInterface} containing all the
 * connection management boilerplate.
 */
public abstract class GenericLogicInterfaceHandler implements GenericLogicInterface {
	protected List<LogicConnection> outputList;
	protected List<LogicConnection> inputList;

	protected final int maxInputs;
	
	protected final WorkDispatcherInterface dispatcher;

	public GenericLogicInterfaceHandler(int maxInputs, WorkDispatcherInterface dispatcher) {
		// set final fields in the class so the compiler stops shouting at us
		this.maxInputs = maxInputs;
		this.dispatcher = dispatcher;
		//anything else? No? Good.
		
		// For some reason the Lists don't need to be instantiated, so nothing to do there
		update();
	}

	@Override
	public void connect(LogicConnection connection) {
		// register this as a new output
		outputList.add(connection);	
		update();
	}

	@Override
	public void acceptConnection(LogicConnection connection) throws ConnectionfailedException {
		// if we have too many inputs already
		// and maxInputs is not a negative (reserved) value
		if ((inputList.size() >= maxInputs) && (maxInputs >= 0)) {
			// "Yea I'm not doing that"
			throw new ConnectionfailedException();
		}
		//register this as a new input
		inputList.add(connection);
		update();
	}

	@Override
	public void destroyConnection(LogicConnection connection) {
		inputList.remove(connection);
		outputList.remove(connection);
		update();
	}
	
	@Override
	public void update() {
		for (LogicConnection output: outputList) {
			//TODO: add propagation delays
			
			//Add job to update outputs now
			dispatcher.addJob(output.OUTEP, new Date());
		}
	}
}

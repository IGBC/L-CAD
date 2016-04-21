package io.lonelyrobot.igbc.lcad.simulation;

import java.util.List;

/**
 * Base implementation of {@link GenericLogicInterface} containing all the
 * connection management boilerplate.
 */
public class GenericLogicInterfaceHandler implements GenericLogicInterface {
	private List<LogicConnection> outputList;
	private List<LogicConnection> inputList;

	private final int maxInputs;

	public GenericLogicInterfaceHandler(int maxInputs) {
		// set final fields in the class so the compiler stops shouting at us
		this.maxInputs = maxInputs;
		//anything else? No? Good.
		
		// For some reason the Lists don't need to be instantiated, so nothing to do there
		
		
	}

	@Override
	public void connect(GenericLogicInterface outEP) {
		LogicConnection connection;
		try {
			connection = new LogicConnection(this, outEP);
		}
		catch (ConnectionfailedException e){
			//TODO: Log something or something, either way we failed
			
			//Stop here so we don't register the connection
			throw e;
		}
		
		// register this as a new output
		outputList.add(connection);		
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
	}

	@Override
	public void destroyConnection(LogicConnection connection) {
		if (inputList.contains(connection) || outputList.contains(connection)) {
			connection.destroy();
		}
		
	}
}

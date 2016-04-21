package io.lonelyrobot.igbc.lcad.simulation.gates;

import java.util.List;

import io.lonelyrobot.igbc.lcad.simulation.GenericLogicInterface;
import io.lonelyrobot.igbc.lcad.simulation.LogicConnection;

public class LogicGate implements GenericLogicInterface {

	private List<LogicConnection> outputList;
	private List<LogicConnection> inputList;
	
	@Override
	public void connect(GenericLogicInterface outEP) {
		LogicConnection connection;
		try {
			connection = new LogicConnection(this, outEP);
		}
		catch (ConnectionfailedException e){
			//TODO: Log something or something, either way we failed
			return;
		}
		outputList.add(connection);		
	}

	@Override
	public void acceptConnection(LogicConnection connection) throws ConnectionfailedException {
		// TODO Auto-generated method stub
		
	}
	
}

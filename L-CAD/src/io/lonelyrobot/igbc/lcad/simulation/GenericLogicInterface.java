package io.lonelyrobot.igbc.lcad.simulation;

public interface GenericLogicInterface {
	
	@SuppressWarnings("serial")
	class ConnectionfailedException extends RuntimeException {};
	
	
	void connect(GenericLogicInterface outEP);
	void acceptConnection(LogicConnection connection) throws ConnectionfailedException;
}

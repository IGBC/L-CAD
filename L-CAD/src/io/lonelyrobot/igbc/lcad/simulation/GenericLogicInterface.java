package io.lonelyrobot.igbc.lcad.simulation;

/**
 * Interface that defines the communication between logic objects and {@link LogicConnection}s
 */
public interface GenericLogicInterface {
	
	
	/**
	 * Internal Exception to signal a connection action failed.
	 */
	@SuppressWarnings("serial")
	class ConnectionfailedException extends RuntimeException {};
	
	
	void connect(GenericLogicInterface outEP);
	void acceptConnection(LogicConnection connection) throws ConnectionfailedException;
	void destroyConnection(LogicConnection connection);
}

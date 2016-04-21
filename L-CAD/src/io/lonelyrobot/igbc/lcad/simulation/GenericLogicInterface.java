package io.lonelyrobot.igbc.lcad.simulation;

/**
 * Interface that defines the communication between logic objects and {@link LogicConnection}s
 */
public interface GenericLogicInterface {
	
	
	/**
	 * Internal Exception to signal a connection action failed.
	 */
	@SuppressWarnings("serial")
	public class ConnectionfailedException extends RuntimeException {};
	
	/**
	 * Update method for signalling that an inputing gate's state has changed
	 */
	public void update();
	
	/**
	 * prototype getter for state. (Needed)
	 */
	public boolean isState();
	
	
	/**
	 * Initiate a connection from this node's output to another node's input
	 * @param outEP Node to connect to.
	 */
	public void connect(GenericLogicInterface outEP);
	/**
	 * attempts to accept connection started with {@link GenericLogicInterface.connect}  
	 * @param connection to accept
	 * @throws ConnectionfailedException if cannot accept connection (For example max inputs reached)
	 */
	public void acceptConnection(LogicConnection connection) throws ConnectionfailedException;
	/**
	 * WIP
	 * @param connection
	 */
	public void destroyConnection(LogicConnection connection);
}

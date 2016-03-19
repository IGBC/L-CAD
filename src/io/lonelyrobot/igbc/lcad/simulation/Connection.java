package io.lonelyrobot.igbc.lcad.simulation;

import java.util.UUID;

/**
 * Represents a link for a gate's output to a gate's input.
 * @author IGBC
 *
 */
public class Connection {
	/**
	 * Output Gate
	 */
	public final LogicGate parent;
	
	/**
	 * Input Gate
	 */
	public final LogicGate child;
	
	/**
	 * Gate ID
	 */
	public final UUID ID;
	
	public Connection(LogicGate parent, LogicGate child){
		// Store input values
		this.parent = parent;
		this.child = child;
		// Generate UUID to identify this connection.
		this.ID = UUID.randomUUID();
	}
}

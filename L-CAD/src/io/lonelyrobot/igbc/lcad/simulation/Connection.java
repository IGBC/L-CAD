package io.lonelyrobot.igbc.lcad.simulation;

import java.util.UUID;

/**
 * Represents a link for a gate's output to a gate's input.
 * 
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

	public Connection(LogicGate parent, LogicGate child) throws LogicGateException {
		// Generate UUID to identify this connection.
		this.ID = UUID.randomUUID();

		// Try to add this connection to the gates.
		try {
			parent.addParentConnection(this);
			child.addChildConnection(this);
			// Store input values
			this.parent = parent;
			this.child = child;

		} catch (LogicGateException e) {
			// Clean up the logic gates.
			parent.deleteConnection(this);
			child.deleteConnection(this);

			// Re throw.
			throw e;
		}

	}

	/**
	 * Destructor. Cleans Up references inside gates to this connection, making
	 * it ready for removal.
	 */
	public void dispose() {
		parent.deleteConnection(this);
		child.deleteConnection(this);
	}
}

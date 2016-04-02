package io.lonelyrobot.igbc.lcad.simulation;

import java.util.HashMap;
import java.util.UUID;

public class Simulation {

	/**
	 * stores all the gates in the simulation by UUID so they can be found
	 * Efficiently.
	 */
	private HashMap<UUID, LogicGate> gateList;

	/**
	 * stores all of the connections in the simulation by UUID
	 */
	private HashMap<UUID, Connection> connectionList;

	/**
	 * proceeds to next step of simulation. Current implementation does not use
	 * multi-threading.
	 */
	public void nextStep() {
		// For each gate compute the next state
		for (LogicGate gate : gateList.values()) {
			gate.compute();
		}
		// After Computation has finished all gates are ready to update

		// Update all the gates
		for (LogicGate gate : gateList.values()) {
			gate.update();
		}
	}

	/**
	 * Creates a new {@link #LogicGate} and adds it to the simulation from a
	 * {@link LogicGate#LogicGateType}. The function returns the gate's
	 * {@link #UUID}
	 * 
	 * @param type
	 *            {@link LogicGate#LogicGateType} Type of gate to generate.
	 * @return {@link UUID} of the gate created.
	 */
	public UUID addGate(LogicGate.LogicGateType type) {
		// create a new gate based on type (auto-factory call)
		LogicGate gate = LogicGate.build(type);
		gateList.put(gate.ID, gate);
		return gate.ID;
	}

	/**
	 * Removes {@link #LogicGate} from the simulation
	 * 
	 * @param ID
	 *            {@link #UUID} Identifier of gate to remove
	 */
	public void removeGate(UUID ID) {
		// Find the gate with the required ID and dispose of it
		gateList.get(ID).dispose();
		// Remove the gate from the gateList;
		gateList.remove(ID);
		// The gate should now have no references and be cleaned up.
	}

	/**
	 * Adds a new {@link #Connection} between two gates to the simulation.
	 * 
	 * @param output
	 *            {@link #UUID} of the output gate for the new connection.
	 * @param input
	 *            {@link #UUID} of the input gate for the new connection.
	 * @return {@link #UUID} of the connection created.
	 */
	public UUID addConnection(UUID output, UUID input) {
		Connection connection;
		try {
			connection = new Connection(gateList.get(output), gateList.get(input));
		} catch (LogicGateException e) {
			return null;
		}
		connectionList.put(connection.ID, connection);
		return connection.ID;
	}

	/**
	 * Removes {@link #Connection} between two gates from the simulation by ID.
	 * 
	 * @param ID
	 *            {@link #UUID} of the connection to be destroyed.
	 */
	public void removeConnection(UUID ID) {
		connectionList.get(ID).dispose();
		connectionList.remove(ID);
	}

	/**
	 * Singleton Pattern
	 */

	/**
	 * Erm... Singleton instance getter for {@link #Simulation} <br/>
	 * #ForeverAlone :(
	 * 
	 * @return instance of {@link #Simulation}
	 */
	public static Simulation instance() {
		if (simulation == null) {
			simulation = new Simulation();
		}
		return simulation;
	}

	private static Simulation simulation = null;

	private Simulation() {
		this.gateList = new HashMap<UUID, LogicGate>();
		this.connectionList = new HashMap<UUID, Connection>();
	}
}

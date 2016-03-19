package io.lonelyrobot.igbc.lcad.simulation;

import java.util.HashMap;
import java.util.UUID;

import io.lonelyrobot.igbc.lcad.simulation.LogicGateException.LogicGateExceptionTypes;

public class Simulation {

	/**
	 * stores all the gates in the simulation by UUID so they can be found
	 * Efficiently.
	 */
	private HashMap<UUID, LogicGate> gateList;

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
	 * @return {@link UUID}
	 */
	public UUID addGate(LogicGate.LogicGateType type) {
		// create a new gate based on type (auto-factory call)
		LogicGate gate = LogicGate.build(type);
		gateList.put(gate.ID, gate);
		return gate.ID;
	}

	/**
	 * Creates a logical connection between the output of parent and the input
	 * of parent. This function works with the gate's UUIDs.
	 * 
	 * @param parent
	 *            {@link #UUID} Gate to output from.
	 * @param child
	 *            {@link #UUID} Gate to input to.
	 * @throws LogicGateException
	 */
	public void addConnection(UUID parent, UUID child) throws LogicGateException {
		if ((gateList.get(parent) != null) && (gateList.get(child) != null)) {
			gateList.get(child).addParent(gateList.get(parent));
		} else {
			throw new LogicGateException(LogicGateExceptionTypes.UUID_NOT_FOUND);
		}
	}

	public Simulation() {
		// TODO Auto-generated constructor stub
	}
}

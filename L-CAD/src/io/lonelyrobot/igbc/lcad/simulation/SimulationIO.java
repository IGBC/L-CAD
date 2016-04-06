package io.lonelyrobot.igbc.lcad.simulation;

import java.util.UUID;

import lombok.Getter;

/**
 * Simulation virtual IO port, Attached to a gate, it offers an external hook
 * into the simulation.
 * 
 * @author IGBC
 *
 */
public class SimulationIO {
	/**
	 * Pin mode
	 */
	public final boolean input;
	public final UUID Gate;
	/* TODO: Store IO address */

	/**
	 * Local cache of the state of the gate it's attached to
	 */
	private @Getter boolean state;

	/**
	 * Syncs virtual IO port with logic gate.
	 * 
	 * @return
	 */
	public boolean update() {
		if (input) {
			/*
			 * Input gates call to the Virtual Port for their state so we just
			 * wait for that
			 */
		} else {
			/* else output */
			Simulation.instance().getGate(Gate).getOutput();
		}
		return state;
	}

	public SimulationIO(boolean isInput, UUID Gate) {
		this.input = isInput;
		this.Gate = Gate;
	}
}

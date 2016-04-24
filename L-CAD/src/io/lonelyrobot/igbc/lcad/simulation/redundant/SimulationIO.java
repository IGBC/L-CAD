package io.lonelyrobot.igbc.lcad.simulation.redundant;

import java.util.UUID;

/**
 * Simulation virtual IO port, Attached to a gate, it offers an external hook
 * into the simulation.
 * 
 * @author IGBC
 *
 */

@Deprecated
public class SimulationIO {
	/**
	 * Pin mode
	 */
	public final boolean input;
	
	/**
	 * Gate port is linked to
	 */
	public final UUID gate;
	
	/**
	 * Definition of outside connection.
	 */
	//public final IOPort address;

	/**
	 * Syncs virtual IO port with logic gate.
	 * 
	 * @return
	 */
	public boolean update() {
		boolean state = false; // or something, fuck this I'm about to branch and delete all this
		if (input) {
			/*
			 * Input gates call to the Virtual Port for their state so we just
			 * wait for that
			 */
		} else {
			/* else output */
			state = Simulation.instance().getGate(gate).isOutput();
			//address.write(state);
		}
		return state;
	}

	public SimulationIO(boolean isInput, UUID gate /*, IOPort address */ ) {
		this.input = isInput;
		this.gate = gate;
		//this.address = address;
	}
}

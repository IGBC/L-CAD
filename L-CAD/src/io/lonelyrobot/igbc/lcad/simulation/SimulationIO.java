package io.lonelyrobot.igbc.lcad.simulation;

/**
 * Simulation input - output data class.
 * @author IGBC
 *
 */
public class SimulationIO {
	public final boolean input;
	private boolean state;
	
	
	
	public SimulationIO(boolean isInput){
		this.input = isInput;
	}
}

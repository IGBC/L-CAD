package io.lonelyrobot.igbc.lcad.simulation.ports;

public interface LogicPortInterface {
	public boolean read();
	public void write(boolean value);
	
	public boolean isOutput();
}

package io.lonelyrobot.igbc.lcad.ports;

public interface IOPort {
	public void write(boolean val);
	public boolean read();
}

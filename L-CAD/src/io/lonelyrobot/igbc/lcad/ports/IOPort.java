package io.lonelyrobot.igbc.lcad.ports;

public abstract class IOPort {
	public abstract void write(boolean val);
	public abstract boolean read();
}

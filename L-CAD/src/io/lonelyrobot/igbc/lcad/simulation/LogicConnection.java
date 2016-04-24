package io.lonelyrobot.igbc.lcad.simulation;

import io.lonelyrobot.igbc.lcad.simulation.GenericLogicInterface.ConnectionfailedException;

public class LogicConnection {
	/**
	 * in point of connection (transmitter)
	 */
	public final GenericLogicInterface INEP;
	
	/**
	 * out point of connection (receiver)
	 */
	public final GenericLogicInterface OUTEP;

	/**
	 * Constructor - Makes a connection between INEP and OUTEP
	 * @param INEP {@link GenericLogicInterface} in point of connection (transmitter)
	 * @param OUTEP {@link GenericLogicInterface} out point of connection (receiver)
	 */
	public LogicConnection(GenericLogicInterface INEP, GenericLogicInterface OUTEP) {
		// Permanently store the connection endpoints in this class
		this.INEP = INEP;
		this.OUTEP = OUTEP;

		// Initialise the connection with the out endpoint
		try {
			OUTEP.acceptConnection(this);
		} catch (ConnectionfailedException e) {
			// on the condition that this failed there's not a lot that can be
			// done, other than to let this be garbage collected.

			// re-throw the exception, this will signal to the connection
			// initialiser that the connection failed.
			throw e;
		}
	}

	public void destroy() {
		INEP.destroyConnection(this);
		OUTEP.destroyConnection(this);
	}	
}
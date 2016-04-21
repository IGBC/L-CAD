package io.lonelyrobot.igbc.lcad.simulation.redundant;

/** 
 * Exception Class for Logic Gate, offering types for many common exceptions, allowing easier handling. 
 * */

@SuppressWarnings("serial")
public class LogicGateException extends Exception {
	
	/**
	 * Exception Type definitions.
	 * Should be defined in plain old English
	 */
	public static enum LogicGateExceptionTypes {UNKNOWN, MAX_INPUTS_EXEEDED, UUID_NOT_FOUND};
	
	public final LogicGateExceptionTypes type;
	
	/**
	 * Returns if exception type is unknown to allow quick re-raising.
	 */
	public boolean isUnknown() { return (this.type == LogicGateExceptionTypes.UNKNOWN); };
	
	
	/**
	 * 8 flavours of constructor.
	 * Now with 14 'Erbs and Spices.
	 */
	
	public LogicGateException() {
		super();
		this.type = LogicGateExceptionTypes.UNKNOWN;
	}

	public LogicGateException(String message) {
		super(message);
		this.type = LogicGateExceptionTypes.UNKNOWN;
	}

	public LogicGateException(Throwable cause) {
		super(cause);
		this.type = LogicGateExceptionTypes.UNKNOWN;
	}

	public LogicGateException(String message, Throwable cause) {
		super(message, cause);
		this.type = LogicGateExceptionTypes.UNKNOWN;
	}

	public LogicGateException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
		super(message, cause, enableSuppression, writableStackTrace);
		this.type = LogicGateExceptionTypes.UNKNOWN;
	}
	
	public LogicGateException(LogicGateExceptionTypes type) {
		super();
		this.type = type;
	}

	public LogicGateException(String message, LogicGateExceptionTypes type) {
		super(message);
		this.type = type;
	}

	public LogicGateException(LogicGateExceptionTypes type, Throwable cause) {
		super(cause);
		this.type = type;
	}

	public LogicGateException(String message, LogicGateExceptionTypes type, Throwable cause) {
		super(message, cause);
		this.type = type;
	}

	public LogicGateException(String message, LogicGateExceptionTypes type, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
		super(message, cause, enableSuppression, writableStackTrace);
		this.type = type;
	}

}

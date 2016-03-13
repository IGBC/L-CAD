package io.lonelyrobot.igbc.gatesim.simulation;

import java.util.Iterator;
import java.util.List;

import io.lonelyrobot.igbc.gatesim.simulation.LogicGateException.LogicGateExceptionTypes;

public class LogicGate {
	
	static enum LogicGateType { AND, NAND, OR, NOR, NOT, OUTPUT, INPUT };
	
	public final LogicGateType type;
	private boolean inputModeAND;
	private boolean inputModeNOT;
	
	public final int maxInputs;
	public final int minInputs;
	
	private List<LogicGate> parents;
	
	private boolean output;
	public boolean getOutput() { return this.output; };
	private boolean inputsAND;
	private boolean inputsOR;
	
	public void update() {
		Iterator<LogicGate> itr = parents.iterator();
		this.inputsAND = itr.next().getOutput();
		this.inputsOR = this.inputsAND;
		while (itr.hasNext()) {
			boolean b = itr.next().getOutput();
			this.inputsOR = this.inputsOR | b;
			this.inputsAND = this.inputsAND & b;
		}
		if (inputModeAND) {
			this.output = this.inputsAND;
		}
		else {
			this.output = this.inputsOR;
		}
		
		if (inputModeNOT) {
			this.output = !this.output;
		}
		
	}
	
	public void addParent(LogicGate _new) throws LogicGateException {
		if (this.parents.size() > maxInputs) {
			this.parents.add(_new);
		}
		else {
			throw new LogicGateException(LogicGateExceptionTypes.MAX_INPUTS_EXEEDED);
		}
	}
	
	public LogicGate(LogicGateType type) {
		this.type = type;
		switch (type) {
		case NOT:
		case OUTPUT:
			this.maxInputs = 1;
			this.minInputs = 1;
			break;
		case INPUT:
			this.maxInputs = 0;
			this.minInputs = 0;
			break;
		case AND:
		case NAND:
		case OR:
		case NOR:
		default:
			this.maxInputs = -1;
			this.minInputs = 2;
			break;
		}
	}
}

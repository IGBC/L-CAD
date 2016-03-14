package io.lonelyrobot.igbc.gatesim.simulation;

import java.util.Iterator;
import java.util.List;
import java.util.UUID;

import io.lonelyrobot.igbc.gatesim.simulation.LogicGateException.LogicGateExceptionTypes;
import lombok.Getter;

public class LogicGate {
	
	/** Static Functions and Fields for a auto-factory pattern */
	public static enum LogicGateType { AND, NAND, OR, NOR, NOT, OUTPUT, INPUT };
	
	public static LogicGate build(LogicGateType type) throws Exception {
		
		// Sane defaults
		int maxInputs = -1;
		LogicGateInputMode inputMode;
		boolean inputNegate = false;
		
		// Set input mode and max inputs based on type
		switch(type) {
		case AND:
		case NAND:
			inputMode = LogicGateInputMode.AND; 
			break;
		case OR:
		case NOR:
			inputMode = LogicGateInputMode.OR; 
			break;
		case NOT:
		case OUTPUT:
			inputMode = LogicGateInputMode.UNITY;
			maxInputs = 1;
			break;
		case INPUT:
			inputMode = LogicGateInputMode.EXT;
			maxInputs = 0;
			break;
		//This will only happen if someone adds a new type and forgets to program it in.
		default:
			throw new Exception("Unprogrammed gate type");
		}
		
		// Set negation mode
		switch(type) {
		// All 'N' Types 
		case NAND:
		case NOR:
		case NOT:
			inputNegate = true;
		default:
			break;
		}
		return new LogicGate(maxInputs, inputMode, inputNegate);
	}
	 
	//! End Of Factory
	
	/** 
	 * Definitions of all the logic gate types and input modes,
	 * There is some data duplication here, but that can be optimised out later.*/
	
	static enum LogicGateInputMode { AND, OR, XOR, UNITY, RAND, EXT };
	
	/**
	 * Storage for enums above, plus output negation flag */
	//public final LogicGateType type;
	public final LogicGateInputMode inputMode;
	public final boolean inputNegate;
	public final UUID ID;
	
	
	// Gate Input Limit
	public final int maxInputs;
	
	// List for storing input gates.
	private List<LogicGate> parents;
	
	//
	private @Getter boolean output; //Defines output state for the current step
	private boolean outputDelta; //Defines temporary output storage for current next step
	
	/**
	 * Computes output of gate for next step of the logic engine. 
	 */
	public void compute() {
		// Default output case
		boolean a = false;
		switch(this.inputMode) {
		case AND:
		case OR:
		case XOR:
			// For AND, OR, and XOR gates
			
			// Generate an iterator that can search the inputs. 
			Iterator<LogicGate> itr = parents.iterator();
			
			// If we have a first input load it into a
			if (itr.hasNext()) {
				a = itr.next().isOutput(); 
			}
			// For each remaining input perform the logic function against it. 
			while (itr.hasNext()) {
				boolean b = itr.next().isOutput();
				switch(this.inputMode) {
				case OR:
					a = a | b;
					break;
				case XOR:
					a = a ^ b;
					break;
				case AND:
				default:
					a = a & b;
					break;
				}
			}
			break;
		case EXT:
			// TODO: raise a call to the simulation
			break;
		case RAND:
			// For a random input gate (more of an easter egg)
			a = SimulationUtils.simRandom.nextBoolean();
			break;
		case UNITY:
			// For single input buffer / not gates
			// Take first input and ignore the rest
			if (parents.size() > 0) {
				a = parents.get(0).isOutput();
			}
			break;
		}
		
		// Handle not types
		if (inputNegate) {
			a = !a;
		}
		
		//write a into the output delta
		a = outputDelta;
	}
	
	public void update() {
		//Move new output into output field
		output = outputDelta;
	}
	
	public void addParent(LogicGate _new) throws LogicGateException {
		if (this.parents.size() > maxInputs) {
			this.parents.add(_new);
		}
		else {
			throw new LogicGateException(LogicGateExceptionTypes.MAX_INPUTS_EXEEDED);
		}
	}
	
	public LogicGate(int maxInputs, LogicGateInputMode inputMode, boolean inputNegate) {
		this.maxInputs = maxInputs;
		this.inputMode = inputMode;
		this.inputNegate = inputNegate;
		this.ID = UUID.randomUUID();
	}
}
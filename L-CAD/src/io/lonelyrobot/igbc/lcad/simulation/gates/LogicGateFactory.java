package io.lonelyrobot.igbc.lcad.simulation.gates;

import io.lonelyrobot.igbc.lcad.simulation.gates.LogicGate;
import io.lonelyrobot.igbc.lcad.simulation.gates.LogicGate.LogicGateInputMode;
import io.lonelyrobot.igbc.lcad.simulation.workers.WorkDispatcherInterface;

public class LogicGateFactory {
	
	/**
	 * Defines standard sane types for commonly needed logic gates. These types
	 * are <b>only</b> for use with the {@link #build()} function. Other usage
	 * violates the EULA!
	 */
	public static enum LogicGateType {
		AND, NAND, OR, NOR, NOT, XOR, XNOR,
	}
	
	/**
	 * Reference to work dispatcher to be given to logic gates
	 */
	private WorkDispatcherInterface dispatcher;
	
	public LogicGateFactory(WorkDispatcherInterface dispatcher) {
		this.dispatcher = dispatcher;	
	}
	
	/**
	 * Builds a {@link #LogicGate} from a {@link #LogicGateType}. This allows
	 * easy construction of commonly needed gate types. For anything more
	 * complicated use the constructor.
	 * 
	 * @param type
	 *            {@link #LogicGateType} Indicates gate type to build.
	 * @return new {@link #LogicGate}
	 * @throws Exception
	 */
	public LogicGate buildGate(LogicGateType type){
		// Sane defaults
		int maxInputs = -1;
		LogicGateInputMode inputMode;
		boolean inputNegate = false;

		// Set input mode and max inputs based on type
		switch (type) {
		case NAND:
			inputNegate = true;
		case AND:
			inputMode = LogicGateInputMode.AND;
			break;
		case NOR:
			inputNegate = true;
		case OR:
			inputMode = LogicGateInputMode.OR;
			break;
		case XNOR:
			inputNegate = true;
		case XOR:
			inputMode = LogicGateInputMode.XOR;
			maxInputs = 2;
			break;
		case NOT:
			inputNegate = true;
			inputMode = LogicGateInputMode.UNITY;
			maxInputs = 1;
			break;
		// This will only happen if someone adds a new type and forgets to
		// program it in.
		default:
			// Be an AND.
			inputMode = LogicGateInputMode.AND;
			break;
		}
		return new LogicGate(maxInputs, dispatcher, inputMode, inputNegate);
	}
}
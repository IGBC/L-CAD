package io.lonelyrobot.igbc.gatesim.simulation;

import java.util.Iterator;
import java.util.List;
import java.util.UUID;

import io.lonelyrobot.igbc.gatesim.simulation.LogicGateException.LogicGateExceptionTypes;
import lombok.Getter;

public class LogicGate {

	/*
	 * Static Functions and Fields for a auto-factory pattern
	 */

	/**
	 * Defines standard sane types for commonly needed logic gates. These types
	 * are <b>only</b> for use with the {@link #build()} function. Other usage
	 * violates the EULA!
	 */
	public static enum LogicGateType {
		AND, NAND, OR, NOR, NOT, OUTPUT, INPUT
	};

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
	public static LogicGate build(LogicGateType type) throws Exception {
		// Sane defaults
		int maxInputs = -1;
		LogicGateInputMode inputMode;
		boolean inputNegate = false;

		// Set input mode and max inputs based on type
		switch (type) {
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
		// This will only happen if someone adds a new type and forgets to
		// program it in.
		default:
			throw new Exception("Unprogrammed gate type");
		}

		// Set negation mode
		switch (type) {
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

	/* ! End Of Factory */

	/*
	 * Definitions of all the logic gate types and input modes, There is some
	 * data duplication here, but that can be optimised out later.
	 */

	/**
	 * <b>Defines Operation to perform on gate inputs: <br/>
	 * AND, OR:</b> Standard implementation<br/>
	 * <b>XOR:</b> Unusual implementation supporting N inputs, will behave
	 * weirdly for more than 2 or 3 (TODO: Fix this)<br/>
	 * <b>UNITY:</b> Takes first input and ignores the rest<br/>
	 * <b>EXT:</b> Asks the {@link #Simulation} for an external input
	 * 
	 */
	public static enum LogicGateInputMode {
		AND, OR, XOR, UNITY, EXT, RAND
		// RAND is an Undocumented Easter egg
	};

	/* Gate Configuration Fields */

	/**
	 * Defines operation to perform in gate inputs
	 */
	public final LogicGateInputMode inputMode;
	/**
	 * Defines whether or not to negate the result of the output computation.
	 */
	public final boolean inputNegate;
	/**
	 * Unique identifier for the gate.
	 */
	public final UUID ID;
	/**
	 * Maximum number of inputs that can be sanely connected to the logic gate.
	 * <br/>
	 * A value of -1 indicates no limit.
	 */
	public final int maxInputs;

	/* Runtime Fields */

	/**
	 * Defines a list of the gates connected to the inputs of this gate, This
	 * defines the connections that form the gate graph.
	 */
	private List<LogicGate> parents;

	/**
	 * Defines the output state of the gate during the current computation step.
	 * This value remains unchanging for the duration of the step making it safe
	 * to access repeatedly during the computation of the next step. This value
	 * will not be updated until {@link #update()} is called.
	 */
	private @Getter boolean output;
	/**
	 * Stores the result of {@link #compute()} temporarily until the step is
	 * incremented with {@link #update()}
	 */
	private boolean outputDelta;

	/**
	 * Computes output of gate for next step of the simulation and saves it into
	 * {@link #outputDelta}
	 */
	public void compute() {
		// Default output case
		boolean a = false;
		switch (this.inputMode) {
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
				switch (this.inputMode) {
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

		// write a into the output delta
		a = outputDelta;
	}

	/**
	 * moves {@link #outputDelta} into {@link #output} for use in the next step.
	 */
	public void update() {
		// Move new output into output field
		output = outputDelta;
	}

	/**
	 * Adds a new parent to the {@link #parents} list, on the condition that
	 * {@link #maxInputs} is not already exceeded.
	 * 
	 * @param _new
	 *            {@link #LogicGate} Handle of gate to add
	 * @throws LogicGateException
	 */
	public void addParent(LogicGate _new) throws LogicGateException {
		if (this.parents.size() > maxInputs) {
			this.parents.add(_new);
		} else {
			throw new LogicGateException(LogicGateExceptionTypes.MAX_INPUTS_EXEEDED);
		}
	}

	/**
	 * Standard Constructor.
	 * 
	 * @param maxInputs
	 *            {@link #Integer} Defines the maximum amount of input
	 *            connections to the gate.
	 * @param inputMode
	 *            {@link #LogicGateInputMode} Defines the operation to perform
	 *            on the inputs of the gate.
	 * @param inputNegate
	 *            {@link #Boolean} Specifies if to invert the result of the
	 *            input computation.
	 */
	public LogicGate(int maxInputs, LogicGateInputMode inputMode, boolean inputNegate) {
		this.maxInputs = maxInputs;
		this.inputMode = inputMode;
		this.inputNegate = inputNegate;
		this.ID = UUID.randomUUID();
	}
}
package io.lonelyrobot.igbc.lcad.simulation.redundant;

import java.util.HashMap;
import java.util.Iterator;
import java.util.UUID;

import io.lonelyrobot.igbc.lcad.simulation.redundant.LogicGateException.LogicGateExceptionTypes;
import lombok.Getter;

/**
 * Represents a logic gate in the simulation.
 * 
 * @author IGBC
 *
 */
@Deprecated
public class LogicGate {
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

	/* Class Fields */

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
	 * Defines a list of the connections to the inputs of this gate.
	 */
	private HashMap<UUID, Connection> parents;

	/**
	 * Defines a list of the connections to the output of this gate.
	 */
	private HashMap<UUID, Connection> children;

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
	 * Auto-Factory Pattern methods and fields. An auto-factory is a factory
	 * pattern baked into the class that it creates.
	 */

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
	public static LogicGate build(LogicGateType type) {
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
			// Be an AND.
			inputMode = LogicGateInputMode.AND;
			break;
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

	// ***Graph Management Functions***

	/**
	 * Adds a {@link #Connection} to an input of the gate.
	 * 
	 * @param connection
	 *            {@link #Connection} to add.
	 * @throws {@link
	 *             #LogicGateException} if maximum number of inputs is exceeded.
	 */
	public void addParentConnection(Connection connection) throws LogicGateException {
		if (parents.size() < maxInputs) {
			parents.put(connection.ID, connection);
		} else {
			throw new LogicGateException(LogicGateExceptionTypes.MAX_INPUTS_EXEEDED);
		}
	}

	/**
	 * Adds a {@link #Connection} to the output of the gate.
	 * 
	 * @param connection
	 *            {@link #Connection} to add.
	 */
	public void addChildConnection(Connection connection) {
		children.put(connection.ID, connection);
	}

	/**
	 * Removes a {@link #Connection} from the gate entirely.
	 * 
	 * @param connection
	 *            {@link #Connection} to delete.
	 */
	public void deleteConnection(Connection connection) {
		parents.remove(connection.ID);
		children.remove(connection.ID);
	}

	// ***Computation Functions***

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
			Iterator<Connection> itr = parents.values().iterator();

			// If we have a first input load it into a
			if (itr.hasNext()) {
				a = itr.next().parent.isOutput();
			}
			// For each remaining input perform the logic function against it.
			while (itr.hasNext()) {
				boolean b = itr.next().parent.isOutput();
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
			Simulation.instance().getInput(this.ID);
			break;
		case RAND:
			// For a random input gate (more of an easter egg)
			a = SimulationUtils.simRandom.nextBoolean();
			break;
		case UNITY:
			// For single input buffer / not gates
			// Take first input and ignore the rest
			if (parents.size() > 0) {
				a = parents.get(0).parent.isOutput();
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

	// ***CONSTRUCTOR***

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
		this.parents = new HashMap<UUID, Connection>();
		this.children = new HashMap<UUID, Connection>();
	}

	/**
	 * Destructor. Cleans Up connections to and from this gate, making it ready
	 * for removal.
	 */
	public void dispose() {
		// These have to call up to the simulation level so that the connections
		// ...are dereferenced in the simulation global maps
		for (Connection connection : parents.values()) {
			Simulation.instance().removeConnection(connection.ID);
		}
		for (Connection connection : children.values()) {
			Simulation.instance().removeConnection(connection.ID);
		}
	}
}
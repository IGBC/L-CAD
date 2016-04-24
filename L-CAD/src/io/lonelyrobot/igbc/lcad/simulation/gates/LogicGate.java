package io.lonelyrobot.igbc.lcad.simulation.gates;

import java.util.Iterator;
import java.util.Random;

import io.lonelyrobot.igbc.lcad.simulation.GenericLogicInterfaceHandler;
import io.lonelyrobot.igbc.lcad.simulation.LogicConnection;
import io.lonelyrobot.igbc.lcad.simulation.workers.WorkDispatcher;
import lombok.Getter;

public class LogicGate extends GenericLogicInterfaceHandler {

	/**
	 * <b>Defines Operation to perform on gate inputs: <br/>
	 * AND, OR:</b> Standard implementation<br/>
	 * <b>XOR:</b> Unusual implementation supporting N inputs, will behave
	 * weirdly for more than 2 or 3 (TODO: Fix this)<br/>
	 * <b>UNITY:</b> Takes first input and ignores the rest<br/>
	 * 
	 */
	public static enum LogicGateInputMode {
		AND, OR, XOR, UNITY, RAND
		// RAND is an Undocumented Easter egg
	};
	
	/**
	 * Defines operation to perform in gate inputs
	 */
	public final LogicGateInputMode inputMode;
	
	/**
	 * Defines whether or not to negate the result of the output computation.
	 */
	public final boolean inputNegate;
	
	/**
	 * Defines the output state of the gate during the current computation step.
	 * This value remains unchanging for the duration of the step making it safe
	 * to access repeatedly during the computation of the next step. This value
	 * will not be updated until {@link #update()} is called.
	 */
	private @Getter boolean state;	
	
	public LogicGate(int maxInputs, WorkDispatcher dispatcher, LogicGateInputMode inputMode, boolean inputNegate) {
		super(maxInputs, dispatcher);
		this.inputMode = inputMode;
		this.inputNegate = inputNegate;
		update();
	}

	//TODO: Not make this behave really weird
	@Override
	public void update() {
		// Default output case
		boolean a = false;
		switch (this.inputMode) {
		case AND:
		case OR:
		case XOR:
			// For AND, OR, and XOR gates

			// Generate an iterator that can search the inputs.
			Iterator<LogicConnection> itr = inputList.iterator();

			// If we have a first input load it into a
			if (itr.hasNext()) {
				a = itr.next().INEP.isState();
			}
			// For each remaining input perform the logic function against it.
			while (itr.hasNext()) {
				boolean b = itr.next().INEP.isState();
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
		case RAND:
			// For a random input gate (more of an easter egg)
			a = new Random().nextBoolean();
			break;
		case UNITY:
			// For single input buffer / not gates
			// Take first input and ignore the rest
			if (inputList.size() > 0) {
				a = inputList.get(0).INEP.isState();
			}
			break;
		}

		// Handle not types
		if (inputNegate) {
			a = !a;
		}

		// write a into the state
		state = a;
		//TODO, write the next update into the work queue
	}
}
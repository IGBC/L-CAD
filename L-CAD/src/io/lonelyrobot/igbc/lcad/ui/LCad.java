package io.lonelyrobot.igbc.lcad.ui;

import java.util.UUID;

import io.lonelyrobot.igbc.lcad.simulation.LogicGate.LogicGateType;
import io.lonelyrobot.igbc.lcad.simulation.Simulation;
import lombok.Getter;

public class LCad {

	private @Getter Simulation sim;
	
	/**
	 * Constructor
	 */
	public LCad() {
		this.sim = Simulation.instance();
	}

	public static void main(String[] args) {
		System.out.println("----------L-CAD Text testing console---------");
		System.out.println("---Writing tests is boring so we have this---");
		System.out.println("");
		LCad cad = new LCad();
		System.out.println("Created LCAD Object");
		UUID in = cad.getSim().addGate(LogicGateType.INPUT);
		UUID out = cad.getSim().addGate(LogicGateType.OUTPUT);
		System.out.println("Created Logic gates");
		cad.getSim().addConnection(in, out);
		System.out.println("Connected gates");
		cad.getSim().nextStep();
		System.out.println("Stepped Simulation.");
	}

}

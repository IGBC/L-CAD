package io.lonelyrobot.igbc.lcad.simulation;

import java.util.HashMap;
import java.util.UUID;

import io.lonelyrobot.igbc.lcad.simulation.GenericLogicInterface.ConnectionfailedException;


public class Simulation {
	/**
	 * Storage spot for all objects in the graph that implement a GLI (nodes).
	 */
	private HashMap<UUID,GenericLogicInterface> nodeList = new HashMap<>();
	
	/**
	 * Storage spot for all connections (edges) in the graph.
	 */
	private HashMap<UUID,LogicConnection> edgeList = new HashMap<>();
	
	public UUID newConnection(GenericLogicInterface inEP, GenericLogicInterface outEP){
		LogicConnection connection;
		try {
			connection = new LogicConnection(inEP, outEP);
		}
		catch (ConnectionfailedException e){
			//TODO: Log something or something, either way we failed
			
			//Stop here so we don't register the connection
			throw e;
		}
		inEP.connect(connection);
		UUID ID = UUID.randomUUID();
		edgeList.put(ID, connection);
		return ID;
	}
	
	public Simulation() {
		//// TODO Auto-generated constructor stub
	}
}

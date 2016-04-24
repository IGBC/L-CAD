package io.lonelyrobot.igbc.lcad.simulation.workers;

import java.util.Date;

import io.lonelyrobot.igbc.lcad.simulation.GenericLogicInterface;

public class WorkDispatcher extends Thread implements WorkDispatcherInterface {

	@Override
	public void addJob(GenericLogicInterface toBeUpdated, Date dateTime) {
		// TODO Auto-generated method stub

	}
	
	@Override 
	public void run() {
		while (true){
			break;
		}
	}
	
	public WorkDispatcher(){
		//TODO: any setup.
		
		//Start the thread
		start();
	}
}

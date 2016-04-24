package io.lonelyrobot.igbc.lcad.simulation.workers;

import java.util.Date;
import io.lonelyrobot.igbc.lcad.simulation.GenericLogicInterface;

public interface WorkDispatcherInterface {
	public void addJob(GenericLogicInterface toBeUpdated, Date dateTime);
	public void stop();
}

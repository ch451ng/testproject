package seiot.modulo_lab_3_3.devices;

import seiot.modulo_lab_3_3.common.*;

public class Tick implements Event {
	
	private long time;
	
	public Tick(long time ){
		this.time = time;
	}
	
	public long getTime(){
		return time;
	}
}

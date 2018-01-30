package seiot.modulo_lab_3_3.devices;

import seiot.modulo_lab_3_3.common.*;

public class ObjDetected implements Event {
	private ProximitySensor source;
	private double distance;
	
	public ObjDetected(ProximitySensor source, double distance){
		this.source = source;
		this.distance = distance;
	}
	
	public ProximitySensor getSource(){
		return source;
	}
	
	public double getDistance(){
		return distance;
	}
}

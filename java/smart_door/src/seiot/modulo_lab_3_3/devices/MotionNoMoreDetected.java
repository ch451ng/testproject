package seiot.modulo_lab_3_3.devices;

import seiot.modulo_lab_3_3.common.*;

public class MotionNoMoreDetected implements Event {
	private ObservableMotionDetectorSensor source;
	
	public MotionNoMoreDetected(ObservableMotionDetectorSensor source){
		this.source = source;
	}
	
	public ObservableMotionDetectorSensor getSource(){
		return source;
	}
}

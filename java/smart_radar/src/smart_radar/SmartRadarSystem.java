package smart_radar;

import seiot.modulo_lab_3_3.common.MsgEvent;
import seiot.modulo_lab_3_3.devices.*;



public class SmartRadarSystem {
	public static void main(String[] args) {
		Counters counters = new Counters();
		
		Light ledA = new seiot.modulo_lab_3_3.devices.emu.Led(4,"ON");
		Light ledB = new seiot.modulo_lab_3_3.devices.emu.Led(5,"DETECT");
		Light ledC = new seiot.modulo_lab_3_3.devices.emu.Led(6,"TRACK");
		
//		Light ledA = new seiot.modulo_lab_3_3.devices.p4j_impl.Led(3); //on
//		Light ledB = new seiot.modulo_lab_3_3.devices.p4j_impl.Led(4); //detect
//		Light ledC = new seiot.modulo_lab_3_3.devices.p4j_impl.Led(5); //track
		
		
		ObservableButton stopButton = new seiot.modulo_lab_3_3.devices.emu.ObservableButton(7);
		ObservableButton startButton = new seiot.modulo_lab_3_3.devices.emu.ObservableButton(8);
		
//		ObservableButton stopButton = new seiot.modulo_lab_3_3.devices.p4j_impl.Button(1);
//		ObservableButton startButton = new seiot.modulo_lab_3_3.devices.p4j_impl.Button(0);
		
		
		Serial inputDev = null;
		try {
			//inputDev = new SerialImpl("/dev/ttyACM0", 9600); //RASPBERRY
			inputDev = new SerialImpl("COM3", 9600); //PC
			//inputDev = new seiot.modulo_lab_3_3.devices.emu.SerialImpl(9,10); //EMU
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		RadarController controller = new RadarController();
		controller.init(counters, ledA, ledB, ledC, startButton, stopButton, inputDev);
		controller.start();
		
		InputMsgReceiver rec = new InputMsgReceiver(controller,inputDev);
		rec.start();
				
	}

}




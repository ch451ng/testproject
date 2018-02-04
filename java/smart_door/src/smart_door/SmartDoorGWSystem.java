package smart_door;

import seiot.modulo_lab_3_3.common.MsgEvent;
import seiot.modulo_lab_3_3.devices.*;
import servers.*;


public class SmartDoorGWSystem {
	public static void main(String[] args) {
		
		
		Light ledA = new seiot.modulo_lab_3_3.devices.emu.Led(4,"ON");
		Light ledB = new seiot.modulo_lab_3_3.devices.emu.Led(5,"DETECT");
		
//		Light ledA = new seiot.modulo_lab_3_3.devices.p4j_impl.Led(3); //on
//		Light ledB = new seiot.modulo_lab_3_3.devices.p4j_impl.Led(4); //detect
	
		
		
		Serial inputDev = null;
		try {
			//inputDev = new SerialImpl("/dev/ttyACM0", 9600); //RASPBERRY
			inputDev = new SerialImpl("COM3", 9600); //PC
			//inputDev = new seiot.modulo_lab_3_3.devices.emu.SerialImpl(9,10); //EMU
		} catch (Exception e) {
			e.printStackTrace();
		}
		
//		RadarController controller = new RadarController();
//		controller.init(counters, ledA, ledB, ledC, startButton, stopButton, inputDev);
//		controller.start();
		DBUpdater dbUpdater = new DBUpdater();
		LoginChecker loginChecker = new LoginChecker();
		dbUpdater.start();
		InputMsgReceiver rec = new InputMsgReceiver(dbUpdater,loginChecker,inputDev);
		rec.start();
				
	}

}




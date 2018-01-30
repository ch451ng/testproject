package servers;

import seiot.modulo_lab_3_3.devices.Serial;
import smart_door.SerialImpl;

public class server {
	public static void main(String[] args) {
		
		Serial inputDev = null;
		try {
			//inputDev = new SerialImpl("/dev/ttyACM0", 9600); //RASPBERRY
			inputDev = new SerialImpl("COM3", 9600); //PC
			//inputDev = new seiot.modulo_lab_3_3.devices.emu.SerialImpl(9,10); //EMU
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		MultiThreadedServer server = new MultiThreadedServer(9000,inputDev);
		new Thread(server).start();

		try {
		    Thread.sleep(20 * 1000);
		} catch (InterruptedException e) {
		    e.printStackTrace();
		}
		System.out.println("Stopping Server");
		server.stop();
	}
}

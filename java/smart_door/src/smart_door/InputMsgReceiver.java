package smart_door;

import seiot.modulo_lab_3_3.common.*;
import seiot.modulo_lab_3_3.devices.*;
//import seiot.modulo_lab_3_3.pingpong2.PingMsg;

public class InputMsgReceiver extends ReactiveAgent {

	static private double MIN_DIST = 0.05;   //Distanza di tracking
	static private double MIN_DETECT = 0.20; //Orizzonte, distanza sopra la quale si ignorano gli oggetti

	private DBUpdater databaseUpdater;
	private LoginChecker loginChecker;
	private RadarController controller;
	private Serial serialDevice;
	private double dist;
	private int ang;
	private Boolean showCounter = true; //Serve per stampare solo una volta i contatori degli oggetti
	private int countD = 0; // Contatori utilizzati per filtrare eventi spuri
	private int countT = 0;
	private double currDist = 50;
	private int currAng = 360;

	public InputMsgReceiver(RadarController controller, Serial serialDevice) {
		this.controller = controller;
		this.serialDevice = serialDevice;
	}

	@Override
	public void run() {
		while (true) {
			try {
				String msg = serialDevice.waitForMsg(); //Attesa di un evento messaggio sulla seriale
				if (msg.startsWith("UT:")) { //Parsing del messaggio (estendere con regex)
				} else {
					if (msg.startsWith("UI:")) {
						
					} else {
						if (msg.startsWith("LR:")) {
							
						} else {
							if (msg.startsWith("TO:")) {
								
							}
						}
							
					}
				}
			} catch (Exception ex) {
				ex.printStackTrace();
			}
		}
	}

	@Override
	protected void processEvent(Event ev) {

	}

}

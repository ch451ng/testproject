package smart_door;

import seiot.modulo_lab_3_3.common.*;
import seiot.modulo_lab_3_3.devices.*;

public class InputMsgReceiver extends ReactiveAgent {

	static private double MIN_DIST = 0.05;   //Distanza di tracking
	static private double MIN_DETECT = 0.20; //Orizzonte, distanza sopra la quale si ignorano gli oggetti

	private DBUpdater databaseUpdater;
	private LoginChecker loginChecker;
	
	private Serial serialDevice;
	private int temp;
	private int lumen;
	private Boolean showCounter = true; //Serve per stampare solo una volta i contatori degli oggetti
	private int countD = 0; // Contatori utilizzati per filtrare eventi spuri
	private int countT = 0;
	private double currDist = 50;
	private int currAng = 360;

	public InputMsgReceiver(DBUpdater databaseUpdater, LoginChecker loginChecker, Serial serialDevice) {
		this.databaseUpdater = databaseUpdater;
		this.loginChecker = loginChecker;
		this.serialDevice = serialDevice;
	}

	@Override
	public void run() {
		while (true) {
			try {
				String msg = serialDevice.waitForMsg(); //Attesa di un evento messaggio sulla seriale
				if (msg.startsWith("UT:")) { //Update temperature
					temp = Integer.parseInt(msg.replace("UT:", ""));
					sendMsgTo(databaseUpdater, new UpdateTemp(temp));
					System.out.println("UpdateTemp");
				} else {
					if (msg.startsWith("UI:")) { //Update Intensity
						lumen = Integer.parseInt(msg.replace("UI:", ""));
						sendMsgTo(databaseUpdater, new UpdateTemp(lumen));
						System.out.println("UpdateInt");

					} else {
						if (msg.startsWith("LR:")) { //Login Request
							
						} else {
							if (msg.startsWith("TO:")) { //Login Timeout
								
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

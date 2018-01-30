package smart_radar;

import seiot.modulo_lab_3_3.common.*;
import seiot.modulo_lab_3_3.devices.*;
//import seiot.modulo_lab_3_3.pingpong2.PingMsg;

public class InputMsgReceiver extends ReactiveAgent {

	static private double MIN_DIST = 0.05;   //Distanza di tracking
	static private double MIN_DETECT = 0.20; //Orizzonte, distanza sopra la quale si ignorano gli oggetti

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
				if (msg.contains("D:") && msg.contains("A:")) { //Parsing del messaggio (estendere con regex)
					int indD = msg.indexOf("D:");
					int indA = msg.indexOf("A:");
					if (indA > 0 && indD >= 0) {
						dist = Double.parseDouble(msg.substring(indD + 2, indA)); //Estrae la distanza
						ang = Integer.parseInt(msg.substring(indA + 2)); //Estrae l'angolo
						if (dist <= MIN_DIST) { //TRACKING
							countD = 0;
							if (countT == 2 && (currDist != dist || currAng != ang)) { //Si genera un evento solo se ce ne sono stati 2 consecutivi
								sendMsgTo(controller, new TrackMsg(dist, ang));
								currDist = dist;
								currAng = ang;
								countT = 0;
							} else {
								countT++;
							}
						} else if (dist <= MIN_DETECT) { //DETECTING
							countT = 0;
							if (countD == 2 && (currDist != dist || currAng != ang)) { //Si genera un evento solo se ce ne sono stati 2 consecutivi
								sendMsgTo(controller, new DetectMsg(ang));
								currDist = dist;
								currAng = ang;
								countD = 0;
							} else {
								countD++;
							}
						} else {
							sendMsgTo(controller, new ScanMsg(dist, ang));
							countT = 0;
							countD = 0;
						}
						if (ang == 0 || ang == 180) { //Se la scansione è completa genera un evento per visualizzare i contatori
							if (showCounter) { //Si usa per visualizzare solo una volta per scansione
								sendMsgTo(controller, new ViewCountMsg());
								showCounter = false;
							}
						} else {
							showCounter = true;
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

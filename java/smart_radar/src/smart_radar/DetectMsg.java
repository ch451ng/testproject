package smart_radar;

import java.util.Date;

import seiot.modulo_lab_3_3.common.*;

public class DetectMsg implements Msg {
	private int angolo;
	private Date date;
	
	public DetectMsg(int angolo) {
		this.angolo = angolo;
		this.date = new Date(); //Quando viene creato si inizializza la data/ora dell'evento 
	}
	
	public void setA(int angolo) {
		this.angolo = angolo;
	}
	
	public int getA() {
		return this.angolo;
	}
	
	public Date getDate() {
		return this.date;
	}

}
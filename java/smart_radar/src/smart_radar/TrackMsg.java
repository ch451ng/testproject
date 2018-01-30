package smart_radar;

import java.util.Date;

import seiot.modulo_lab_3_3.common.*;

public class TrackMsg implements Msg {
	private int angolo;
	private double dist;
	private Date date;

	public TrackMsg(double dist, int angolo) {
		this.angolo = angolo;
		this.dist = dist;
		this.date = new Date(); //Quando viene creato si inizializza la data/ora dell'evento 
	}

	public void setD(double dist) {
		this.dist = dist;
	}

	public double getD() {
		return this.dist;
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
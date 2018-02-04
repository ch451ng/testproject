package smart_door;


import java.util.Date;

import seiot.modulo_lab_3_3.common.*;

public class UpdateTemp implements Msg {
	private int temp;
	private Date date;

	public UpdateTemp(int temp) {
		this.temp = temp;
		this.date = new Date(); //Quando viene creato si inizializza la data/ora dell'evento 
	}

	public void setT(int temp) {
		this.temp = temp;
	}

	public int getT() {
		return this.temp;
	}

	public Date getDate() {
		return this.date;
	}
}

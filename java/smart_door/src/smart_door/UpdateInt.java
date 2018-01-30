package smart_door;


import java.util.Date;

import seiot.modulo_lab_3_3.common.*;

public class UpdateInt implements Msg {
	private int lumen;
	private Date date;

	public UpdateInt(int lumen) {
		
		this.lumen = lumen;
		this.date = new Date(); //Quando viene creato si inizializza la data/ora dell'evento 
	}



	public void setI(int lumen) {
		this.lumen = lumen;
	}

	public int getI() {
		return this.lumen;
	}

	public Date getDate() {
		return this.date;
	}
}
package smart_radar;


import seiot.modulo_lab_3_3.common.*;

public class ScanMsg implements Msg {
	private int angolo;
	private double dist;

	public ScanMsg(double dist, int angolo) {
		this.angolo = angolo;
		this.dist = dist;
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
}
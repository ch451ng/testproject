package smart_radar;

public class Counters {

	private int countD;
	private int countT;
	
	public Counters(){
		countD = 0;
		countT = 0;
	}
	
	public synchronized void incD(){
		countD++;
	}
	
	public synchronized void incT(){
		countT++;
	}
	
	
	public synchronized int getNumDetected(){
		return countD;
	}
	
	public synchronized int getNumTracked(){
		return countT;
	}
}

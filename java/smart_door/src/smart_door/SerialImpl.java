package smart_door;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;

public class SerialImpl implements seiot.modulo_lab_3_3.devices.Serial, SerialPortEventListener {

	private int rx;
	private int tx;
	private boolean isMsgAvailable;
	private String msg;
	private StdInputAgent auxWorker;
	
	private SerialPort serialPort;
	private BufferedReader input;
	private OutputStream output;
	private BlockingQueue<String> queue;
	
	public SerialImpl(String port, int rate) throws Exception {
		queue = new ArrayBlockingQueue<String>(100);

		CommPortIdentifier portId = CommPortIdentifier.getPortIdentifier(port);
		// open serial port, and use class name for the appName.
		SerialPort serialPort = (SerialPort) portId.open(this.getClass().getName(), 2000);

		// set port parameters
		serialPort.setSerialPortParams(rate,
				SerialPort.DATABITS_8,
				SerialPort.STOPBITS_1,
				SerialPort.PARITY_NONE);

		// serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN);
		// open the streams
		input = new BufferedReader(new InputStreamReader(serialPort.getInputStream()));
		output = serialPort.getOutputStream();

		// add event listeners
		serialPort.addEventListener(this);
		serialPort.notifyOnDataAvailable(true);
		try {
			auxWorker = new StdInputAgent();
			auxWorker.start();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	@Override
	public synchronized boolean isMsgAvailable() {
		isMsgAvailable = !queue.isEmpty();
		return isMsgAvailable;
	}
	
	public synchronized String readMsg(){
		String m = msg;
		isMsgAvailable = false;
		msg = null;
		return m;
	}
	
	public String receiveMsg() throws InterruptedException {
		return queue.take();
	}
	
	@Override
	public void sendMsg(String msg) {
		char[] array = msg.toCharArray();
		byte[] bytes = new byte[array.length];
		for (int i = 0; i < array.length; i++){
			bytes[i] = (byte) array[i];
		}
		try {
			output.write(bytes);
			output.flush();
		} catch(Exception ex){
			ex.printStackTrace();
		}
	}
	
	synchronized void setMsg(String msg){
		this.isMsgAvailable = true;
		this.msg = msg;
		notifyAll();
	}
	
	public synchronized String waitForMsg() throws InterruptedException {
			while (!isMsgAvailable){
				wait();
			}
			String m = msg;
			isMsgAvailable = false;
			msg = null;
			return m;
	}
	
	public synchronized void serialEvent(SerialPortEvent oEvent) {
		if (oEvent.getEventType() == SerialPortEvent.DATA_AVAILABLE) {
			try {
				if (input.ready()) {
				String msg=input.readLine();
				queue.put(msg);
				}
			} catch (Exception e) {
				System.out.println("ERR");
				System.err.println(e.toString());
			}
		}
		}
	
	
	class StdInputAgent extends Thread {
		public StdInputAgent(){
		}
		
		public void run(){
			
			BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
			while (true){
				try {
					String msg = queue.take();
					setMsg(msg);
					
				} catch (Exception ex){
					ex.printStackTrace();
				}
			}
		}
	}

}

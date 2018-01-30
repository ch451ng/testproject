package smart_radar;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.text.DateFormat;
import java.text.SimpleDateFormat;

import seiot.modulo_lab_3_3.common.*;
import seiot.modulo_lab_3_3.devices.*;

public class RadarController extends ReactiveAgent {

	static final String MSG_ON_SCAN = "00";
	static final String MSG_OFF = "02";
	static final String MSG_TRACK = "01";

	private enum State {
		IDLE, DETECTED, TRACK, SCAN
	};

	private State state;
	private Light powerLed;
	private Light trackLed;
	private Light detectLed;
	private ObservableTimer timer;
	private ObservableButton onButton;
	private ObservableButton offButton;
	private int currentCount;
	private Serial serialDevice;

	private Counters radarCounter;

	public void init(Counters counter, Light led, Light ledD, Light ledT, ObservableButton on, ObservableButton off,
			Serial serialDevice) {
		this.powerLed = led;
		this.trackLed = ledT;
		this.detectLed = ledD;
		this.serialDevice = serialDevice;
		this.onButton = on;
		onButton.addObserver(this);
		this.offButton = off;
		offButton.addObserver(this);
		this.timer = new ObservableTimer();
		timer.addObserver(this);
		state = State.IDLE;
		this.radarCounter = counter;
	}

	@Override
	protected void processEvent(Event ev) {
		if (ev instanceof MsgEvent) {
			Msg msg = ((MsgEvent) ev).getMsg();
			if (msg instanceof ViewCountMsg) {
				showCounter();
			}
		}
		switch (state) {
		case IDLE:
			if (ev instanceof ButtonPressed && ((ButtonPressed) ev).getSourceButton() == onButton) {
				try {
					powerLed.switchOn();
					serialDevice.sendMsg(MSG_ON_SCAN); //Invia messaggio di transizione on/scan all'arduino
				} catch (IOException e) {
					e.printStackTrace();
				}
				state = State.SCAN;
			}
			break;

		case TRACK:
			if (ev instanceof MsgEvent) {
				Msg msg = ((MsgEvent) ev).getMsg();
				if (msg instanceof ScanMsg || msg instanceof DetectMsg) {
					try {
						trackLed.switchOff();
						serialDevice.sendMsg(MSG_ON_SCAN); //Invia messaggio di transizione on/scan all'arduino
					} catch (IOException e) {
						e.printStackTrace();
					}
					state = State.SCAN;
				} else if (msg instanceof DetectMsg) { //Se l'oggetto si sposta sopra soglia
					try {
						log(ev);
						radarCounter.incD();
						detectLed.switchOn();
						timer.scheduleTick(500);
						trackLed.switchOff();
						serialDevice.sendMsg(MSG_ON_SCAN); //Invia messaggio di transizione on/scan all'arduino
					} catch (IOException e) {
						e.printStackTrace();
					}
					state = State.DETECTED;
				} else if (msg instanceof TrackMsg) { //Traccia eventuali spostamenti sotto soglia rimanendo nello stato
					radarCounter.incT();
					log(ev);
				}

			} else if (ev instanceof ButtonPressed && ((ButtonPressed) ev).getSourceButton() == offButton) {
				try {
					powerLed.switchOff();
					serialDevice.sendMsg(MSG_OFF); //Invia messaggio di transizione off all'arduino
				} catch (IOException e) {
					e.printStackTrace();
				}
				state = State.IDLE;

			} else if (ev instanceof Tick) {
				try {
					detectLed.switchOff();
				} catch (Exception ex) {
					ex.printStackTrace();
				}
			}
			break;

		case DETECTED:
			if (ev instanceof Tick) {
				try {
					detectLed.switchOff();
				} catch (Exception ex) {
					ex.printStackTrace();
				}
				state = State.SCAN;
			} else if (ev instanceof MsgEvent) {
				Msg msg = ((MsgEvent) ev).getMsg();
				if (msg instanceof TrackMsg) {
					try {
						log(ev);
						radarCounter.incT();
						trackLed.switchOn();
						serialDevice.sendMsg(MSG_TRACK); //Invia messaggio di transizione track all'arduino
					} catch (IOException e) {
						e.printStackTrace();
					}
					state = State.TRACK;
				} else if (msg instanceof DetectMsg) { //Traccia eventuali spostamenti in range di detect rimanendo nello stato
					radarCounter.incD();
					log(ev);
				}
				
			} else if (ev instanceof ButtonPressed && ((ButtonPressed) ev).getSourceButton() == offButton) {
				try {
					powerLed.switchOff();
					serialDevice.sendMsg(MSG_OFF); //Invia messaggio di transizione off all'arduino
				} catch (IOException e) {
					e.printStackTrace();
				}
				state = State.IDLE;

			}
			break;

		case SCAN:
			if (ev instanceof MsgEvent) {
				Msg msg = ((MsgEvent) ev).getMsg();
				if (msg instanceof DetectMsg) {

					try {
						log(ev);
						radarCounter.incD();
						detectLed.switchOn();
						timer.scheduleTick(500);
					} catch (Exception ex) {
						ex.printStackTrace();
					}
					state = State.DETECTED;
				} else if (msg instanceof TrackMsg) {
					try {
						log(ev);
						radarCounter.incT();
						trackLed.switchOn();
						serialDevice.sendMsg(MSG_TRACK); //Invia messaggio di transizione track all'arduino
					} catch (IOException e) {
						e.printStackTrace();
					}
					state = State.TRACK;
				}
			} else if (ev instanceof Tick) {
				try {
					detectLed.switchOff();
				} catch (Exception ex) {
					ex.printStackTrace();
				}
			} else if (ev instanceof ButtonPressed && ((ButtonPressed) ev).getSourceButton() == offButton) {
				try {
					serialDevice.sendMsg(MSG_OFF); //Invia messaggio di transizione off all'arduino
					powerLed.switchOff();
				} catch (IOException e) {

					e.printStackTrace();
				}
				state = State.IDLE;

			}

			break;
		}

	}

	private void showCounter() {
		System.out.printf("Detectded: %d\nTracked: %d\n", radarCounter.getNumDetected(), radarCounter.getNumTracked());

	}

	private void log(Event ev) {
		String log = "";
		DateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss.SSS");
		Msg msg = ((MsgEvent) ev).getMsg();

		if (msg instanceof TrackMsg) {
			int ang = ((TrackMsg) msg).getA();
			String date = dateFormat.format(((TrackMsg) msg).getDate());
			double dist = ((TrackMsg) msg).getD();
			log = String.format("Time %s - Object tracked at angle %d distance %.2f\n", date, ang, dist);
			System.out.printf(log);

		} else if (msg instanceof DetectMsg) {
			int ang = ((DetectMsg) msg).getA();
			String date = dateFormat.format(((DetectMsg) msg).getDate());
			log = String.format("Time %s - Object detected at angle %d\n", date, ang);
			System.out.printf(log);
		}
		try (FileWriter fw = new FileWriter("smart_radar_log.txt", true);
				BufferedWriter bw = new BufferedWriter(fw);
				PrintWriter out = new PrintWriter(bw)) {
			out.println(log);
			out.close();
			
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}

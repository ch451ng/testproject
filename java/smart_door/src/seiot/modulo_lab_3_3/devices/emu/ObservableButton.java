package seiot.modulo_lab_3_3.devices.emu;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import seiot.modulo_lab_3_3.common.*;
import seiot.modulo_lab_3_3.devices.*;

import javax.swing.JButton;
import javax.swing.JFrame;

public class ObservableButton extends seiot.modulo_lab_3_3.devices.ObservableButton {

	private int pinNum;
	private boolean isPressed;
	private ButtonFrame buttonFrame;
	
	public ObservableButton(int pinNum){
		this.pinNum = pinNum;
		try {
			buttonFrame = new ButtonFrame(pinNum);
			buttonFrame.setVisible(true);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	@Override
	public synchronized boolean isPressed() {
		return isPressed;
	}
	
	void setPressed(boolean state){
		isPressed = state;
		if (isPressed){
			this.notifyEvent(new ButtonPressed(this));
		} else {
			this.notifyEvent(new ButtonReleased(this));
		}
	}
	
	class ButtonFrame extends JFrame implements MouseListener {
		  public ButtonFrame(int pin){
		    super("Button Emu");
		    setSize(200,50);
		    JButton button = new JButton("Button on pin: "+pin);
		    button.addMouseListener(this);
		    getContentPane().add(button);
		    addWindowListener(new WindowAdapter(){
		      public void windowClosing(WindowEvent ev){
		        System.exit(-1);
		      }
		    });
		  }

		@Override
		public void mousePressed(MouseEvent e) {
			setPressed(true);
		}

		@Override
		public void mouseReleased(MouseEvent e) {
			setPressed(false);
		}

		@Override
		public void mouseEntered(MouseEvent e) {
		}

		@Override
		public void mouseExited(MouseEvent e) {
		}

		@Override
		public void mouseClicked(MouseEvent e) {			
		}
	}

}

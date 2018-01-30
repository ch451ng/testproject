package seiot.modulo_lab_3_3.devices;

import seiot.modulo_lab_3_3.common.*;

public class ButtonReleased implements Event {
	private Button source;
	
	public ButtonReleased(Button source){
		this.source = source;
	}
	
	public Button getSourceButton(){
		return source;
	}
}

#include "MsgService.h"
#include "Led.h"
#include "ButtonImpl.h"
#include "TempSensor.h"
#include <SoftwareSerial.h>
#include <Wire.h>
#include "sonar.h"
#include "pir.h"
#include "Servo2.h"
#include "PWMServo.h"

/*
 *  BT module connection:  
 *  - pin 2 <=> TXD
 *  - pin 3 <=> RXD
 *
 */ 

MsgService msgService(2,3);
Button* button;
Led* led;
TempSensor* temp;
Sonar* sonar;
Pir* pir;
Servo2* servo;
PWMServo* myservo;

bool buttonPressed;
bool detected;

void setup() {
  button = new ButtonImpl(7);
  led = new Led(5);
  temp = new TempSensor();
  sonar = new Sonar(10,12);
  pir = new Pir(4);
  myservo->attach(9);
  myservo->write(0);
  msgService.init();  
  Serial.begin(9600);
  while (!Serial){}
  buttonPressed = false;
  Serial.println("ready to go.");   

}

void loop() {
  if (msgService.isMsgAvailable()) {
    Msg* message = msgService.receiveMsg();
    String msg = message->getContent();
    if (msg == "1"){
      Serial.println("LED ON");
      led->switchOn();
      msgService.sendMsg(Msg("ok"));
    } else if (msg == "2"){
      Serial.println("LED OFF");
      led->switchOff();
      msgService.sendMsg(Msg("ok"));
    } else if (msg == "3"){
      int value = temp->readTemperature();
      Serial.println("temp: "+String(value));
      msgService.sendMsg(Msg("temp:"+String(value)));
    } else if (msg == "4") {
    	float dist = sonar->getDistance();
    	Serial.println("dist: "+String(dist));
    	msgService.sendMsg(Msg("dist:"+String(dist)));

    } else if (msg == "5") {
	msgService.sendMsg(Msg("servo"));
    myservo->write(180);

}



    delete message;
  }
  
  if (button->isPressed()){
    if (!buttonPressed){
      Serial.println("pressed");
      msgService.sendMsg(Msg("button pressed"));
      buttonPressed = true;
    }
  } else if (buttonPressed){
      Serial.println("released");
      msgService.sendMsg(Msg("button released"));
      buttonPressed = false;
  }

//  if (pir->isDetected()){
//	  if (!detected){
//		  Serial.println("detected");
//		  msgService.sendMsg(Msg("detected"));
//		  detected = true;
//	  } else if (detected){
//		  Serial.println("lost");
//		  		  msgService.sendMsg(Msg("lost"));
//		  		  detected = false;
//	  }
//  }


}


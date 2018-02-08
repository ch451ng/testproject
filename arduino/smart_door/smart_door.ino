#include "Arduino.h"
#include "MsgService.h"
#include "MsgServiceBT.h"
#include "Led.h"
#include "ButtonImpl.h"
#include "TempSensor.h"
#include <SoftwareSerial.h>
#include <Wire.h>
#include "sonar.h"
#include "pir.h"
//#include "PWMServo.h"

//

#include "Shared.h"
#include "Scheduler.h"
#include "SerialMessagingTask.h"
#include "MessagingTaskBT.h"
#include "UpdateRemoteTask.h"

Scheduler sched;

void setup()
{


	Button* button;
	Led* led;
	TempSensor* temp;
	Sonar* sonar;
	Pir* pir;
	//Servo2* servo;
	//PWMServo* myservo;
	Shared* shared = new Shared();

	sched.init(25);

	temp = new TempSensor();
	MsgServiceBT* msgServiceBT = new MsgServiceBT(2,3);
	MsgService* msgService = new MsgService();


	msgServiceBT->init();
	msgService->init();


	//Task* t0 = new SerialMessagingTask(shared, msgService);
	//t0->init(25);
	//sched.addTask(t0);

	Task* t1 = new MessagingTaskBT(shared, msgServiceBT, msgService);
	t1->init(25);
	sched.addTask(t1);

	msgService->sendMsg(shared->getLoginMsg());

	Task* t2 = new UpdateRemoteTask(shared, temp, msgService, msgServiceBT);
	t2->init(1000);
	sched.addTask(t2);
	msgService->sendMsg("TEST01");

}

void loop()
{
	sched.schedule();
}

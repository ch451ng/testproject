#include "Scheduler.h"
#include "BlinkTask.h"
#include "config.h"
#include "Shared.h"
#include "LedExt.h"
#include "MessagingTask.h"
#include "DoorManagerTask.h"
#include "DetectMoveTask.h"
#include "DistanceDetectorTask.h"
#include "Pir.h"
#include "Sonar.h"
#include "ButtonImpl.h"
#include "MsgService.h"

Scheduler sched;

void setup(){

	sched.init(25);

	Shared* shared = new Shared();

	Pir* pir = new Pir(PIR_PIN);
	Sonar* sonar = new Sonar(SONAR_ECHO_PIN,SONAR_TRIG_PIN);
	LedExt* lr = new LedExt(LR_PIN,0);
	LedExt* ldist1 = new LedExt(LDIST1_PIN,0);
	LedExt* ldist2 = new LedExt(LDIST2_PIN,0);

	Button* close = new ButtonImpl(CLOSE_PIN);
	Button* touch = new ButtonImpl(TOUCH_PIN);

	MsgService* msgService = new MsgService();
	msgService->init();

	Task* t0 = new MessagingTask(shared, close,msgService);
	t0->init(100);
	sched.addTask(t0);

	Task* t1 = new DoorManagerTask(shared, lr);
	t1->init(50);
	sched.addTask(t1);

	Task* t2 = new DetectMoveTask(shared, pir,msgService);
	t2->init(100);
	sched.addTask(t2);

	Task* t3 = new DistanceDetectorTask(shared, ldist1, ldist2,sonar,touch,msgService);
	t3->init(100);
	sched.addTask(t3);

}



void loop(){
	sched.schedule();
}

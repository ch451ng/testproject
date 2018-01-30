#include "Scheduler.h"
#include "config.h"
#include "LedExt.h"
#include "MessagingTask.h"
#include "Sonar.h"
#include "RadarDrive.h"
#include "MsgService.h"
#include "RadarControlTask.h"

Scheduler sched;

//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here

	sched.init(25);

	Shared* shared = new Shared();

	Sonar* sonar = new Sonar(SONAR_ECHO_PIN,SONAR_TRIG_PIN);
	RadarDrive* drive = new RadarDrive(SERVO_PIN);
	LedExt* lr = new LedExt(CONN_PIN,0);

	MsgService* msgService = new MsgService();
	msgService->init();

	Task* t0 = new MessagingTask(shared, msgService);
	t0->init(25);
	sched.addTask(t0);

	Task* t1 = new RadarControlTask(shared, lr, sonar, drive, msgService);
	t1->init(50);
	sched.addTask(t1);
}


void loop()
{
	sched.schedule();
}

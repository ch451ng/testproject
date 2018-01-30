/*
 * PSE a.a. 2016/2017
 *
 * CONSEGNA #3 - SMART CAR
 *
 * author: A. Ricci, A. Croatti
 *
 */
#include "Scheduler.h"
#include "DetectDistanceTask.h"
#include "CollisionManagerTask.h"
#include "CarControllerTask.h"
#include "Led.h"
#include "LedExt.h"
#include "config.h"
#include <Servo.h>
#include <FlexiTimer2.h>
#include "SoftwareSerial.h"
#include "Logger.h"

#define VERSION "1.0"

Scheduler sched(10);

void setup(){
  Logger::init();
  
  sched.init(5);
  
  Led* l2 = new Led(L2_PIN);

  CarControllerTask* t0 = new CarControllerTask();
  t0->init(25);
  sched.addTask(t0);

  Task* t1 = new DetectDistanceTask(t0,l2);
  t1->init(25);
  sched.addTask(t1);

  Task* t2 = new CollisionManagerTask(t0,l2);
  t2->init(25);
  sched.addTask(t2);
  
  Logger::log(String(".:: SMART CAR READY v.")+VERSION+" ::.");
}

void loop(){
  sched.schedule();
}

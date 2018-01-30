/*
 * PSE a.a. 2016/2017
 *
 * CONSEGNA #2 - SMART TOILET
 *
 * author: A. Ricci
 *
 */
#include "Scheduler.h"
#include "DetectPresenceTask.h"
#include "WCMonitoringTask.h"
#include "SelfCleaningTask.h"
#include "SharedContext.h"
#include "Led.h"
#include "Sonar.h"
#include "WashingTask.h"
#include "AlarmTask.h"
#include "Pir.h"
#include "MsgService.h"
#include "ToiletServiceTask.h"
#include "LedExt.h"
#include "ButtonImpl.h"
#include "config.h"

Scheduler sched(10);

void setup(){
  
  sched.init(25);
  
  SharedContext* pContext = new SharedContext();  
  
  MsgService* msgService = new MsgService();
  msgService->init();

  Led* l1 = new Led(L1_PIN);
  Pir* pir = new Pir(PIR_PIN);
  Sonar* sonar = new Sonar(SONAR_ECHO_PIN,SONAR_TRIG_PIN);
  LedExt* l2 = new LedExt(L2_PIN);
  Led* l3 = new Led(L3_PIN);
  Display* display = new Display(msgService);
  Button* b1 = new ButtonImpl(T1_PIN);
  Button* b2 = new ButtonImpl(T2_PIN);
 
  Task* t0 = new DetectPresenceTask(pContext,pir,l1,display);
  t0->init(100);
  sched.addTask(t0);

  WashingTask* t1b = new WashingTask(pContext,l2);
  t1b->init(25);
  sched.addTask(t1b);

  Task* t1 = new WCMonitoringTask(pContext,sonar,t1b);
  t1->init(100);
  sched.addTask(t1);

  Task* t2 = new SelfCleaningTask(pContext,l3);
  t2->init(100);
  sched.addTask(t2);

  Task* t3 = new ToiletServiceTask(pContext,msgService);
  t3->init(100);
  sched.addTask(t3);

  Task* t4 = new AlarmTask(pContext,sonar,l3,b1,b2);
  t4->init(100);
  sched.addTask(t4);
}

void loop(){
  sched.schedule();
}

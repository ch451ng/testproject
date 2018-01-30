#ifndef __ALARMTASK__
#define __ALARMTASK__

#include "Task.h"
#include "SharedContext.h"
#include "ProximitySensor.h"
#include "Light.h"
#include "Button.h"

class AlarmTask: public Task {

public:

  AlarmTask(SharedContext* pContext, ProximitySensor* sensor, Light* led, Button* on, Button* off);
  void init(int period);  
  void tick();

private:
  float lastDistDetected;
  ProximitySensor* sensor;
  Light* light;
  Button* on;
  Button* off;
  SharedContext* pContext;
  int btcount;
  int notMovingCount;
  enum { IDLE, BUTTON_PRESSED, DETECTED, NOT_MOVING, ALARM } state;

};

#endif


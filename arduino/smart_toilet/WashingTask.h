#ifndef __WASHINGTASK__
#define __WASHINGTASK__

#include "Task.h"
#include "Scheduler.h"
#include "LightExt.h"
#include "SharedContext.h"

class WashingTask: public Task {

public:
  WashingTask(SharedContext* pContext, LightExt* light);  
  void init(int period);  
  void tick();
  void trigger();

private:
  int pulseCount;
  int intensity;
  volatile bool isTriggered;
  LightExt* led;
  SharedContext* pContext;
  enum { IDLE, PULSE, PULSE_DOWN, PULSE_UP } state;

};

#endif


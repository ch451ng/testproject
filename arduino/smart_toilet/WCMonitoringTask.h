#ifndef __WCMONITORINGTASK__
#define __WCMONITORINGTASK__

#include "Task.h"
#include "SharedContext.h"
#include "ProximitySensor.h"
#include "Scheduler.h"
#include "WashingTask.h"
#include "LightExt.h"

class WCMonitoringTask: public Task {

public:
  WCMonitoringTask(SharedContext* pContext, ProximitySensor* sensor, WashingTask* washingTask);
  void init(int period);  
  void tick();

private:
  
  ProximitySensor* sensor;
  SharedContext* pContext;
  WashingTask* washingTask;
  enum { NO_ONE, DETECTED, USING_WC } state;

};

#endif


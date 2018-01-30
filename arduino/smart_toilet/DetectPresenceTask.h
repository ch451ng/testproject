#ifndef __DETECTPRESENCETASK__
#define __DETECTPRESENCETASK__

#include "Task.h"
#include "SharedContext.h"
#include "PresenceSensor.h"
#include "Light.h"
#include "Display.h"

class DetectPresenceTask: public Task {

public:

  DetectPresenceTask(SharedContext* pContext, PresenceSensor* sensor, Light* light, Display* display);
  void init(int period);  
  void tick();

private:
  PresenceSensor* detector;
  Light* light;
  SharedContext* pContext;
  Display* display;
  int count;
  enum { NO_ONE, DETECTED, EXITING } state;

};

#endif


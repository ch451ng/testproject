#ifndef __SELFCLEANINGTASK__
#define __SELFCLEANINGTASK__

#include "Task.h"
#include "SharedContext.h"
#include "Light.h"

class SelfCleaningTask: public Task {

public:

  SelfCleaningTask(SharedContext* pContext, Light* cleaningLight);
  void init(int period);  
  void tick();

private:
  int lastWCCleaningCount;
  Light* light;
  SharedContext* pContext;
  enum { IDLE, CLEANING } state;
  int count;
};

#endif


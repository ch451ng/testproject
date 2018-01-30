#ifndef __TOILETSERVICETASK__
#define __TOILETSERVICETASK__

#include "Task.h"
#include "SharedContext.h"
#include "MsgService.h"

class ToiletServiceTask: public Task {

public:

  ToiletServiceTask(SharedContext* pContext, MsgService* msgService);
  void init(int period);  
  void tick();

private:
  MsgService* msgService;
  SharedContext* pContext;
};

#endif


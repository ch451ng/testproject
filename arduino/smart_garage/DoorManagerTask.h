/*
 * DoorManagerTask.h
 *
 *  Created on: 07 nov 2017
 *      Author: Luke
 */

#ifndef SMART_GARAGE_DOORMANAGERTASK_H_
#define SMART_GARAGE_DOORMANAGERTASK_H_



#include "Task.h"
#include "LedExt.h"
#include "enumerati.h"
#include "Shared.h"

class DoorManagerTask: public Task {

private:
  int openingCNT;
  int waitingCNT;
  int intensity;
  LightExt* led;
  doorstatus state;
  Shared* shared;

public:

  DoorManagerTask(Shared* shared, LightExt* door);
  void init(int period);
  void tick();
};


#endif /* SMART_GARAGE_DOORMANAGERTASK_H_ */

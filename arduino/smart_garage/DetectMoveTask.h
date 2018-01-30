/*
 * DetectMoveTask.h
 *
 *  Created on: 08 nov 2017
 *      Author: Luke
 */

#ifndef DETECTMOVETASK_H_
#define DETECTMOVETASK_H_

#include "Task.h"
#include "Shared.h"
#include "PresenceSensor.h"
#include "enumerati.h"
#include "MsgService.h"

class DetectMoveTask: public Task {
public:

  DetectMoveTask(Shared* shared, PresenceSensor* sensor,MsgService* msgService);
  void init(int period);
  void tick();

private:
  PresenceSensor* detector;
  Shared* shared;
  detectmvstatus state;
  MsgService* msgService;

};
#endif /* DETECTMOVETASK_H_ */

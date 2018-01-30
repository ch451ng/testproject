/*
 * DistanceDetectorTask.h
 *
 *  Created on: 09 nov 2017
 *      Author: Luke
 */

#ifndef DISTANCEDETECTORTASK_H_
#define DISTANCEDETECTORTASK_H_

#include "Task.h"
#include "LedExt.h"
#include "enumerati.h"
#include "Shared.h"
#include "ProximitySensor.h"
#include "Button.h"
#include "Costant.h"
#include "MsgService.h"



class DistanceDetectorTask: public Task {
private:
  //float distance;
  LightExt* led1;
  LightExt* led2;
  proxstatus state;
  Shared* shared;
  ProximitySensor* sensor;
  Button* touch;
  void SetDisplay(LightExt* ld1, LightExt* ld2, int intensity);
  MsgService* msgService;

public:

  DistanceDetectorTask(Shared* shared, LightExt* ld1, LightExt* ld2, ProximitySensor* prox, Button* touch,MsgService* msgService);
  void init(int period);
  void tick();
};

#endif /* DISTANCEDETECTORTASK_H_ */

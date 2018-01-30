#ifndef __DISTANCE_DETECTOR_TASK__
#define __DISTANCE_DETECTOR_TASK__

#include "Task.h"
#include "ProximitySensor.h"
#include "Light.h"
#include "CarControllerTask.h"

class DetectDistanceTask: public Task {

public:

  DetectDistanceTask(CarControllerTask* pCarController, Light* led);
  void init(int period);  
  void tick();

private:
  ProximitySensor* pSonar;
  Light* pLight;
  // SharedContext* pContext;
  CarControllerTask* pCarController;
  enum { NO_CAR_DETECTED, CAR_DETECTED, CAR_VERY_NEAR } state;
};

#endif


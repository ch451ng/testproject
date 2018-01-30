#ifndef __COLLISION_MANAGER_TASK__
#define __COLLISION_MANAGER_TASK__

#include "Task.h"
#include "Light.h"
#include "Button.h"
#include "CarControllerTask.h"
#include "DefenceDevice.h"

class CollisionManagerTask: public Task {

public:

  CollisionManagerTask(CarControllerTask* car, Light* pLight);
  void init(int period);  
  void tick();

private:
  Button* pCollisionDetector;
  Light* pLight;
  int collisionTicks;
  CarControllerTask* pCarController;
  DefenceDevice* pDefenceDevice;

  enum { IDLE, COLLISION_DETECTED_MOVING, COLLISION_DETECTED_PARKED } state;
};

#endif


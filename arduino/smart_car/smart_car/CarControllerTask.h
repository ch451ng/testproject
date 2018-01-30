#ifndef __CAR_CONTROLLER_TASK__
#define __CAR_CONTROLLER_TASK__

#include "Task.h"
#include "LightExt.h"
#include "MsgService.h"

class CarControllerTask: public Task {
 
public: 
  CarControllerTask();
  
  void init(int period);  
  void tick();
  virtual bool notifyCarInRange(int dist);
  virtual bool notifyNoCarsInRange();
  virtual bool notifyCollision();

  bool isCarOff();
  bool isCarMoving();
  bool isCarParked();

  bool isDefenceLevelUpdated();
  int  fetchDefenceLevel();
  
private:
  void checkMsgs();
  
  LightExt* pLight;
  MsgService* pMsgService;

  int defenceLevel;
  bool defenceLevelUpdated;
  int ledIntensity;
  int fadeAmount;
  enum { CAR_OFF, CAR_MOVING, CAR_PARKED } state;
};




#endif


#include "CollisionManagerTask.h"
#include "ButtonImpl.h"
#include "Led.h"
#include "config.h"
#include "Arduino.h"
#include "Logger.h"

#define LED_TIME 2000

CollisionManagerTask::CollisionManagerTask(CarControllerTask* car, Light* light){
  this->pCarController = car;
  this->pCollisionDetector = new ButtonImpl(T1_PIN);
  this->pDefenceDevice = new DefenceDevice(SERVO_PIN);
  this->pLight = light;
}
  
void CollisionManagerTask::init(int period){
  Task::init(period);
  state = IDLE;    
  /* test */
  /*
  pDefenceDevice->setLevel(0);
  delay(500);
  pDefenceDevice->setLevel(100);
  delay(500);
  pDefenceDevice->setLevel(0);
  */
}
  
void CollisionManagerTask::tick(){
  
  switch (state){
    case IDLE: {
      if (pCollisionDetector->isPressed()){
        if (pCarController->isCarMoving()){
          pCarController->notifyCollision();
          state = COLLISION_DETECTED_MOVING;
          Logger::log("collision detected while moving");
        } else if (pCarController->isCarParked()){
          pLight->switchOn();
          pCarController->notifyCollision();
          collisionTicks = 0;
          state = COLLISION_DETECTED_PARKED;
          Logger::log("collision detected while parked");
        }
      } 
      break;
    }
    case COLLISION_DETECTED_MOVING: {
      // set the specified mech
      if (pCarController->isDefenceLevelUpdated()){
        int level = pCarController->fetchDefenceLevel();
        if (level >= 0){
          Logger::log(String("applying defence level: ")+level);
          pDefenceDevice->setLevel(level);
        } else {
          /* disabled */
          pDefenceDevice->setLevel(0);
          Logger::log(String("[car controller] defence stopped."));
          state = IDLE;
        }
      }
      break;
    }
    case COLLISION_DETECTED_PARKED: {
      collisionTicks++;
      if (collisionTicks*getPeriod() > LED_TIME){
        Logger::log("collision while parked.");
        pLight->switchOff();
        collisionTicks = 0;
        state = IDLE;  
      }
      break;
    }
  }
}


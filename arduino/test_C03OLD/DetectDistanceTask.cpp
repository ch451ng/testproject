#include "DetectDistanceTask.h"
#include "Sonar.h"
#include "config.h"
#include "Arduino.h"
#include "Logger.h"

#define DIST_MAX 30
#define DIST_MIN 10

DetectDistanceTask::DetectDistanceTask(CarControllerTask* car, Light* led){
  this->pCarController = car;
  this->pLight = led;
  pSonar = new Sonar(SONAR_ECHO_PIN,SONAR_TRIG_PIN);
}
  
void DetectDistanceTask::init(int period){
  Task::init(period);
  state = NO_CAR_DETECTED;    
}
  
void DetectDistanceTask::tick(){
  if (pCarController->isCarMoving()){
    float value = pSonar->getDistance();
    int d = value * 100; // in cm
    // Logger::log(String("dist: ")+d);
    switch (state){
      case NO_CAR_DETECTED: {
        if (d < DIST_MAX){
          state = CAR_DETECTED;
          Logger::log(String("car_detected: ")+d);
        }
        break;
      }
      case CAR_DETECTED: {
        if (d < DIST_MIN){
          state = CAR_VERY_NEAR;
          pCarController->notifyCarInRange(d);
          pLight->switchOn();
          Logger::log(String("car_very_near: ")+d);
        } else if (d >= DIST_MAX) {
          state = NO_CAR_DETECTED;          
          pCarController->notifyNoCarsInRange();
          Logger::log("no_car_detected");
        } else {
          Logger::log(String("car_detected: ")+d);
          pCarController->notifyCarInRange(d);
        }      
        break;
      }
      case CAR_VERY_NEAR: {
        if (d > DIST_MIN) {
          pLight->switchOff();
          if (d < DIST_MAX){
            Logger::log("car_detected");
            pCarController->notifyCarInRange(d);
            state = CAR_DETECTED;
          } else {
            Logger::log("no_car_detected");
            state = NO_CAR_DETECTED;
            pCarController->notifyNoCarsInRange();
          }
        } else {
          pCarController->notifyCarInRange(d);
        }
        break;
      }
    }
  }
}

#include "AlarmTask.h"
#include "Sonar.h"
#include "Arduino.h"

#define MAX_DIST 0.40
#define BUTTON_PRESS_COUNT 40
#define MOVING_THRESHOLD 0.05
#define NOT_MOVING_COUNT 40

AlarmTask::AlarmTask(SharedContext* pContext, ProximitySensor* sensor, Light* light, Button* on, Button* off){
  this->pContext = pContext;
  this->light = light;
  this->on = on;
  this->off = off;
  this->sensor = sensor;
}
  
void AlarmTask::init(int period){
  Task::init(period);
  state = IDLE;    
}
  
void AlarmTask::tick(){
  switch (state){
    case IDLE: {
      if (on->isPressed()){
        btcount = 0;
        state = BUTTON_PRESSED;
      } else {
        if (pContext->isSomeoneInside()){
          float dist = sensor->getDistance();
          if (dist < MAX_DIST){
            lastDistDetected = dist;
            state = DETECTED;
          } 
        }
      }
      break;
    }
    case DETECTED: {
      float current = sensor->getDistance();
      float delta = abs(current - lastDistDetected);
      lastDistDetected = current;
      // Serial.println("delta: "+String(delta));
      if (delta < MOVING_THRESHOLD){
          state = NOT_MOVING;
          notMovingCount = 0;
      } else {
        state = IDLE;
      }
      break;
    }
    case BUTTON_PRESSED: {
      if (on->isPressed()){
        btcount++;
        if (btcount > BUTTON_PRESS_COUNT){
          state = ALARM;
          //Serial.println("ALARM!");
          light->switchOn();
          pContext->setAlarm(true);
        }
      } else {
        state = IDLE;        
      }
      break;
    }
    case NOT_MOVING: {
      float current = sensor->getDistance();
      float delta = abs(current - lastDistDetected);
      // Serial.println("delta: "+String(delta));
      if (delta < MOVING_THRESHOLD){
        notMovingCount++;
        if (notMovingCount > NOT_MOVING_COUNT){
          state = ALARM;
          light->switchOn();
          pContext->setAlarm(true);
        }
      } else {
        state = IDLE; 
      }
      break;
    }
    case ALARM: {
      if (off->isPressed()){
        state = IDLE;
        pContext->setAlarm(false);
        // Serial.println("ALARM off.");
        light->switchOff();
      }
      break;
    }
  }
}

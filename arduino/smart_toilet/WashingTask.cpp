#include "WashingTask.h"
#include "LedExt.h"

WashingTask::WashingTask(SharedContext* pContext, LightExt* light){
  this->pContext = pContext;
  this->led = light;
  isTriggered = false;
}
  
void WashingTask::init(int period){
  Task::init(period);
  state = IDLE;   
  led->switchOn();
  led->setIntensity(0);
}

void WashingTask::trigger(){
  isTriggered = true;
}  

void WashingTask::tick(){
  switch (state){
    case IDLE: {
      if (isTriggered){
        pulseCount = 0;
        intensity = 0;
        state = PULSE;
      }
      break;
    }
    case PULSE: {
      pulseCount++;
      // Serial.println("Washing.. "+String(pulseCount));
      if (pulseCount < 40){
        state = PULSE_UP;
      } else {
        state = IDLE;
        isTriggered = false;
      }
      break;      
    }
    case PULSE_UP: {
      for (int i = 0; i < 50; i++){
        intensity++;
        led->setIntensity(intensity);      
      }  
      if (intensity >= 250){
        state = PULSE_DOWN;
      }
      break;
    }
    case PULSE_DOWN: {
      for (int i = 0; i < 50; i++){
        intensity--;
        led->setIntensity(intensity);      
      }  
      if (intensity <= 0){
        state = PULSE;
      }
      break;
    }
  }
}

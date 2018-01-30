#include "DetectPresenceTask.h"
#include "Pir.h"
#include "Led.h"

DetectPresenceTask::DetectPresenceTask(SharedContext* pContext, PresenceSensor* sensor, Light* light, Display* display){
  this->light = light;
  this->detector = sensor;
  this->pContext = pContext;
  this->display = display;
}
  
void DetectPresenceTask::init(int period){
  Task::init(period);
  state = NO_ONE;    
}
  
void DetectPresenceTask::tick(){
  switch (state){
    case NO_ONE:
      if (detector->isDetected()){
        if (!pContext->isCleaning()){
          light->switchOn();
          pContext->trackNewUser();
          pContext->setSomeoneInside(true);
          // Serial.println("someone inside.");
          state = DETECTED;     
        } else {
          display->showMsg("Si prega di uscire, toilette in fase di auto-pulizia");
        }
      }
      break;
    case DETECTED:
      if (!detector->isDetected()){
        state = EXITING;
        count = 0;
      }
      break;
    case EXITING:
      if (detector->isDetected() || pContext->isInUse()){
        state = DETECTED;     
      } else {
        count++;
        if (count > 100){
          // 10 sec
          light->switchOff();
          pContext->setSomeoneInside(false);
          state = NO_ONE;     
        }
      }
      break;
  }
}

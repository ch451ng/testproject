#include "WCMonitoringTask.h"
#include "Sonar.h"
#include "WashingTask.h"

#define DMIN 0.10
#define DMAX 0.30

WCMonitoringTask::WCMonitoringTask(SharedContext* pContext, ProximitySensor* sensor, WashingTask* washingTask){
  this->pContext = pContext;
  this->sensor = sensor;
  this->washingTask = washingTask;
}
  
void WCMonitoringTask::init(int period){
  Task::init(period);
  state = NO_ONE;   
}
  
void WCMonitoringTask::tick(){
  switch (state){
    case NO_ONE:
      if (pContext->isSomeoneInside()){
        state = DETECTED;     
      }
      break;
    case DETECTED: {
      float dist = sensor->getDistance();
      if (dist < DMIN){
        state = USING_WC;
        // Serial.println("using");
        pContext->setUsing(true);
      } else if (!pContext->isSomeoneInside()){
        state = NO_ONE;
      }
      break;
    }
    case USING_WC: {
      float dist = sensor->getDistance();
      // Serial.println(">> dist "+String(dist));
      if (dist > DMAX){
        pContext->trackNewWCUsage();
        washingTask->trigger();
        pContext->setUsing(false);      
        state = DETECTED;     
        // Serial.println("done-using:washing");
      }
      break;
    }
  }
}

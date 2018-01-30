#include "SelfCleaningTask.h"

#define NMAX_USAGE 2
#define CLEANING_TIME 100

SelfCleaningTask::SelfCleaningTask(SharedContext* pContext, Light* cleaningLight){
  this->pContext = pContext;
  this->light = cleaningLight;
}
  
void SelfCleaningTask::init(int period){
  Task::init(period);
  lastWCCleaningCount = 0;
  state = IDLE;    
}
  
void SelfCleaningTask::tick(){
  switch (state){
    case IDLE: {
      int num = pContext->getWCUsageCount();
      int delta = num - lastWCCleaningCount;
      if (!pContext->isSomeoneInside() && delta > NMAX_USAGE){
        state = CLEANING;   
        light->switchOn();
        pContext->setCleaning(true);
        lastWCCleaningCount = num;  
        count = 0;
      }
      break;
    }
    case CLEANING: {
      count++;
      if (count > CLEANING_TIME){
        state = IDLE;
        pContext->setCleaning(false);
        light->switchOff();
      }
      break;
    }
  }
}

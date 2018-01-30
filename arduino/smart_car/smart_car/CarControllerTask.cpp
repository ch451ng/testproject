#include "CarControllerTask.h"

#include "LedExt.h"
#include "config.h"
#include "Logger.h"

#define CAR_MODALITY_OFF     '0'
#define CAR_MODALITY_MOVING  '1'
#define CAR_MODALITY_PARKED  '2'

CarControllerTask::CarControllerTask() {
  pLight = new LedExt(L1_PIN);   
  fadeAmount = 5;
  pMsgService = new MsgService(BT_TXD,BT_RXD);
}


void CarControllerTask::init(int period){
  Task::init(period);
  pMsgService->init();
  state = CAR_OFF;    
  ledIntensity = 0;
  defenceLevelUpdated = false;
  defenceLevel = -1;
}
  
void CarControllerTask::tick(){
  checkMsgs();
  switch (state){
    case CAR_OFF: {
      break;
    }
    case CAR_MOVING: {
      break;
    }
    case CAR_PARKED: {
      ledIntensity+=fadeAmount;
      pLight->setIntensity(ledIntensity);
      if (ledIntensity == 0 || ledIntensity == 255){
        fadeAmount = -fadeAmount;  
      }
      break;
    }
  }
}

void CarControllerTask::checkMsgs(){
   if (pMsgService->isMsgAvailable()){
     Msg* msg = pMsgService->receiveMsg();
     String content = msg->getContent();
     if (content.startsWith("sc:m")){
       char ch = content.charAt(4);
       if (ch == '0'){
         state = CAR_OFF;  
         pLight->switchOff();
         Logger::log("changed modality: CAR OFF");
       } else if (ch == '1'){
         state = CAR_MOVING;
         pLight->switchOff();
         Logger::log("changed modality: CAR MOVING");
       } else if (ch == '2'){
         state = CAR_PARKED;
         ledIntensity = 0;
         pLight->switchOn();
         Logger::log("changed modality: CAR PARKED");
       } else {
         /* wrong state */
         
       }
     } else if (content.startsWith("sc:doff")){
       defenceLevel = -1;
       Logger::log(String("defence stopped."));
       defenceLevelUpdated = true;
     } else if (content.startsWith("sc:d")){
       String slevel = content.substring(4);
       defenceLevel = (int) slevel.toInt();
       Logger::log(String("setting defence level to: ")+defenceLevel);
       defenceLevelUpdated = true;
     }
     delete msg;
   }
}

bool CarControllerTask::isDefenceLevelUpdated(){
  return defenceLevelUpdated;
}

int  CarControllerTask::fetchDefenceLevel(){
  defenceLevelUpdated = false;
  return defenceLevel;
}

bool CarControllerTask::isCarOff(){
  return state == CAR_OFF;
}

bool CarControllerTask::isCarMoving(){
  return state == CAR_MOVING;
}

bool CarControllerTask::isCarParked(){
  return state == CAR_PARKED;
}

bool CarControllerTask::notifyCarInRange(int dist){
  pMsgService->sendMsg(Msg(String("sc:r")+dist));
}

bool CarControllerTask::notifyNoCarsInRange(){
  pMsgService->sendMsg(Msg("sc:roff"));
}


bool CarControllerTask::notifyCollision(){
  pMsgService->sendMsg(Msg("sc:c"));
}

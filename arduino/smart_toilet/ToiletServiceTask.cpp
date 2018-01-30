#include "ToiletServiceTask.h"

ToiletServiceTask::ToiletServiceTask(SharedContext* pContext, MsgService* msgService){
  this->pContext = pContext;
  this->msgService = msgService;
  this->pContext = pContext;
}
  
void ToiletServiceTask::init(int period){
  Task::init(period);
}
  
void ToiletServiceTask::tick(){
  if (msgService->isMsgAvailable()) {
    Msg* msg = msgService->receiveMsg();    
    if (msg->getContent() == "req_nusers"){
      msgService->sendMsg("req_nusers:"+String(pContext->getNUsers()));
    } else if (msg->getContent() == "req_nusages"){
      msgService->sendMsg("req_nusages:"+String(pContext->getWCUsageCount()));
    } else if (msg->getContent() == "req_state"){
      String alarm = pContext->isAlarmOn() ? "alarm" : "no_alarm";
      String busy = pContext->isSomeoneInside() ? "busy":"free";
      String clean = pContext->isCleaning() ? "cleaning":"no_cleaning";
      msgService->sendMsg("req_state:("+alarm+","+busy+","+clean+")");
    } else {
      msgService->sendMsg("not understood.");  
    }
    delete msg;
  }  
}

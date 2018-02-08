/*
 * MessagingTask.cpp
 *
 *  Created on: 07 nov 2017
 *      Author: Luke
 */

#include "Arduino.h"
#include "Costant.h"
#include "enumerati.h"
#include "SerialMessagingTask.h"
#include "MsgService.h"
#include "MessagingTaskBT.h"

MessagingTaskBT::MessagingTaskBT(Shared* shared, MsgServiceBT* msgServiceBT, MsgService* msgService) {
	this->shared = shared;
	//this->close = close;
	this->msgServiceBT = msgServiceBT;
	this->msgService = msgService;
}

void MessagingTaskBT::init(int period){
	Task::init(period);
	//Serial.begin(9600);
}

void MessagingTaskBT::tick(){

	if (msgServiceBT->isMsgAvailable()) {
		Msg* msg = msgServiceBT->receiveMsg();
		String content = msg->getContent();
		if (content.startsWith("LR:")){
			shared->setLoginStatus(loginstatus::REQUEST);
			shared->setLoginMsg(content);
			msgService->sendMsg(content);
		}
		//TEMP

		//LVALUE (get set)

		delete msg;
	}
}







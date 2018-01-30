/*
 * MessagingTask.cpp
 *
 *  Created on: 07 nov 2017
 *      Author: Luke
 */

#include "MessagingTask.h"
#include "Arduino.h"
#include "Costant.h"
#include "enumerati.h"

MessagingTask::MessagingTask(Shared* shared, MsgService* msgService) {
	this->shared = shared;
	//this->close = close;
	this->msgService = msgService;
}

void MessagingTask::init(int period){
	Task::init(period);
	//Serial.begin(9600);
}

void MessagingTask::tick(){

	if (msgService->isMsgAvailable()) {
		Msg* msg = msgService->receiveMsg();
		if (msg->getContent() == "00") { // ON/SCAN
			shared->setRStatus(scanstatus::SCAN);
		} else {
			if (msg->getContent() == "01") { //TRACK
				shared->setRStatus(scanstatus::TRACK);
			} else {
				if (msg->getContent() == "02") { //OFF
					shared->setRStatus(scanstatus::IDLE);
				}
			}
		}
		delete msg;
	}
}







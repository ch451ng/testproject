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

MessagingTask::MessagingTask(Shared* shared,Button* close, MsgService* msgService) {
	this->shared = shared;
	this->close = close;
	this->msgService = msgService;
}

void MessagingTask::init(int period){
	Task::init(period);
	//Serial.begin(9600);
}

void MessagingTask::tick(){
	if (close->isPressed()){
		if (shared->getDistance() < DIST_CLOSE || !shared->isDetected()){
			shared->setCloseRequest(true);
		}
	} else {
		if (msgService->isMsgAvailable()) {
			Msg* msg = msgService->receiveMsg();
			if (msg->getContent() == "OPEN"){
				shared->setOpenRequest(true);
			} else {
				if (msg->getContent() == "STOP"){
					if (shared->isDetected()){
						if (shared->getDist() == proxstatus::CANSTOP || shared->getDist() == proxstatus::TOUCH) {
							msgService->sendMsg("OK");
							shared->setCloseRequest(true);
						} else {
								msgService->sendMsg("TOO FAR");
						}
					}
				} else {
					msgService->sendMsg("Available command: OPEN, STOP");
				}
				delete msg;
			}
		}
	}
}






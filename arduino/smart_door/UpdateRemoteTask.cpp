/*
 * UpdateRemoteTask.cpp
 *
 *  Created on: 28 gen 2018
 *      Author: Luke
 */

#include "UpdateRemoteTask.h"

UpdateRemoteTask::UpdateRemoteTask(Shared* shared, TempSensor* temp1,
		MsgService* msgService, MsgServiceBT* msgServiceBT) {
	this->shared = shared;
	//this->led = ld1;
	this->temp = temp1;
	this->msgService = msgService;
	this->msgServiceBT = msgServiceBT;
}

void UpdateRemoteTask::init(int period) {
	Task::init(period);
	lastTemp = -375;
	lastInt = -1;
}

void UpdateRemoteTask::tick() {

	int curTemp = temp->readTemperature();
	if (abs(lastTemp - curTemp) > 5) {
		lastTemp = curTemp;
		msgService->sendMsg("UT:" + String(lastTemp));
		//msgServiceBT->sendMsg("UT:" + String(lastTemp));
		shared->setTemp(lastTemp);
	} else {
		delay(500);
		int meanTemp = (lastTemp + curTemp +  temp->readTemperature()) / 3;
		if (lastTemp != meanTemp) {
			lastTemp = meanTemp;

			msgService->sendMsg("UT:" + String(lastTemp));
			//msgServiceBT->sendMsg("UT:" + String(lastTemp));
			shared->setTemp(lastTemp);
		}
	}

	int curInt = shared->getLedIntensity();
	if (lastInt != curInt) {
		lastInt = curInt;
		msgService->sendMsg("UI:" + String(lastInt));
	}

}

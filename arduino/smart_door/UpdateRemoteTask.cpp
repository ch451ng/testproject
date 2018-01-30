/*
 * UpdateRemoteTask.cpp
 *
 *  Created on: 28 gen 2018
 *      Author: Luke
 */



#include "UpdateRemoteTask.h"

UpdateRemoteTask::UpdateRemoteTask(Shared* shared, TempSensor* temp1, MsgService* msgService){
	this->shared = shared;
	//this->led = ld1;
	this->temp = temp1;
	this->msgService = msgService;
}

void UpdateRemoteTask::init(int period){
	Task::init(period);
	lastTemp = -375;
	lastInt = -1;
}

void UpdateRemoteTask::tick() {
	float curTemp = temp->readTemperature();
	if (lastTemp != curTemp){
		lastTemp = curTemp;
		msgService->sendMsg("UT:" + String(lastTemp));
		//msgServiceBT->sendMsg("UT:" + String(lastTemp));
		shared->setTemp(lastTemp);
	}

	int curInt = shared->getLedIntensity();
	if (lastInt != curInt){
		lastInt = curInt;
		msgService->sendMsg("UI:" + String(lastInt));
	}

}

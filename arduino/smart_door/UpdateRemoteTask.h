/*
 * UpdateRemoteTask.h
 *
 *  Created on: 28 gen 2018
 *      Author: Luke
 */

#ifndef UPDATEREMOTETASK_H_
#define UPDATEREMOTETASK_H_

#include "Task.h"

#include "enumerati.h"
#include "Shared.h"

#include "MsgService.h"



class UpdateRemoteTask: public Task {
private:

	Shared* shared;

	TempSensor* temp;
	MsgService* msgService;
	MsgServiceBT* msgServiceBT;
	float lastTemp;
	int lastInt;

public:

	UpdateRemoteTask(Shared* shared, TempSensor* temp1, MsgService* msgService,MsgServiceBT* msgServiceBT);
	void init(int period);
	void tick();
};



#endif /* UPDATEREMOTETASK_H_ */

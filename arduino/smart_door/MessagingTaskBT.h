/*
 * MessagingTask.h
 *
 *  Created on: 07 nov 2017
 *      Author: Luke
 */

#ifndef SMART_DOOR_MESSAGINGTASKBT_H_
#define SMART_DOOR_MESSAGINGTASKBT_H_


#include "Task.h"
#include "Shared.h"
//#include "Button.h"
#include "MsgServiceBT.h"

class MessagingTaskBT: public Task {

public:

	MessagingTaskBT(Shared* share, MsgServiceBT* msgServiceBT, MsgService* msgService);
	void init(int period);
	void tick();

private:
	MsgService* msgService;
	MsgServiceBT* msgServiceBT;
	Shared* shared;
	//Button* close;
};




#endif /* SMART_GARAGE_MESSAGINGTASK_H_ */

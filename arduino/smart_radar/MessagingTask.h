/*
 * MessagingTask.h
 *
 *  Created on: 07 nov 2017
 *      Author: Luke
 */

#ifndef SMART_GARAGE_MESSAGINGTASK_H_
#define SMART_GARAGE_MESSAGINGTASK_H_


#include "Task.h"
#include "Shared.h"
//#include "Button.h"
#include "MsgService.h"

class MessagingTask: public Task {

public:

	MessagingTask(Shared* share, MsgService* msgService);
	void init(int period);
	void tick();

private:
	MsgService* msgService;
	Shared* shared;
	//Button* close;
};




#endif /* SMART_GARAGE_MESSAGINGTASK_H_ */

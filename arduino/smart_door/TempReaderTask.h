/*
 * TempReaderTask.h
 *
 *  Created on: 04 feb 2018
 *      Author: Luke
 */

#ifndef TEMPREADERTASK_H_
#define TEMPREADERTASK_H_


#include "Task.h"

#include "enumerati.h"
#include "Shared.h"

#include "TempSensor.h"



class TempReaderTask: public Task {
private:

	Shared* shared;

	TempSensor* temp;
	int readTemp;
	int lastTemp;
	int lastInt;
	int count;

public:

	TempReaderTask(Shared* shared, TempSensor* temp1);
	void init(int period);
	void tick();
};

#endif /* TEMPREADERTASK_H_ */

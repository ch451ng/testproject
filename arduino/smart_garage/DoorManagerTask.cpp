/*
 * DoorManagerTask.cpp
 *
 *  Created on: 07 nov 2017
 *      Author: Luke
 */

#include "DoorManagerTask.h"
#include "LedExt.h"
#include "enumerati.h"
#include "Arduino.h"

DoorManagerTask::DoorManagerTask(Shared* shared, LightExt* door){
	this->shared = shared;
	this->led = door;
}

void DoorManagerTask::init(int period){
	Task::init(period);
	state = doorstatus::CLOSE;
	led->switchOn();
	led->setIntensity(0);
}

void DoorManagerTask::tick(){
	switch (state){
	case doorstatus::CLOSE: {
		if (shared->openRequest()){
			openingCNT = 0;
			intensity = 0;
			shared->setOpenRequest(false);
			shared->setCloseRequest(false);
			shared->setDetected(false);
			state = doorstatus::OPENING;
		}
		break;
	}
	case doorstatus::OPENING: {

		if (shared->closeRequest()){
			shared->setCloseRequest(false);
			shared->setDetectorStatus(false);
			shared->setDetected(false);
			state = doorstatus::CLOSING;
		} else {
			openingCNT++;
			if (openingCNT < 40 ){
				intensity += 5;
				led->setIntensity(intensity);
				if (intensity >= 250) {
					shared->setOpenRequest(false);
					shared->setDetectorStatus(true);
					waitingCNT = 0;
					state = doorstatus::OPEN;

				}
			} else {
				shared->setDetectorStatus(true);
				shared->setOpenRequest(false);
				waitingCNT = 0;
				state = doorstatus::OPEN;
			}
		}
		break;
	}
	case doorstatus::OPEN: {
		waitingCNT++;
		if (shared->isDetected() && !shared->closeRequest()){
			shared->setDetectorStatus(false);

		} else {
			if ( waitingCNT >200  ||  shared->closeRequest()){
				shared->setDetectorStatus(false);
				shared->setDetected(false);
				state = doorstatus::CLOSING;
			}
		}
		break;
	}
	case doorstatus::CLOSING: {
		if (shared->openRequest()){
			shared->setOpenRequest(false);
			state = doorstatus::OPENING;
		} else {
			openingCNT--;
			if(openingCNT >= 0){
				intensity -= 5;
				led->setIntensity(intensity);
				if (intensity <= 0){
					shared->setCloseRequest(false);
					state = doorstatus::CLOSE;
				}
			} else {
				shared->setCloseRequest(false);
				state = doorstatus::CLOSE;
			}
		}
		break;
	}
	}
}


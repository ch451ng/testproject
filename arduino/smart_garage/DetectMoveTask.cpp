/*
 * DetectMoveTask.cpp
 *
 *  Created on: 08 nov 2017
 *      Author: Luke
 */

#include "DetectMoveTask.h"

#include "Pir.h"
#include "Arduino.h"
#include "enumerati.h"

DetectMoveTask::DetectMoveTask(Shared* shared, PresenceSensor* sensor, MsgService* msgService){
  this->detector = sensor;
  this->shared = shared;
  this->msgService = msgService;
}

void DetectMoveTask::init(int period){
  Task::init(period);
  state = detectmvstatus::IDLE;
}

void DetectMoveTask::tick(){
  switch (state){
  	  case detectmvstatus::IDLE:
  		if (shared->detectorStatus()) {
  			if (detector->isDetected()){
  				 msgService->sendMsg("Welcome home");
  				 shared->setDetected(true);
  				state = detectmvstatus::DM1;
  			} else {
  				shared->setDetected(false);
  				state = detectmvstatus::DM0;
  			}
  		}
  		break;

  	  case detectmvstatus::DM0:
  		  if (shared->detectorStatus()){
  			  if (detector->isDetected() ){
  				   msgService->sendMsg("Welcome home");
  				  shared->setDetected(true);
  				  state = detectmvstatus::DM1;
  			  }
  		  } else {
  			  state = detectmvstatus::IDLE;
  		  }
  		  break;
  	  case detectmvstatus::DM1:
  		  if (shared->detectorStatus()){
  			  if (!detector->isDetected()){
  				  shared->setDetected(false);
  				  state = detectmvstatus::DM0;
  			  }
  		  } else {
  			 state = detectmvstatus::IDLE;
  		  }
  		  break;
  }
}

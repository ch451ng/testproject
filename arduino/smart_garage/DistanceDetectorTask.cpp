/*
 * DistanceDetectorTask.cpp
 *
 *  Created on: 09 nov 2017
 *      Author: Luke
 */

#include "DistanceDetectorTask.h"
#include "LedExt.h"
#include "enumerati.h"
#include "Arduino.h"
#include "Sonar.h"

DistanceDetectorTask::DistanceDetectorTask(Shared* shared, LightExt* ld1, LightExt* ld2,ProximitySensor* prox, Button* touch,MsgService* msgService) {
	// TODO Auto-generated constructor stub
	this->shared = shared;
	this->led1 = ld1;
	this->led2 = ld2;
	this->sensor = prox;
	this->touch = touch;
	this->msgService = msgService;
}

void DistanceDetectorTask::init(int period){
	Task::init(period);
	state = proxstatus::IDLE;
	led1->switchOn();
	led1->setIntensity(0);
	led2->switchOn();
	led2->setIntensity(0);
}

void DistanceDetectorTask::SetDisplay(LightExt* ld1, LightExt* ld2, int intensity){
	if (intensity > 255 && intensity <= 510){
		ld1->setIntensity(255);
		ld2->setIntensity(intensity-255);
	} else {
		if (intensity >= 0 && intensity <= 255){
			ld1->setIntensity(intensity);
			ld2->setIntensity(0);
		} else {
			if (intensity < 0){
				ld1->setIntensity(0);
				ld2->setIntensity(0);
			} else {
				ld1->setIntensity(255);
				ld2->setIntensity(255);
			}
		}
	}
}
void DistanceDetectorTask::tick(){
	int intensity;
	float dist;
	switch (state){
	case proxstatus::IDLE:
		if (shared->isDetected()){
			dist = sensor->getDistance();
			intensity = 510 - (((dist-DIST_MIN)/0.45)*255);
			shared->setDistance(dist);
			if (dist > DIST_MAX){
				SetDisplay(led1,led2,0);
				state = proxstatus::TOODIST;
				shared->setDist(state);
			} else {
				msgService->sendMsg("Distance: " + String(dist));
				SetDisplay(led1,led2,intensity);
				if (dist > DIST_CLOSE){
					state = proxstatus::APPROACH;
					shared->setDist(state);
				} else {
					if (dist < DIST_MIN){
						msgService->sendMsg("OK CAN STOP");
						state = proxstatus::CANSTOP;
						shared->setDist(state);
					} else {
						state = proxstatus::INSIDE;
						shared->setDist(state);
					}
				}
			}
		}
		break;
	case proxstatus::TOODIST:
		if (!shared->isDetected()){
			SetDisplay(led1,led2,0);
			state = proxstatus::IDLE;
			shared->setDist(state);
		} else {
			SetDisplay(led1,led2,0);
			dist = sensor->getDistance();
			shared->setDistance(dist);
			if (dist <= DIST_MAX) {
				msgService->sendMsg("Distance: " + String(dist));
				intensity = 510 - (((dist-DIST_MIN)/0.45)*255);
				SetDisplay(led1,led2,intensity);

				if (dist >= DIST_CLOSE){
					state = proxstatus::APPROACH;
					shared->setDist(state);
				} else {
					if (dist > DIST_MIN){
						state = proxstatus::INSIDE;
						shared->setDist(state);
					} else {
						msgService->sendMsg("OK CAN STOP");
						state = proxstatus::CANSTOP;
						shared->setDist(state);
					}
				}
			}
		}
		break;

	case proxstatus::APPROACH:
		if (!shared->isDetected()){
			SetDisplay(led1,led2,0);
			state = proxstatus::IDLE;
			shared->setDist(state);
		} else {
			dist = sensor->getDistance();
			intensity = 510 - (((dist-DIST_MIN)/0.45)*255);
			SetDisplay(led1,led2,intensity);
			shared->setDistance(dist);
			if (dist > DIST_MAX) {
				state = proxstatus::TOODIST;
				shared->setDist(state);
			} else {
				msgService->sendMsg("Distance: " + String(dist));
				if (dist < DIST_MIN){
					msgService->sendMsg("OK CAN STOP");
					state = proxstatus::CANSTOP;
					shared->setDist(state);
				} else {
					if (dist < DIST_CLOSE) {
						state = proxstatus::INSIDE;
						shared->setDist(state);
					}
				}
			}
		}

		break;

	case proxstatus::INSIDE:
		if (!shared->isDetected()){
			SetDisplay(led1,led2,0);
			state = proxstatus::IDLE;
			shared->setDist(state);
		} else {
			dist = sensor->getDistance();
			intensity = 510 - (((dist-DIST_MIN)/0.45)*255);
			SetDisplay(led1,led2,intensity);
			shared->setDistance(dist);
			if (dist > DIST_MAX) {
				state = proxstatus::TOODIST;
				shared->setDist(state);
			} else {
				msgService->sendMsg("Distance: " + String(dist));
				if (dist < DIST_MIN){
					msgService->sendMsg("OK CAN STOP");
					state = proxstatus::CANSTOP;
					shared->setDist(state);
				} else {
					if (dist >= DIST_CLOSE) {
						state = proxstatus::APPROACH;
						shared->setDist(state);
					}
				}
			}
		}
		break;

	case proxstatus::CANSTOP:
		if (!shared->isDetected()){
			SetDisplay(led1,led2,0);
			state = proxstatus::IDLE;
			shared->setDist(state);
		} else {
			if (touch->isPressed()){
				msgService->sendMsg("TOUCHING");
				state = proxstatus::TOUCH;
				shared->setDist(state);
			} else {
				dist = sensor->getDistance();
				shared->setDistance(dist);
				if (dist > DIST_MAX) {
					state = proxstatus::TOODIST;
					shared->setDist(state);
				} else {
					msgService->sendMsg("Distance: " + String(dist));
					if (dist >= DIST_CLOSE){
						state = proxstatus::APPROACH;
						shared->setDist(state);
					} else {
						if (dist >= DIST_MIN){
							state = proxstatus::INSIDE;
							shared->setDist(state);
						}
					}
				}
			}
		}
		break;

	case proxstatus::TOUCH:
		if (!touch->isPressed()){
			msgService->sendMsg("OK CAN STOP");
			state = proxstatus::CANSTOP;
			shared->setDist(state);
		}

		break;

	}
}

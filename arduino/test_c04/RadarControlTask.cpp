/*
 * RadarControlTask.cpp
 *
 *  Created on: 02 dic 2017
 *      Author: Luke
 */

#include "RadarControlTask.h"
#include "LedExt.h"
#include "enumerati.h"
#include "Arduino.h"
#include "ServoTimer2.h"

RadarControlTask::RadarControlTask(Shared* shared, LightExt* ld1,
		ProximitySensor* prox, RadarDrive* servo, MsgService* msgService) {
	// TODO Auto-generated constructor stub
	this->shared = shared;
	this->led = ld1;
	this->sensor = prox;
	this->drive = servo;
	this->msgService = msgService;
}

void RadarControlTask::init(int period) {
	Task::init(period);
	state = scanstatus::IDLE;
	led->switchOn();
	led->setIntensity(0);
	angolo = ANG_START;
	inc = 1;
	drive->setPositionT2(angolo);
	periodo = period;

}

void RadarControlTask::tick() {
	switch (state) {
	case scanstatus::IDLE: {
		if (shared->getRStatus() == scanstatus::SCAN) {

			led->setIntensity(254);
			state = scanstatus::SCAN;
			speedCNT = 0;
		}
	}
	break;
	case scanstatus::SCAN: {
		if (shared->getRStatus() == scanstatus::TRACK) {

			state = scanstatus::TRACK;
		} else if (shared->getRStatus() == scanstatus::IDLE) {
			led->setIntensity(0);
			angolo = ANG_START;
			drive->setPositionT2(angolo);
			state = scanstatus::IDLE;
		} else {

			float distanza = fetchDistance();
			msgService->sendMsg("D:" + String(distanza) + "A:" + String(angolo));

			speedCNT++;
			if (speedCNT >= OMEGA / periodo) {
				drive->setPositionT2(angolo);
				if (angolo >= 180 || angolo <= 0)
					inc = -inc;
				angolo += inc;
				speedCNT = 0;
			}
		}
	}
	break;
	case scanstatus::TRACK: {
		if (shared->getRStatus() == scanstatus::IDLE) {
			led->setIntensity(0);
			drive->setPositionT2(ANG_START);
			state = scanstatus::IDLE;
		} else if (shared->getRStatus() == scanstatus::SCAN) {
			state = scanstatus::SCAN;
		}
		float distanza = fetchDistance();
		msgService->sendMsg("D:" + String(distanza) + "A:" + String(angolo));
		break;
	}
	}
}

float RadarControlTask::fetchDistance() {
	float distance = sensor->getDistance();
	if (abs(distance - lastDistance) > DIST_SPIKE) {
		distance = sensor->getDistance();
	}
	lastDistance = distance;
	return distance;
}

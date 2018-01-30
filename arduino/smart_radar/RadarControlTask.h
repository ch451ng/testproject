/*
 * RadarControlTask.h
 *
 *  Created on: 02 dic 2017
 *      Author: Luke
 */

#ifndef RADARCONTROLTASK_H_
#define RADARCONTROLTASK_H_

#include "Task.h"
#include "LedExt.h"
#include "enumerati.h"
#include "Shared.h"
#include "ProximitySensor.h"
#include "RadarDrive.h"
#include "Costant.h"
#include "MsgService.h"

#define DIST_SPIKE 0.50
#define ANG_START 90
#define OMEGA 500 //un grado ogni OMEGA ms

class RadarControlTask: public Task {
private:
	//float distance;
	int angolo;
	int remappedAngolo;
	int inc;
	float lastDistance = DIST_SPIKE + 1;
	int speedCNT;

	LightExt* led;
	scanstatus state;
	Shared* shared;
	ProximitySensor* sensor;
	RadarDrive* drive;
	MsgService* msgService;
	int periodo;

	float fetchDistance();
public:

	RadarControlTask(Shared* shared, LightExt* ld1, ProximitySensor* prox, RadarDrive* servo, MsgService* msgService);
	void init(int period);
	void tick();
};

#endif /* RADARCONTROLTASK_H_ */

/*
 * Shared.cpp
 *
 *  Created on: 07 nov 2017
 *      Author: Luke
 */

#include "Shared.h"

#include "enumerati.h"

Shared::Shared() {
	// TODO Auto-generated constructor stub
	detected = false;
	openSGN = false;
	closeSGN = false;
	enableDetector = false;
	distance = -1;
}

bool Shared::isDetected(){
	return detected;
}

void Shared::setDetected(bool detected){
	this->detected = detected;
}


bool Shared::openRequest(){
	return openSGN;
}

void Shared::setOpenRequest(bool openSGN){
	this->openSGN = openSGN;
}

bool Shared::closeRequest(){
	return closeSGN;
}

void Shared::setCloseRequest(bool closeSGN){
	this->closeSGN = closeSGN;
}

bool Shared::detectorStatus(){
	return this->enableDetector;
}

void Shared::setDetectorStatus(bool enableDetector){
	this->enableDetector = enableDetector;
}

float Shared::getDistance(){
	return this->distance;
}

void Shared::setDistance(float dist){
	this->distance = dist;
}

proxstatus Shared::getDist(){
	return this->dist;
}
void Shared::setDist(proxstatus dist){
	this->dist = dist;

}

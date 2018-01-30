/*
 * Shared.cpp
 *
 *  Created on: 07 nov 2017
 *      Author: Luke
 */

#include "Shared.h"
#include "enumerati.h"

Shared::Shared() {
	received_status = scanstatus::IDLE;
}

scanstatus Shared::getRStatus(){
	return this->received_status;
}

void Shared::setRStatus(scanstatus rStatus){
	this->received_status = rStatus;
}



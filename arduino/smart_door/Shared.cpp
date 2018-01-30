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
	login_status = loginstatus::IDLE;
	login_msg = "";
	ledInt = 0;
	temp = -375;
}

scanstatus Shared::getRStatus(){
	return this->received_status;
}

void Shared::setRStatus(scanstatus rStatus){
	this->received_status = rStatus;
}

scanstatus Shared::getLoginStatus(){
	return this->login_status;
}

void Shared::setLoginStatus(loginstatus rStatus){
	this->login_status = rStatus;
}

String Shared::getLoginMsg(){
	return this->login_msg;
}

void Shared::setLoginMsg(String msg){
	this->login_msg = msg;
}

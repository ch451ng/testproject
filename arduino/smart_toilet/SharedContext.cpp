#include "SharedContext.h"

SharedContext::SharedContext(){
  inside = false;
  inUse = false;
  wcUsageCount = 0;
  cleaning = false;  
  alarm = false;
  userCount = 0;
};

void SharedContext::setAlarm(bool alarm){
	this->alarm = alarm;
};

bool SharedContext::isAlarmOn(){
	return alarm;
};

int SharedContext::getNUsers(){
	return userCount;
};

void SharedContext::trackNewUser(){
	userCount++;
};

bool SharedContext::isInUse(){
	return inUse;
};

void SharedContext::setUsing(bool inUse){
	this->inUse = inUse;
};    

bool SharedContext::isSomeoneInside(){
	return inside;
};

void SharedContext::setSomeoneInside(bool inside){
	this->inside = inside;
};  


void SharedContext::trackNewWCUsage(){
  wcUsageCount++;    
};

int SharedContext::getWCUsageCount(){
  return wcUsageCount;
};

bool SharedContext::isCleaning(){
  return cleaning;
};

void SharedContext::setCleaning(bool cleaning){
  this->cleaning = cleaning;
}



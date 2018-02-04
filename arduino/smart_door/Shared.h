#ifndef __SHARED__
#define __SHARED__

#include "enumerati.h"
#include "Arduino.h"

class Shared {
public:
	Shared();
	scanstatus getRStatus();
	void setRStatus(scanstatus rStatus);
	loginstatus getLoginStatus();
	void setLoginStatus(loginstatus rStatus);
	String getLoginMsg();
	void setLoginMsg(String msg);
	int getLedIntensity();
	void setLedIntensity(int ledInt);
	float getTemp();
	void setTemp(float temp);


private:
	scanstatus received_status;
	loginstatus login_status;
	String login_msg;
	int ledInt;
	float temp;
};

#endif

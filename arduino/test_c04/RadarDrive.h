/*
 * RadarDrive.h
 *
 *  Created on: 02 dic 2017
 *      Author: Luke
 */

#ifndef RADARDRIVE_H_
#define RADARDRIVE_H_


#include "ServoTimer2.h"
//#include "PWMServo.h"

class RadarDrive {

	public:
		RadarDrive(int pin);
		//void setPosition(int value);
		void setPositionT2(int value);
	private:
		int pin;
		ServoTimer2 servo;
};

#endif /* RADARDRIVE_H_ */

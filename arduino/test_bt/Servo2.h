/*
 * RadarDrive.h
 *
 *  Created on: 02 dic 2017
 *      Author: Luke
 */

#ifndef SERVO2_H_
#define SERVO2_H_


#include "ServoTimer2.h"
//#include "PWMServo.h"

class Servo2 {

	public:
		Servo2(int pin);
		//void setPosition(int value);
		void setPositionT2(int value);
	private:
		int pin;
		ServoTimer2 servo;
};

#endif /* SERVO2_H_ */

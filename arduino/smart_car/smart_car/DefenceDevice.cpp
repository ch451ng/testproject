#include "DefenceDevice.h"

#include "Arduino.h"
#include "Logger.h"

DefenceDevice::DefenceDevice(int pin){
  this->pin = pin; 
  servo.attach(pin); 
}

void DefenceDevice::setLevel(int pos){
  int value = pos*1.8;
  if (value > 180){
    value = 180;
  } else if (value < 0){
    value = 0; 
  }
  Logger::log(String("driving servo to ")+value);
  servo.write(value);
}

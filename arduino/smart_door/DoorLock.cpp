#include "Arduino.h"

#include "DoorLock.h"

DoorLock::DoorLock(int pin){
  this->pin = pin; 
  servo.attach(pin); 
}

void DoorLock::setLevel(int pos){
  int value = pos*1.8;
  if (value > 180){
    value = 180;
  } else if (value < 0){
    value = 0; 
  }
  servo.write(value);
}

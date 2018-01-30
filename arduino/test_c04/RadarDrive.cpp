#include "RadarDrive.h"
//#include "ServoTimer2.h"
#include "Arduino.h"
//#include "Logger.h"

RadarDrive::RadarDrive(int pin){
  this->pin = pin;
  servo.attach(pin);
}

void RadarDrive::setPositionT2(int pos){
  int remappedAngolo = map(pos, 0, 180, 750, 2250);
  int value = remappedAngolo;
  servo.write(value);
}

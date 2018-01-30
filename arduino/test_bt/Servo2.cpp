#include "Servo2.h"
//#include "ServoTimer2.h"
#include "Arduino.h"
//#include "Logger.h"

Servo2::Servo2(int pin){
  this->pin = pin;
  servo.attach(pin);
}

void Servo2::setPositionT2(int pos){
  int remappedAngolo = map(pos, 0, 180, 750, 2250);
  int value = remappedAngolo;
  servo.write(value);
}

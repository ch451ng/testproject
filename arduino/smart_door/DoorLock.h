#ifndef __DOOR_LOCK__
#define __DOOR_LOCK__

// #include <ServoTimer2.h>
#include <Servo.h>

class DoorLock {

public:
  DoorLock(int pin);
  
  /*
   * Level: 0 - off/closed, 100 - max
   */
  void setLevel(int value);

private:
  int pin;
  // ServoTimer2 servo;
  Servo servo;
};

#endif


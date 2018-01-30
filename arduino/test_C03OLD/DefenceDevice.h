#ifndef __DEFENCE_DEVICE__
#define __DEFENCE_DEVICE__

// #include <ServoTimer2.h>
#include <Servo.h>

class DefenceDevice {

public:
  DefenceDevice(int pin);
  
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


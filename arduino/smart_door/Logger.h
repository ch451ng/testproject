#ifndef __LOGGER__
#define __LOGGER__

#include "Arduino.h"

class Logger {
  public: 
    static void init();
    static void log(String msg);
};

#endif

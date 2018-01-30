#include "Logger.h"

void Logger::init(){
  Serial.begin(9600);
}

void Logger::log(String msg){
  Serial.println(msg);
}


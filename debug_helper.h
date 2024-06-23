#ifndef DEBUG_HELPER
#define DEBUG_HELPER

#include <Arduino.h>


#define DEBUG_MODE

#define INFO_WIFI

void debugMeseg(char* meseg){

  #ifdef DEBUG_MODE
    Serial.print(meseg);
    Serial.print('\n');
  #endif

}

void debugWifiInfo(char* meseg){
  #ifdef INFO_WIFI
    Serial.print(meseg);
    Serial.print('\n');
  #endif
}


#endif
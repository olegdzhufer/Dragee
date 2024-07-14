
#ifndef CHAR_LIST_H
#define CHAR_LIST_H

#include <pgmspace.h>

#define EMPTY_CHAR ""

const char initFirstLine[] PROGMEM = "      INIT.....   ";
const char initSecondLine[] PROGMEM = " Slava Ukraine";
const char initThirdLine[] PROGMEM = "     Smert Moskalam";


const char* HeatName PROGMEM = "HEAT";
const char* CoolingName PROGMEM = "COOLING";
const char* Fan PROGMEM = "FAN";
const char* Stop PROGMEM = "STOP";
const char* SettingName PROGMEM = "Setting";


const char* TCur PROGMEM = "TCur";
const char* TempCurr PROGMEM = "TempCurr:";
const char* TSet PROGMEM = "TSet";
const char* TempSet PROGMEM = "TempSet:";

const char* kpName PROGMEM = "Kp";
const char* kpDesc PROGMEM = "Kp :";

const char* kiName PROGMEM = "Ki";
const char* kiDesc PROGMEM = "Ki :";

const char* kdName PROGMEM = "Kd";
const char* kdDesc PROGMEM = "Kd :";

const char* Empty = "";

  


#endif
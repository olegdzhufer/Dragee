
#pragma once

#include <Arduino.h>
// #include "buildTime.h"

#define DEBUG 1

#define DEBUG_SERIAL_SPD 115200

#ifdef DEBUG
#define D_SerialBegin(...) Serial.begin(__VA_ARGS__);
#define D_print(fmt,...)       Serial.println(__VA_ARGS__)
#define D_write(fmt,...)       Serial.write(__VA_ARGS__)
#define D_println(fmt,...)     D_println(__VA_ARGS__)
#else
#define D_SerialBegin(bauds)
#define D_print(...)
#define D_write(...)
#define D_println(...)
#endif



#if defined(DEBUG) && DEBUG > 0
#define DEBUG_PRINT(fmt, ...) Serial.printf("%s C%d) " fmt "\r\n", \
							__func__, xPortGetCoreID(), \
							##__VA_ARGS__); 
#else
 #define DEBUG_PRINT(fmt, ...) /* Don't do anything in release builds */
#endif

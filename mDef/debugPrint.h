
#pragma once

#include <Arduino.h>


#ifdef DEBUG
#define D_SerialBegin(...) Serial.begin(__VA_ARGS__);
#define D_print(...)       Serial.print(__VA_ARGS__)
#define D_write(...)       Serial.write(__VA_ARGS__)
#define D_println(...)     D_println(__VA_ARGS__)
#else
#define D_SerialBegin(bauds)
#define D_print(...)
#define D_write(...)
#define D_println(...)
#endif

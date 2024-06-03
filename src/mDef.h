#ifndef MDEF_H 
#define MDEF_H

#include <Arduino.h>
#include "pins.h"

#define DEBUG 0

#if (DEBUG == 1)
#define DEBUG_SERIAL Serial
#define DEBUG_BAUD 115200
#define DEBUG_BEGIN Serial.begin(DEBUG_BAUD)
#else
#define DEBUG_SERIAL 
#define DEBUG_BAUD 
#define DEBUG_BEGIN 
#endif


#define WIFI_SSID "ssid"
#define WIFI_PASS "pass"


#define __Kp 30
#define __Ki 0.7 
#define __Kd 200

#define LCD_ADDR 0x3F
#define LCD_ROWS 4
#define LCD_COLS 20

#define ONE_WIRE_BUS 13

#define STATUS_CODES \
    X(STATUS_OK       , 0)\
    X(FAIL          , -1)\
    X(UNDEFINED     , -2)\
    X(UNAUTHORIZED  , -3)\
    X(NOT_FOUND     , -4)\
    X(INTERNAL_ERROR, -5)\
    X(OUT_OF_MEMORY , -6)\
    X(OUT_OF_RANGE  , -7)\
    X(INVALID_ARG   , -8)\
    X(TIMEOUT       , -9)\
    X(READ_ERROR    , -10)\
    X(WRITE_ERROR   , -11)\
    X(OPEN_ERROR    , -12)\
    X(CLOSE_ERROR   , -13)\
    X(FLUSH_ERROR   , -14)\
    X(SEEK_ERROR    , -15)\
    X(I2C_ERROR   , -16)\

   
    
#define X(a, b) a = (b),
typedef enum {
	STATUS_CODES
} STATUS;
#undef X


#endif
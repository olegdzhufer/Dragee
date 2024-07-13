#ifndef MDEF_H 
#define MDEF_H

#include <Arduino.h>
#include <stdio.h>

//Section

#define ENC_S
#define BTN_S
#define RELAY_S
#define TIMER_S
#define WIFI_S
#define MENU_S
#define TEMP_S
#define FILE_S
#ifdef WIFI_S
  #define WEB_S
#endif


// Debug mod

// #define DEBUG
// #define DEBUG_FUNC

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


#if defined(DEBUG) && DEBUG > 0
#define DEBUG_PRINT(fmt, ...) Serial.printf("%s, %s: F%s L%s in %s C%d) " fmt "\r\n", \
							__DATE__, __TIME__, __FILE__, __LINE__, __func__, xPortGetCoreID(), \
							##__VA_ARGS__); 

#define DEBUG_FUNC(fmt, ...) Serial.printf("%s CoreId:%d)" fmt "\r\n", \
                            __func__, xPortGetCoreID(), \
                            ##__VA_ARGS__)
#else
 #define DEBUG_PRINT(fmt, ...) /* Don't do anything in release builds */
 #define DEBUG_FUNC(fmt, ...) /* Don't do anything in release builds */
#endif



#define STATUS_CODES \
    X(STATUS_OK     , 0)\
    X(FAILURE       , -1)\
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
    X(I2C_ERROR     , -16)\
    X(FS_NOT_INITED     , -17)\

#define X(a, b) a = (b),
typedef enum {
    STATUS_CODES
} STATUS_t;
#undef X


#endif
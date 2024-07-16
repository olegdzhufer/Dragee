#ifndef MDEF_H 
#define MDEF_H

#include <Arduino.h>

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
    X(DALLAS_NO_CALLBACK , -127)\

#define X(a, b) a = (b),
typedef enum {
    STATUS_CODES
} STATUS_t;
#undef X


#endif
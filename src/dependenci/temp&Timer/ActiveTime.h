#ifndef ACTIVETIME_H
#define ACTIVETIME_H

// #include <Arduino.h>

typedef struct ActiveTime
{
    uint8_t h;
    uint8_t m;
    uint8_t s;

    char* (*getTime)(ActiveTime* timer);

}ActiveTime;


#endif
#ifndef TIMELOGIC_H
#define TIMELOGIC_H
/**
 * uint32_t seconds = millis() / 1000, minutes, hours;
 minutes = seconds / 60;
 seconds %= 60;
 hours = minutes / 60;
 minutes %= 60;
*/
#include <Arduino.h>
#include <stdint.h>
#include "../mDef.h"
#include "time.h"

#define COUNTIMER_MAX_HOURS 999
#define COUNTIMER_MAX_MINUTES_SECONDS 59

#ifndef IN_HOURS
#define IN_HOURS 3600L
#endif

#ifndef IN_MINUTES
#define IN_MINUTES 60L
#endif

#ifndef IN_SECONDS
#define IN_SECONDS 1000L
#endif

 clock_t sec = millis() / 1000ul;      
 clock_t timeHours = (sec / 3600ul);        
 clock_t timeMins = (sec % 3600ul) / 60ul;  
 clock_t timeSecs = (sec % 3600ul) % 60ul;  


const u32 TimeInterval = 3000; // 3s

#endif
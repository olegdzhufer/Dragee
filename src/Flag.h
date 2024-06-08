#ifndef FLAG_H
#define FLAG_H

#include <Arduino.h>

/**
 * 0 bit - FAN status (on = 1, off = 0)
 * 1 bit - HEAP screan (onscreen = 1)
 * 2 bit - HEAP status (on = 1, off = 0)
 * 3 bit - COOLING screan (onscreen = 1)
 * 4 bit - COOLING status (on = 1, off = 0)
 * 5 bit - STOP mode (on = 1, off = 0)
 * 6 bit - EMPTY
 * 7 bit - EMPTY
 */
uint8_t FLAG_CONTROL_REG = 0x00;


#define CONTOLE_FLAG FLAG_CONTROL_REG

//Flag FAN operation
#define FAN_FLAG    (1 << 0)

#define FAN_CHECK   (CONTOLE_FLAG & FAN_FLAG)

#define FAN_ON      CONTOLE_FLAG |= FAN_FLAG
#define FAN_OFF     CONTOLE_FLAG &= ~FAN_FLAG

//________________________________________________


//Flag HEAP operation
#define HEAP_FLAG               (1 << 2)
#define HEAP_ONSCREEN_FLAG      (1 << 1)

#define HEAP_CHECK              (CONTOLE_FLAG & HEAP_FLAG)
#define HEAP_ONSCREEN_CHECK     (CONTOLE_FLAG & HEAP_ONSCREEN_FLAG)

#define HEAP_ONSCREEN           CONTOLE_FLAG |= HEAP_ONSCREEN_FLAG
#define HEAP_OURSCREEN          CONTOLE_FLAG &= ~HEAP_ONSCREEN_FLAG

#define HEAP_ONSCREEN           CONTOLE_FLAG |= HEAP_ONSCREEN_FLAG
#define HEAP_OURSCREEN          CONTOLE_FLAG &= ~HEAP_ONSCREEN_FLAG
#define HEAP_ON                 CONTOLE_FLAG |= HEAP_FLAG
#define HEAP_OFF                CONTOLE_FLAG &= ~HEAP_FLAG

//________________________________________________

//Flag HEAP operation
#define COOLING_FLAG               (1 << 4)
#define COOLING_ONSCREEN_FLAG      (1 << 3)

#define COOLING_CHECK              (CONTOLE_FLAG & COOLING_FLAG)
#define COOLING_ONSCREEN_CHECK     (CONTOLE_FLAG & COOLING_ONSCREEN_FLAG)

#define COOLING_ONSCREEN           CONTOLE_FLAG |= COOLING_ONSCREEN_FLAG
#define COOLING_OURSCREEN          CONTOLE_FLAG &= ~COOLING_ONSCREEN_FLAG

#define COOLING_ONSCREEN           CONTOLE_FLAG |= COOLING_ONSCREEN_FLAG
#define COOLING_OURSCREEN          CONTOLE_FLAG &= ~COOLING_ONSCREEN_FLAG
#define COOLING_ON                 CONTOLE_FLAG |= COOLING_FLAG
#define COOLING_OFF                CONTOLE_FLAG &= ~COOLING_FLAG

//________________________________________________


//

#endif

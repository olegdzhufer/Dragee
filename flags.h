#ifndef FLAG_H
#define FLAG_H

#include <Arduino.h>

/**
 * 0 bit - FAN status (on = 1, off = 0)
 * 1 bit - HEAT screan (onscreen = 1)
 * 2 bit - HEAT status (on = 1, off = 0)
 * 3 bit - COOLING screan (onscreen = 1)
 * 4 bit - COOLING status (on = 1, off = 0)
 * 5 bit - STOP mode (on = 1, off = 0)
 * 6 bit - EMPTY
 * 7 bit - ERROR BTN OR ENC FLAG
 */
uint8_t FLAG_CONTROL_REG = 0x00;

/**
 * 0 bit - Init flag (1 - ready to work, 0 - init is not complete)
 * 1 bit - Inti section flag (1- all variable ok, 0 - work (init) is not complete)
 * 2 bit - Update Menu flag (1 - time to update, 0 - not need update now)
 * 3 bit - EMPTY
 * 4 bit - EMPTY
 * 5 bit - EMPTY
 * 6 bit - EMPTY
 * 7 bit - ERROR MENU FLAG
 */
uint8_t FLAG_MENU_REG = 0x00;



#define CONTROL_FLAG   FLAG_CONTROL_REG
#define MENU_FLAG       FLAG_MENU_REG

//Flag FAN operation

#define FAN_CHECK   (CONTROL_FLAG & (1 << 0))
#define FAN_ON      (CONTROL_FLAG |= (1 << 0))
#define FAN_OFF     (CONTROL_FLAG &= ~(1 << 0))

//________________________________________________


//Flag HEAT operation

#define HEAT_CHECK              (CONTROL_FLAG & (1 << 2))
#define HEAT_ONSCREEN_CHECK     (CONTROL_FLAG &  (1 << 1))


#define HEAT_ONSCREEN           (CONTROL_FLAG |=  (1 << 1))
#define HEAT_OURSCREEN          (CONTROL_FLAG &= ~ (1 << 1))
#define HEAT_ON                 (CONTROL_FLAG |= (1 << 2))
#define HEAT_OFF                (CONTROL_FLAG &= ~(1 << 2))

//________________________________________________

//Flag HEAT operation

#define COOLING_CHECK              (CONTROL_FLAG & (1 << 4))
#define COOLING_ONSCREEN_CHECK     (CONTROL_FLAG & (1 << 3))

#define COOLING_ONSCREEN           (CONTROL_FLAG |= (1 << 3))
#define COOLING_OURSCREEN          (CONTROL_FLAG &= ~(1 << 3))

#define COOLING_ONSCREEN           (CONTROL_FLAG |= (1 << 3))
#define COOLING_OURSCREEN          (CONTROL_FLAG &= ~(1 << 3))
#define COOLING_ON                 (CONTROL_FLAG |= (1 << 4))
#define COOLING_OFF                (CONTROL_FLAG &= ~(1 << 4))

//________________________________________________


//Flag Stop operation


#define STOP_CHECK  (CONTROL_FLAG &  (1 << 5))
#define STOP_ON     (CONTROL_FLAG |=  (1 << 5) )
#define STOP_OFF    (CONTROL_FLAG &= ~ (1 << 5)) 

//________________________________________________

//------------------ERROR_SECTION--------------------


#define DROP_ERROR_BTN_ENC  (CONTROL_FLAG |=  (1 << 7))
#define CHECK_ERROR         (CONTROL_FLAG &  (1 << 7))

//---------------------------------------------------


// |____________________________________________________________________________________________________________________|
// |__________________________________________________|__MENU_FLAG_|____________________________________________________|
// |____________________________________________________________________________________________________________________|


#define COMPLETE_INIT_MENU          (MENU_FLAG & (1 << 0))
#define COMPLETE_INIT_SECTION_MENU  (MENU_FLAG &  (1 << 1))
#define CHECK_UPDATE_MENU           (MENU_FLAG & (1 << 2))         

//------------------------ERORR_SECTION------------------------


//-------------------------------------------------------------


#endif


#ifndef INCVAR_H
#define INCVAR_H

#include <Arduino.h>
#include <MenuLib.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Ticker.h>
#include <EncButton.h>
#include <PIDController.h>

#include "pins.h"



static Menu menu;
Line* curLine ;
Ticker temperatureTicker;


//flag to use
uint8_t REG_FLAG = 0x00;

/**
 * 
 * 0 - bit flag updata LCD
 * 1 - bit flag updata tepm data
 * 2 - bit flag data in enc
 * 3 - bit flag button pres
 * 4 - bit flag FAN status
 * 5 - bit Change mode
 * 6 - bit flag setup LCD
 * 7 - bit flag end init Menu
 */ 
#define RELOAD_LCD  (1 << 0) 
#define RELOAD_TEMP (1 << 1)
#define ENC_INT     (1 << 2)
#define BTN_INT     (1 << 3)
#define FAN_STATUS  (1 << 4)
#define CHANGEMOD   (1 << 5)
#define SETUP_LCD   (1 << 6)
#define READY_LCD   (1 << 7)





uint8_t REG_FLAG_S = 0x00;


/*
* 0 - bit Heap Select
* 1 - bit Heap Status
* 2 - bit Cooling Select
* 3 - bit Cooling Status
* 4 - bit Stop Select
* 5 - bit Fan Select
* 6 - bit Timer Reset
* 7 - bit Timer
*/


#define HEAP_SELECT     (1 << 0)
#define HEAP_STATUS     (1 << 1)
#define COOLING_SELECT  (1 << 2)
#define COOLING_STATUS  (1 << 3)
#define STOP_SELECT     (1 << 4)
#define FAN_SELECT      (1 << 5)
#define TIMER_RESET     (1 << 6)
#define TIMER_STATUS    (1 << 7)

uint8_t REG_MENU_STATUS = STOP_SELECT;




//main
int encderVal = 0x00;
int press = 0;
int pressbtn = 0;
//________________________________


//btn
int buttonState = 0;
unsigned long debounceDelay = 0;
//________________________________


//menu
Screen* mainS;
Screen* Heap, *Cooling, *FAN, *STOP;
Line* TempSetH, *TempCurH, *TempSetC, *TempCurC, *TempCurF, *TempCurS;
float tcH = 0, tcC = 0 ;
//________________________________


//Enc

int enc_pre;
//________________________________


//relay
uint8_t RelayState1 = LOW;
uint8_t RelayState2 = LOW;
uint8_t RelayState3 = LOW;

bool changeRelayState1 = false;
bool changeRelayState2 = false;
bool changeRelayState3 = false;

bool relayState;
//__________________________________


//dallas
int count = 0;
//__________________________________


//Timer
float most_recent_temperature_measurement;
//___________________________________








#include "btn&enc/btns.h"
#include "temp&Timer/dallas_sensor.h"
#include "menu/menu.h"
#include "btn&enc/encoder.h"
#include "temp&Timer/TimerSet.h"
#include"temp&Timer/ActiveTime.h"


#include"main_work_function_block.h"



#endif
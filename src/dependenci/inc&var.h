#ifndef INCVAR_H
#define INCVAR_H

#include <Arduino.h>
#include <Menulib.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Ticker.h>
#include <EncButton.h>
#include <PIDController.h>

#include "pins.h"



static Menu menu;
Ticker temperatureTicker;


//flag to use

// 0 - bit flag updata LCD
// 1 - bit flag updata tepm data
// 2 - bit flag data in enc
// 3 - bit flag button pres
// 4 - bit flag FAN status
// 5 - bit flag Stop mode
// 6 - bit flag setup LCD
// 7 - bit flag end init Menu

uint8_t REG_FLAG = 0x00;


#define RELOAD_LCD  (1 << 0)
#define RELOAD_TEMP (1 << 1)
#define ENC_INT     (1 << 2) //interapt
#define BTN_INT     (1 << 3) //interapt
#define FAN_STATUS  (1 << 4)
#define STOP_MODE   (1 << 5)
#define SETUP_LCD   (1 << 6)
#define READY_LCD   (1 << 7)



//0 - bit HEAP
//1 - bit COOLING
//2 - bit STOP
//3 - bit Start Heap
//4 - bit Start Cooling

uint8_t REG_STATUS = 0x01;

#define HEAP_SELECT     (1 << 0)
#define COOLING_SELECT  (1 << 1)
#define STOP_SELECT     (1 << 2)
#define HEAP_ON         (1 << 3)
#define COOLING_ON      (1 << 4)


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



#endif
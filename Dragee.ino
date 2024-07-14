#include <Arduino.h>


#include "mDef.h"
#include "settings.h"
#include "timerThermo.h"


#include "menu.h"


#include "RTC.h"
#include "countTimer.h"
#include "relay.h"
#include "Pid.h"

#include "btns.h"




#ifdef ENC_S
  #include "Enc.h"
#endif





void setup()
{

  setupSystem();



  setupTime();
 

  #ifdef MENU_S
    initSection();
  #endif

  #ifdef TIMER_S
    timer_setup();
  #endif

  #ifdef RELAY_S
    relaySetup();  
  #endif  

  initDaysArray(); // Initialise the array for storage and set some values


  #ifdef TEMP_S
    startSensor();
  #endif

  actuateHeating(OFF);
  lastTimerSwitchCheck = millis() + timerCheckDuration; 

  #ifdef BTN_S
    btnsSetup();
  #endif
  


  #ifdef ENC_S
    encoder_setup();
  #endif


  timerCool.onTimer();
  timerHeat.onTimer();

}

void loop()
{ 
  #ifdef BTN_S
    btnsLoop(); 
  #endif

  #ifdef RELAY_S
    relayTick();
  #endif

  #ifdef ENC_S
    read_encoder();
  #endif

  #ifdef MENU_S
    lcdLoop();
  #endif

  #ifdef TIMER_S
    timer_loop();
  #endif

  #ifdef TEMP_S
    sensorTempLoop();
  #endif

  loopPID();
}



void AssignSensorReadingsToArray()
{
  #ifdef DEBUG_FUNC
    Serial.println(__func__);
  #endif
  
  SensorReading[1][0] = 1;
  SensorReading[1][1] = Temperature;
  SensorReading[1][2] = RelayState;
  AddReadingToSensorData(1, Temperature); 
}

void AddReadingToSensorData(byte RxdFromID, float Temperature)
{ 
  #ifdef DEBUG_FUNC
    Serial.println(__func__);
  #endif
  byte ptr, p;
  ptr = SensorReadingPointer[RxdFromID];
  sensordata[RxdFromID][ptr].Temp = Temperature;
  ptr++;
  if (ptr >= SensorReadings){
    p = 0;
    do{
      sensordata[RxdFromID][p].Temp = sensordata[RxdFromID][p + 1].Temp;
      p++;
    } while (p < SensorReadings);
    ptr = SensorReadings - 1;
    sensordata[RxdFromID][SensorReadings - 1].Temp = Temperature;
  }
  SensorReadingPointer[RxdFromID] = ptr;
}


void setupSystem()
{
  Serial.begin(115200); // Initialise serial communications
  Serial.setDebugOutput(true);
  delay(200);

  #ifdef DEBUG
    Serial.println(__FILE__);
    Serial.println("Starting...");
  #endif

  
}





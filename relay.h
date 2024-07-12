#ifndef RELAY_H
#define RELAY_H

// #include <Arduino.h>
#include "settings.h"
#include "menu.h"
#include "countTimer.h"
#include "Pid.h"

class Relay
{
private:
  uint8_t pin;
  uint8_t state = false;
  uint8_t changeFlag = false;
  Line* CurrLine = NULL;
  simpPid *pidElement;
  float* tempR = NULL;
  bool statusTemp = false;

public:
  bool allowed = true;
  bool isMain = false;


  Screen *screen = NULL;

  Relay()
  {
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif
  }

  Relay(uint8_t pin, uint8_t initState = LOW, Screen* screen = NULL)
  {
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif
    this->pin = pin;
    this->state = initState;

    pinMode(pin, OUTPUT);
    digitalWrite(pin, state);

    if(screen != NULL)
    {
      attachScreen(screen);
    }
  }

  void setLine(Line* line, float* temp){
    this->CurrLine = line;
    this->tempR = temp;
  }

  void getLine(){
    if(this->CurrLine && this->tempR){
      temp = this->tempR;
      currLine = this->CurrLine;
      this->statusTemp = true;
    }
  }
  void setNull(){
    temp = NULL;
    currLine = NULL;
    this->statusTemp = false;
  }

  void setPid(simpPid* pid){
    if(pid){
      this->pidElement = pid;
    }
  }

  bool attachScreen(Screen* screen)
  {
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif
    if(screen != NULL)
    {
      this->screen = screen;
      return true;
    }
    return false;
  }

  void setMain(bool value)
  {
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif
    isMain = value;
  }

  void setAllowed(bool value)
  {
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif
    allowed = value;
  }

  void toggleFlag()
  {
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif
    changeFlag = !changeFlag;


  }

  void toggle()
  {
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif
    Serial.println(this->screen->name);
    state = !state;
    digitalWrite(pin, state);

  }

  bool workStatus(){
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif
    return this->state;
  }

  void tick()
  {
    if (allowed || isMain)
    {
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif

      if (isMain)
      {
        allowed = state;
      }

      if (changeFlag)
      {
        changeFlag = false;
        toggle();

        if(this->screen != NULL && this->workStatus()){
          menu.curr = this->screen;
          FLAG_LCD = true;
        }
        if(this->statusTemp){
          this->getLine();
        }else{
          this->setNull();
        }
        
      }
      
    }
    else
    {
      if (state == HIGH)
      {
        state = LOW;
        digitalWrite(pin, state);
      }
    }

    // if(this->state && this->pidElement){
      
    //   this->pidElement->PidActivate();
    //   this->pidElement->tickPid();
    // }else{
    //   this->pidElement->PidDeactivate();
    //   this->relayOff();
    // }
  }

  void relayOff(){
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif
    temp = NULL;
    currLine = NULL;
    state = LOW;
    digitalWrite(pin, state);
  }
  void relayOn(){
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif

    state = HIGH;
    digitalWrite(pin, state);
  }


  ~Relay(){
    this->screen = NULL;
  }
};
#ifdef RELAY_S

Relay relayHeat(HEAT_PIN, LOW, Heat);
Relay relayCool(COOL_PIN, LOW, Cooling);
Relay relayFan(FAN_PIN, LOW, FAN);

void relaySetup()
{
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif
  Serial.println(__FILE__);

  relayHeat.attachScreen(Heat);
  relayCool.attachScreen(Cooling);


  relayFan.attachScreen(FAN);

  relayHeat.setLine(TempSetH, &TargetTemp);

  relayFan.setMain(true);
}

void relayTick()
{
  relayHeat.tick();
  relayCool.tick();
  relayFan.tick();
}

#endif


#endif
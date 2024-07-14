#ifndef RELAY_H
#define RELAY_H

// #include <Arduino.h>
#include "settings.h"
#include "menu.h"
#include "countTimer.h"
#include "PID_v2.h"

typedef enum PidMode{
  HeatMode,
  CoolMode
} PidMode;

class Relay
{
private:
  uint8_t pin;
  uint8_t state = false;
  uint8_t changeFlag = false;
  Line* CurrLine = NULL;
  
  float* tempR = NULL;
  bool statusTemp = false;

  /* PID PARAM*/
public:
  uint32_t windowStartTime, WindowSize = 2000;
  double Output, tempLocal, target;
  PidMode modePid;
  PID *pidElement;

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

  void setPID(PID* pid){
    if(pid){
      this->pidElement = pid;
    }
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

  void PIDBegin(){
    if(this->pidElement){
      windowStartTime = millis();
      this->pidElement->SetOutputLimits(0, this->WindowSize);
      this->pidElement->SetMode(AUTOMATIC);
    }
  }

  void ResetK(){
    // this->pidElement
  }

  //#########################

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

  void PidRelayTick(){
    if(this->pidElement){
      this->pidElement->Compute();
      if (millis() - this->windowStartTime > this->WindowSize){
        this->windowStartTime += this->WindowSize;
      }
      if (this->Output < millis() - this->windowStartTime){
        if(this->modePid == HeatMode) digitalWrite(this->pin, HIGH);
        else digitalWrite(this->pin, LOW);
      } 
      else {
        if(this->modePid == HeatMode) digitalWrite(this->pin, LOW);
        else digitalWrite(this->pin, HIGH);
      }
    }
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
    
    if(this->state && this->pidElement){
      this->tempLocal = (double)Temperature;
      this->target = (double)(*(this->tempR));
      this->PidRelayTick();
    }
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

PID pidCool(&relayCool.tempLocal, &relayCool.Output, &relayCool.target, Kp, Ki, Kd, DIRECT);
PID pidHeat(&relayHeat.tempLocal, &relayHeat.Output, &relayHeat.target, Kp, Ki, Kd, DIRECT);


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
  relayCool.setLine(TempSetC, &FrostTemp);
  
  relayFan.setMain(true);

  relayHeat.setPID(&pidHeat);
  relayCool.setPID(&pidCool);

  relayHeat.PIDBegin();
  relayCool.PIDBegin();

  relayHeat.modePid = PidMode::HeatMode;
  relayCool.modePid = PidMode::CoolMode;

}

void relayTick()
{
  relayHeat.tick();
  relayCool.tick();
  relayFan.tick();
}

#endif


#endif
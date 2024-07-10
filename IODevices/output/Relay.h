#ifndef RELAY_H
#define RELAY_H

#include "../../mDef.h"
#include "LedSts.h"


class Relay
{
private:
  u8 changeFlag = false;
  u8 pin;
  bool normallyOpen = false;

public:
  String name;
  u8 state = LOW;
  LedSts ledStatus;

  uint32_t timerStart=0;
  uint8_t timerSec=0;

  Relay* first_p=NULL;

  Relay* prev_p=NULL;
  Relay* next_p=NULL;


public:
  Relay() {}

  Relay(u8 pinRel, u8 pinLed, u8 initState = OFF, bool isNormallyOpen = false)
  {
    DEBUG_PRINT("Creating relay with");

    init(pinRel, initState, isNormallyOpen);
    ledStatus.init(pinLed, initState, isNormallyOpen);
    
  }

  void init(u8 pinRel, u8 initState = LOW, bool isNormallyOpen = false)
  {
    this->pin = pinRel;
    this->state = initState;
    this->normallyOpen = isNormallyOpen;
    pinMode(pin, OUTPUT);
    if (normallyOpen)
    {
      turnOn();
    }
    else
    {
      turnOff();
    }

     if(first_p == NULL){
       first_p = this;
     }
  }

  void setName(String name)
  {
    this->name = name;
  }

  String getName()
  {
    return name;
  }

  void toggleFlag()
  {
    // if (first_p == NULL)
    // {
      // return;
    // }
    
    // if((first_p->getState() == true) || (first_p == this)){
      changeFlag = !changeFlag;
    // ledStatus.toggle();
    // }
  }

  void toggle()
  {
    DEBUG_PRINT("Toggle relay state");
    // if (first_p == NULL)
    // {
      // return;
    // }

    // if((first_p->getState() == true) || (first_p == this))
    // {
      state = !state;
      DEBUG_PRINT("Relay state chenaged to %d", state);
      digitalWrite(pin, state);
      if (getState())
      {
        timerStart = millis();
        // timer->start();
      }else{
        // timer->stop();
        timerSec=0;
        timerStart = 0;
      }
    // }
  }

  bool getState()
  {
    if (normallyOpen)
    {
      return !state;
    }
    else
    {
      return state;
    }
  }

  void turnOn()
  {
    if (normallyOpen)
    {
      if (state == !true)
      {
        return;
      }
      state = !true;
    }
    else
    {
      if (state == true)
      {
        return;
      }
      state = true;
    }
    digitalWrite(pin, state);
  }

  void turnOff()
  {
    if (normallyOpen)
    {
      if (state == !false)
        return;
      state = !false;
    }
    else
    {
      if (state == false)
        return;
      state = false;
      timerSec=0;
      timerStart=0;
    }
    digitalWrite(pin, state);
  }

  void tick()
  {
    if (changeFlag)
    {
      changeFlag = false;
      ledStatus.toggle();
      toggle();
    }
    if (timerStart > 0)
    {
      if (millis() - timerStart >= 1000){
        Serial.print("1sec+ ");
        timerSec++;
        Serial.println(timerSec);
      }
    }
    
  }

  ~Relay(){}
};



#endif
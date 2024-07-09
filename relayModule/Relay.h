#ifndef RELAY_H
#define RELAY_H

#include "../mDef.h"
#include "LedSts.h"
#include "../Timer/CountTimer.h"

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
  Countimer timerSec;
  Countimer timerStart;
  static Relay* first_p;

public:
  Relay() {}

  Relay(u8 pinRel, u8 pinLed, u8 initState = LOW, bool isNormallyOpen = false)
  {
   #ifdef DEBUG_FUNC
    Serial.println(__func__);
    Serial.print("pin: ")
        Serial.println(pin);
   #endif

    init(pinRel, initState, isNormallyOpen);
    ledStatus.init(pinLed, initState, isNormallyOpen);
    // timerSec.setCounter(0, 0, 2, Countimer::COUNT_UP, NULL); //todo add lcd flag to update every sec
    timerStart.setCounter(24, 60, 60, Countimer::COUNT_UP, NULL);
    //timer.setInterval(callBackToTimer , 1000);
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
    if (first_p == NULL)
    {
      return;
    }
    
    if((first_p->getState() == true) || (first_p == this)){
      changeFlag = !changeFlag;
    // ledStatus.toggle();
    }
  }

  void toggle()
  {
    if (first_p == NULL)
    {
      return;
    }

    if((first_p->getState() == true) || (first_p == this))
    {
      state = !state;
      digitalWrite(pin, state);
      if (getState())
      {
        timerStart.start();
      }else{
        timerStart.stop();
      }
    }
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
  }

  ~Relay(){}
};



#endif
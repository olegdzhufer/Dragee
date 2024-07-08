#ifndef RELAY_H
#define RELAY_H

#include "../mDef.h"
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
  // TimerCount* timer = NULL;
  
public:
  Relay() {}

  Relay(u8 pinBtn, u8 pinLed, u8 initState = LOW, bool isNormallyOpen = false)
  {
#ifdef DEBUG_FUNC
    Serial.println(__func__);
    Serial.printt("pin: ")
        Serial.println(pin);
#endif

    init(pinBtn, initState, isNormallyOpen);
    ledStatus.init(pinLed, initState, isNormallyOpen);
  }

  void init(u8 pinBtn, u8 initState = LOW, bool isNormallyOpen = false)
  {
    this->pin = pinBtn;
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
    changeFlag = !changeFlag;
    // ledStatus.toggle();
  }

  void toggle()
  {
    state = !state;
    digitalWrite(pin, state);
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
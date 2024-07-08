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

  ~Relay()
  {
  }
};

class RelayList : public Relay
{
public:
  static RelayList *first_p;
  static RelayList *proc_relay_p;
  RelayList *next_p = NULL;
  RelayList *prev_p = NULL;

  RelayList(u8 pinBtn, u8 pinLed, u8 initState = LOW, bool isNormallyOpen = false)
  {
    Relay(pinBtn, pinLed, initState, isNormallyOpen);

    if (first_p == NULL)
    {
      first_p = this;
    }
  }

  static void tickAll()
  {
    if (first_p==NULL){
      return;
    }
      proc_relay_p = first_p;
      if(first_p->getState() == true)
      {
        proc_relay_p = first_p;
        while (proc_relay_p)
        {
          proc_relay_p->tick();
          proc_relay_p = proc_relay_p->next_p;
        }
      }else{
        first_p->tick();
      }
  
  }

  void setNext(RelayList *next_p)
  {
    if (next_p != NULL)
    {
      this->next_p = next_p;
      next_p->prev_p = this;
    }
  }


  void tick()
  {
    if ((first_p->getState() == true) || (this == first_p))
    {
      Relay::tick();
    }
    // if (first_p)
    // {
    //   if (this->next_p != NULL)
    //   {
    //     proc_relay_p = this->next_p;
    //   }
    //   else
    //   {
    //     // proc_relay_p = first_p;
    //     proc_relay_p = NULL;
    //   }
    // }
  }


  ~RelayList()
  {
    if (this->prev_p != NULL)
    {
      this->prev_p->next_p = this->next_p;
    }

    if (this->next_p != NULL)
    {
      this->next_p->prev_p = this->prev_p;
    }

    else if (first_p == this)
    {
      first_p = this->next_p;
    }
  }
};

#endif
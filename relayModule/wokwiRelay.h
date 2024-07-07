#ifndef RELAY_H
#define RELAY_H

#include "mDef.h"


class Relay
{
 public:
  uint8_t pin;
  String name;
  uint8_t state = LOW;
  uint8_t changeFlag = false;
  bool normallyOpen;

  u8 stsPin;

  

public:
  Relay(){}


  Relay(uint8_t pin, uint8_t initState = LOW, bool isNormallyOpen = false)
  {
#ifdef DEBUG_FUNC
    Serial.println(__func__);
    Serial.printt("pin: ")
        Serial.println(pin);
#endif

    init(pin, initState, isNormallyOpen);
  }


  void init(uint8_t pin, uint8_t initState = LOW, bool isNormallyOpen = false)
  {
    this->pin = pin;
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
#ifdef DEBUG_FUNC
    Serial.println(__func__);
#endif
    this->name = name;
  }


  String getName()
  {
#ifdef DEBUG_FUNC
    Serial.println(__func__);
#endif
    return name;
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
    state = !state;
    digitalWrite(pin, state);
  }


  bool getState()
  {
#ifdef DEBUG_FUNC
    Serial.println(__func__);
#endif

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
#ifdef DEBUG_FUNC
    Serial.println(__func__);
#endif
    if (normallyOpen)
    {
      if (state == !true)
        return;
      state = !true;
    }
    else
    {
      if (state == true)
        return;
      state = true;
    }
    digitalWrite(pin, state);
  }


  void turnOff()
  {
#ifdef DEBUG_FUNC
    Serial.println(__func__);
#endif
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
      toggle();
    }
  }

  ~Relay()
  {
#ifdef DEBUG_FUNC
    Serial.println(__func__);
#endif

    if (this->prev_p != NULL)
    {
      this->prev_p->next_p = this->next_p;
    }

    if (this->next_p != NULL)
    {
      this->next_p->prev_p = this->prev_p;
    }

  }
};



class RelayList: public Relay
{
public:
 static RelayList *first_p;
  static RelayList *proc_relay_p;
  RelayList *next_p = NULL;
  RelayList *prev_p = NULL;
  
  RelayList(uint8_t pin, uint8_t initState = LOW, bool isNormallyOpen = false)
  {
    Relay::init(pin, initState, isNormallyOpen);

    if (first_p == NULL)
    {
      first_p = this;
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
    Relay::tick();
    
    if (first_p)
    {
      if (this->next_p != NULL)
      {
        proc_relay_p = this->next_p;
      }
      else
      {
        proc_relay_p = NULL;
      }
    }
  }

};


#endif
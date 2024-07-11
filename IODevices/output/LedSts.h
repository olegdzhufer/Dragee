#ifndef LED_STS_H
#define LED_STS_H

#include <Arduino.h>
#include "../../mDef.h"

class LedSts
{
private:
   uint8_t pin;
   bool normallyOpen = false;
   bool state = LOW;

public:
    LedSts(){}; // default constructor

    LedSts(uint8_t pin, uint8_t initState = LOW, bool isNormallyOpen = false)
    {
      DEBUG_PRINT("Creating sts led");
        init(pin, initState, isNormallyOpen);
    }

    void init(uint8_t pin, uint8_t initState = LOW, bool isNormallyOpen = false)
    {
        this->pin = pin;
        this->state = initState;
        this->normallyOpen = isNormallyOpen;
        pinMode(pin, OUTPUT);
        digitalWrite(pin, state);
        // if (isNormallyOpen)
        // {
        //     turnOn();
        // }
        // else
        // {
        //     turnOff();
        // }
    }

  void turnOn()
  {
    DEBUG_PRINT("Turning ON sts led");
    if (normallyOpen)
    {
      if (state == !true){
        return;
      }
      state = !true;
    }
    else
    {
      if (state == true){
        return;
      }
      state = true;
    }
    digitalWrite(pin, state);
  }


  void turnOff()
  {
        DEBUG_PRINT("Turning OFF sts led");

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


  void toggle()
    {
        state = !state;
        DEBUG_PRINT("STSled state changed to %d", state);
        digitalWrite(this->pin, state);
    }


    // ~LedSts();

    friend class Relay;
    friend class SwitchButton;
};




#endif
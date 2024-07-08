#ifndef LED_STS_H
#define LED_STS_H

#include "../mDef.h"

class LedSts
{
private:
   u8 pin;
   bool normallyOpen = false;
   bool state = LOW;

public:
    LedSts(){}; // default constructor

    LedSts(u8 pin, u8 initState = LOW, bool isNormallyOpen = false)
    {
        init(pin, initState, isNormallyOpen);
    }

    void init(u8 pin, u8 initState = LOW, bool isNormallyOpen = false)
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
        digitalWrite(pin, state);
    }


    // ~LedSts();

    friend class Relay;
    friend class SwitchButton;
};




#endif
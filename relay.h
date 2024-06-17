#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>
#include "settings.h"

class Relay
{
private:
  uint8_t pin;
  uint8_t state = false;
  uint8_t changeFlag = false;

public:
  bool allowed = true;
  bool isMain = false;

  Relay()
  {
  }

  Relay(uint8_t pin, uint8_t initState = LOW)
  {
    init(pin, initState);
  }

  void init(uint8_t pin, uint8_t initState = LOW)
  {
    this->pin = pin;
    this->state = initState;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, state);
  }

  void setMain(bool value)
  {
    isMain = value;
  }

  void setAllowed(bool value)
  {
    allowed = value;
  }

  void toggleFlag()
  {
    changeFlag = !changeFlag;
  }

  void toggle()
  {
    state = !state;
    digitalWrite(pin, state);
  }

  void tick()
  {

    if (allowed || isMain)
    {

      if (isMain)
      {
        allowed = state;
      }

      if (changeFlag)
      {
        changeFlag = false;
        toggle();
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
  }

  ~Relay()
  {
  }
};

Relay relayHeat();
Relay relayCool();
Relay relayFan();

void relaySetup()
{
  Serial.println(__FILE__);
  
  relayHeat.init(HEAT_PIN, LOW);
  relayCool.init(COOL_PIN, LOW);
  relayFan.init(FAN_PIN, LOW);
  relayFan.setMain(true);
}

void relayTick()
{
  relayHeat.tick();
  relayCool.tick();
  relayFan.tick();
}

#endif
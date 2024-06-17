#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>
#include "settings.h"
#include "menu.h"
class Relay
{
private:
  uint8_t pin;
  uint8_t state = false;
  uint8_t changeFlag = false;

public:
  bool allowed = true;
  bool isMain = false;

  Screen *screen = NULL;

  Relay()
  {
  }

  Relay(uint8_t pin, uint8_t initState = LOW, Screen* screen = NULL)
  {
    this->pin = pin;
    this->state = initState;

    pinMode(pin, OUTPUT);
    digitalWrite(pin, state);

    if(screen != NULL)
    {
      attachScreen(screen);
    }
  }

  bool attachScreen(Screen* screen)
  {
    if(screen != NULL)
    {
      this->screen = screen;
      return true;
    }
    return false;
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

        menu.curr = screen;
        CHECK_UPDATE_MENU = true;
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

    this->screen = NULL;
  }
};

Relay relayHeat(HEAT_PIN, LOW);
Relay relayCool(COOL_PIN, LOW);
Relay relayFan(FAN_PIN, LOW);

void relaySetup()
{
  Serial.println(__FILE__);


  relayHeat.attachScreen(Heat);
  relayCool.attachScreen(Cooling);
  relayFan.attachScreen(FAN);

  relayFan.setMain(true);
}

void relayTick()
{
  relayHeat.tick();
  relayCool.tick();
  relayFan.tick();
}


#endif
#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>
#include "settings.h"
#include "menu.h"
#include "countTimer.h"



class Relay {
private:
  uint8_t pin;
  uint8_t state = false;
  uint8_t changeFlag = false;

public:
  bool allowed = true;
  bool isMain = false;

  Screen* screen = NULL;

  Relay() {
    Serial.println(__func__);
  }

  Relay(uint8_t pin, uint8_t initState = LOW, Screen* screen = NULL) {
    Serial.println(__func__);
    this->pin = pin;
    this->state = initState;

    pinMode(pin, OUTPUT);
    digitalWrite(pin, state);

    if (screen != NULL) {
      attachScreen(screen);
    }
  }

  bool attachScreen(Screen* screen) {
    Serial.println(__func__);
    if (screen != NULL) {
      this->screen = screen;
      return true;
    }
    return false;
  }

  void setMain(bool value) {
    Serial.println(__func__);
    isMain = value;
  }

  void setAllowed(bool value) {
    Serial.println(__func__);
    allowed = value;
  }

  void toggleFlag() {
    Serial.println(__func__);
    changeFlag = !changeFlag;
  }

  void toggle() {
    Serial.println(__func__);
    state = !state;
    digitalWrite(pin, state);
    if((this == &relayHeat || this == &relayCool) && state == true){
      startTimer();
    }else if ((this == &relayHeat || this == &relayCool) && state == false){
      stopTimer();
    }
  }

  bool workStatus() {
    Serial.println(__func__);
    return this->state;
  }

  void tick() {

    if (allowed || isMain) {
      Serial.println(__func__);

      if (isMain) {
        allowed = state;
      }

      if (changeFlag) {
        changeFlag = false;
        toggle();

        if (this->screen != NULL && this->workStatus()) {
          menu.curr = this->screen;
          FLAG_LCD = true;
        }
      }

    } else {
      if (state == HIGH) {
        state = LOW;
        digitalWrite(pin, state);
      }
    }
  }

  void relayOff() {
    state = LOW;
    digitalWrite(pin, state);
  }
  void relayOn() {
    state = HIGH;
    digitalWrite(pin, state);
  }

  ~Relay() {

    this->screen = NULL;
  }
};

Relay relayHeat(HEAT_PIN, LOW, Heat);
Relay relayCool(COOL_PIN, LOW, Cooling);
Relay relayFan(FAN_PIN, LOW, FAN);

void relaySetup() {
  Serial.println(__func__);
  Serial.println(__FILE__);

  relayHeat.attachScreen(Heat);
  relayCool.attachScreen(Cooling);
  relayFan.attachScreen(FAN);

  relayFan.setMain(true);
}

void relayTick() {
  relayHeat.tick();
  relayCool.tick();
  relayFan.tick();
}


#endif
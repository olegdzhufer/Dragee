#ifndef BTNS_DEF_H
#define BTNS_DEF_H

#include <Arduino.h>
#include <EncButton.h>
#include "settings.h"
#include "relay.h"


class ButtonSwitch : public VirtButton {
public:

  void (*callbackOnPress)() = NULL;

  ButtonSwitch() {}

  ButtonSwitch(uint8_t btnPin, uint8_t ledPin, uint8_t btnMode = INPUT_PULLUP, uint8_t btnLevel = LOW, uint8_t ledInitState = LOW) {
    init(btnPin, ledPin, btnMode, btnLevel, ledInitState);
  }

  void init(uint8_t btnPin, uint8_t ledPin, uint8_t btnMode = INPUT_PULLUP, uint8_t btnLevel = LOW, uint8_t ledInitState = LOW) {
    this->btnPin = btnPin;
    EB_mode(btnPin, btnMode);
    setBtnLevel(btnLevel);

    setLed(ledPin, ledInitState);
  }

  bool read() {
    return EB_read(btnPin) ^ bf.read(EB_INV);
  }

  bool tick() {
    bool tick = VirtButton::tick(EB_read(btnPin));
    if (tick) {
      pressedBtn();

      return true;
    }
    return false;
  }

  bool tickRaw() {
    return VirtButton::tickRaw(EB_read(btnPin));
  }


  void setLed(uint8_t ledPin, uint8_t ledState = LOW) {
    this->ledPin = ledPin;
    this->ledState = ledState;
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, ledState);
  }


  void toggleLed() {
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }


  void pressedBtn() {
    uint16_t btnState = VirtButton::action();
    switch (btnState) {

      case EB_CLICK:
        Serial.println("click");
        toggleLed();
        if (relay != NULL)
        {
          relay->toggleFlag();
        }
        
        callCallback();
        break;
      default:
        Serial.println("other action");
    }
  }

  void attachCallback(void (*callback)()) {
    this->callbackOnPress = callback;
  }

  void callCallback() {
    if (callbackOnPress != NULL) {
      callbackOnPress();
    }
  }

  bool attachRelay(Relay *relay) {
    if (relay == NULL)
    {
      return false;
    }
    this->relay = relay;
    return true;
  }



private:
  uint8_t btnPin;
  uint8_t ledPin;
  uint8_t ledState;

  Relay *relay=NULL;
};


ButtonSwitch btn1(BTN1_PIN, LED_PIN1, INPUT_PULLUP, LOW);
ButtonSwitch btn2(BTN2_PIN, LED_PIN2, INPUT_PULLUP, LOW);
ButtonSwitch btnSwitch(BTN3_PIN, LED_PIN3, INPUT_PULLUP, LOW);


void callbackSwitch() {

  switch (btnSwitch.action()) {

    case EB_HOLD:
      // FAN_ON;
      Serial.println("HOLD");
      break;

    case EB_RELEASE:
      // FAN_OFF;
      Serial.println("RELEASE");
      break;
    default:
      break;
  }
}


void callbackBtn1() {
  switch (btn1.action()) {

    case EB_CLICK:
      // Serial.println("Btn1 clicked");
      // if (!(HEAT_ONSCREEN)) {
      //   HEAT_ONSCREEN;
      //   FULL_OFF_COOLING;
      //   STOP_OFF;
      // } else if (HEAT_ONSCREEN && FAN_CHECK && !(HEAT_CHECK)) {
      //   HEAT_ON;
      //   FULL_OFF_COOLING;
      //   STOP_OFF;
      // } else if (HEAT_ONSCREEN && !(HEAT_CHECK) && !(FAN_CHECK)) {
      //   //Here plase code to print in MENU such as "FAN is not on !"

      // } else if (HEAT_ONSCREEN && HEAT_CHECK) {
      //   FULL_OFF_HEAT;
      //   STOP_ON;
      // }
      break;

    default:
      break;
  }
}

void callbackBtn2() {
  switch (btn2.action()) {
    // Serial.println("Btn2 clicked");
    case EB_CLICK:
      // if (!(COOLING_ONSCREEN)) {
      //   COOLING_ONSCREEN;
      //   FULL_OFF_HEAT;
      //   STOP_OFF;
      // } else if (COOLING_ONSCREEN && FAN_CHECK && !(COOLING_CHECK)) {
      //   COOLING_ON;
      //   FULL_OFF_HEAT;
      //   STOP_OFF;
      // } else if (COOLING_ONSCREEN && !(COOLING_CHECK) && !(FAN_CHECK)) {
      //   //Here plase code to print in MENU such as "FAN is not on !"

      // } else if (COOLING_ONSCREEN && COOLING_CHECK) {
      //   FULL_OFF_COOLING;
      //   STOP_ON;
      // }
      break;

    default:
      break;
  }
}

void heatControl(AsyncWebServerRequest *request) {
  String state = "OFF";
  if (request->hasParam("heat_state")) {
    String act_state = request->getParam("heat_state")->value();
    if (act_state == "1") {
      state = "ON";
      // HEAT_ON;
      request->send(200, "text/html", state);
    } else if (act_state == "0") {
      state = "OFF";
      // HEAT_OFF;
      request->send(200, "text/html", state);
    }
  }
}

void coldControl(AsyncWebServerRequest *request) {
  String state = "OFF";
  if (request->hasParam("cold_state")) {
    String act_state = request->getParam("cold_state")->value();
    if (act_state == "2") {
      state = "ON";
      // COOLING_ON;
      request->send(200, "text/html", state);
    } else if (act_state == "3") {
      state = "OFF";
      // COOLING_OFF;
      request->send(200, "text/html", state);
    }
  }
}

void fanControl(AsyncWebServerRequest *request) {
  String state = "OFF";
  if (request->hasParam("fan_state")) {
    String act_state = request->getParam("fan_state")->value();
    if (act_state == "4") {
      state = "ON";
      // FAN_ON;
      request->send(200, "text/html", state);
    } else if (act_state == "5") {
      state = "OFF";
      // FAN_OFF;
      request->send(200, "text/html", state);
    }
  }
}

void btnsSetup() {
  Serial.println(__FILE__);
  btn1.attachCallback(callbackBtn1);
  btn2.attachCallback(callbackBtn2);
  btnSwitch.attachCallback(callbackSwitch);

  btn1.attachRelay(&relayHeat);
  btn2.attachRelay(&relayCool);
  btnSwitch.attachRelay(&relayFan);
}

void btnsLoop() {
  btn1.tick();
  btn2.tick();
  btnSwitch.tick();
}


#endif
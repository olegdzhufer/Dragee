#ifndef BTNS_DEF_H
#define BTNS_DEF_H

#include <Arduino.h>
#include <EncButton.h>
#include "menu.h"
#include "settings.h"
#include "relay.h"


bool fan = false;

class ButtonSwitch : public VirtButton
{
public:
  void (*callbackOnPress)() = NULL;

  ButtonSwitch() {Serial.println(__func__);}

  ButtonSwitch(uint8_t btnPin, uint8_t ledPin, uint8_t btnMode = INPUT_PULLUP, uint8_t btnLevel = LOW, uint8_t ledInitState = LOW, bool workEn =false)
  {
    Serial.println(__func__);
    init(btnPin, ledPin, btnMode, btnLevel, ledInitState, workEn);
  }

  void init(uint8_t btnPin, uint8_t ledPin, uint8_t btnMode = INPUT_PULLUP, uint8_t btnLevel = LOW, uint8_t ledInitState = LOW, bool workEn =false)
  {
    Serial.println(__func__);
    this->btnPin = btnPin;
    this->workEn = workEn;
    EB_mode(btnPin, btnMode);
    setBtnLevel(btnLevel);

    setLed(ledPin, ledInitState);
  }

  bool read()
  {
    Serial.println(__func__);
    return EB_read(btnPin) ^ bf.read(EB_INV);
  }

  bool tick()
  {
    bool tick = VirtButton::tick(EB_read(btnPin));
    if (tick && this->workEn)
    {
      Serial.println(__func__);
      // Serial.print("check");
      pressedBtn();

      return true;
    }else{

    }
    return false;
  }

  void tickSwitch()
  {
    if (tick()&& this->workEn)
    {
      Serial.println(__func__);
      switch (VirtButton::action())
      {

      case EB_HOLD:
        // FAN_ON;
        fan = true;
        toggleLed();
        if (relay != NULL)
        {
          relay->toggleFlag();
        }
        callCallback();

        Serial.println("HOLD");
        break;

      case EB_RELEASE:
        // FAN_OFF;
        Serial.println(__func__);
        menu.curr = STOP;
        relay->toggleFlag();
        this->LedOff();
        fan = false;
        FLAG_LCD = true;
        Serial.println("RELEASE");
        break;
      default:
        break;
      }
    }
  }

  bool tickRaw()
  {
    Serial.println(__func__);
    return VirtButton::tickRaw(EB_read(btnPin));
  }

  void setLed(uint8_t ledPin, uint8_t ledState = LOW)
  {
    Serial.println(__func__);
    Serial.print("Led");
    this->ledPin = ledPin;
    this->ledState = ledState;
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, ledState);
  }

  void toggleLed()
  {
    Serial.println(__func__);
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }

  void pressedBtn()
  {
    uint16_t btnState = VirtButton::action();
    // Serial.println("Action \n");
    Serial.println(__func__);

    switch (btnState)
    {

    case EB_CLICK:
      // Serial.println("click");
      toggleLed();
      if (relay != NULL)
      {
        relay->toggleFlag();
      }
      callCallback();
      FLAG_LCD = true;
      break;
    default:
      Serial.println("other action");
    }
  }

  void attachCallback(void (*callback)())
  {
    Serial.println(__func__);
    this->callbackOnPress = callback;
  }

  void callCallback()
  {
    Serial.println(__func__);
    if (callbackOnPress != NULL)
    {
      callbackOnPress();
    }
  }

  bool attachRelay(Relay *relay)
  {
    Serial.println(__func__);
    if (relay == NULL)
    {
      return false;
    }
    this->relay = relay;
    return true;
  }

  void LedOff(){
    Serial.println(__func__);
    ledState = LOW;
    digitalWrite(ledPin, ledState);
  }
  void LedOn(){
    Serial.println(__func__);
    ledState = HIGH;
    digitalWrite(ledPin, ledState);
  }

  void OffMode(){
    Serial.println(__func__);
    this->LedOff();
    this->relay->relayOff();
  }

  void EnWork(){
    Serial.println(__func__);
    this->workEn = true;
  }
  void DeWork(){
    Serial.println(__func__);
    this->workEn = false;
    OffMode();
  }

private:
  uint8_t btnPin;
  uint8_t ledPin;
  uint8_t ledState;
  bool workEn = false;

  Relay *relay = NULL;
};

ButtonSwitch btn1(BTN1_PIN, LED_PIN1, INPUT_PULLUP, LOW);
ButtonSwitch btn2(BTN2_PIN, LED_PIN2, INPUT_PULLUP, LOW);
ButtonSwitch btnSwitch(BTN3_PIN, LED_PIN3, INPUT_PULLUP, LOW);

void callbackSwitch()
{
  Serial.println(__func__);
}

void callbackBtn1()
{
  Serial.println(__func__);
  switch (btn1.action())
  {

  case EB_CLICK:
    btn2.OffMode();
    break;

  default:
    break;
  }
}

void callbackBtn2()
{
  Serial.println(__func__);
  switch (btn2.action())
  {
  
  case EB_CLICK:
    btn1.OffMode();
    break;

  default:
    break;
  }
}

void heatControl(AsyncWebServerRequest *request)
{
  Serial.println(__func__);
  String state = "OFF";
  if (request->hasParam("heat_state"))
  {
    String act_state = request->getParam("heat_state")->value();
    if (act_state == "1")
    {
      state = "ON";
      // HEAT_ON;
      request->send(200, "text/html", state);
    }
    else if (act_state == "0")
    {
      state = "OFF";
      // HEAT_OFF;
      request->send(200, "text/html", state);
    }
  }
}

void coldControl(AsyncWebServerRequest *request)
{
  Serial.println(__func__);
  String state = "OFF";
  if (request->hasParam("cold_state"))
  {
    String act_state = request->getParam("cold_state")->value();
    if (act_state == "2")
    {
      state = "ON";
      // COOLING_ON;
      request->send(200, "text/html", state);
    }
    else if (act_state == "3")
    {
      state = "OFF";
      // COOLING_OFF;
      request->send(200, "text/html", state);
    }
  }
}

void fanControl(AsyncWebServerRequest *request)
{
  Serial.println(__func__);
  String state = "OFF";
  if (request->hasParam("fan_state"))
  {
    String act_state = request->getParam("fan_state")->value();
    if (act_state == "4")
    {
      state = "ON";
      // FAN_ON;
      request->send(200, "text/html", state);
    }
    else if (act_state == "5")
    {
      state = "OFF";
      // FAN_OFF;
      request->send(200, "text/html", state);
    }
  }
}

void btnsSetup()
{
  Serial.println(__func__);
  Serial.println(__FILE__);
  btn1.attachCallback(callbackBtn1);
  btn2.attachCallback(callbackBtn2);
  btnSwitch.EnWork();


  btn1.attachRelay(&relayHeat);
  btn2.attachRelay(&relayCool);
  btnSwitch.attachRelay(&relayFan);
}

void btnsLoop()
{
  if(fan){
    Serial.println(__func__);
    btn1.EnWork();
    btn2.EnWork();
  }else{
    Serial.println(__func__);
    btn1.DeWork();
    btn2.DeWork();
  }

  btn1.tick();
  btn2.tick();
  btnSwitch.tickSwitch();

}

#endif
#ifndef BTNS_DEF_H
#define BTNS_DEF_H

#include <EncButton.h>
#include "menu.h"
#include "countTimer.h"
#include "settings.h"
#include "relay.h"
#include "Pid.h"

bool fan = false;

class ButtonSwitch : public VirtButton
{
public:
  void (*callbackOnPress)() = NULL;

  ButtonSwitch() {    
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif
    }

  ButtonSwitch(uint8_t btnPin, uint8_t ledPin, uint8_t btnMode = INPUT_PULLUP, uint8_t btnLevel = LOW, uint8_t ledInitState = LOW, bool workEn =false)
  {
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif
    init(btnPin, ledPin, btnMode, btnLevel, ledInitState, workEn);
  }

  void init(uint8_t btnPin, uint8_t ledPin, uint8_t btnMode = INPUT_PULLUP, uint8_t btnLevel = LOW, uint8_t ledInitState = LOW, bool workEn =false)
  {
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif
    this->btnPin = btnPin;
    this->workEn = workEn;
    EB_mode(btnPin, btnMode);
    setBtnLevel(btnLevel);

    setLed(ledPin, ledInitState);
  }

  void addTimer(TimerCount* timer){
    if(timer){
      this->timer = timer;
    }
  }

  bool swichTimer(){
    if(this->timer){
      return this->timer->swichTimerMode();
    }
    return false;
  }
  void offTimer(){
    if(this->timer){
      this->timer->offTimer();
    }
  }
  void onTimer(){
    if(this->timer){
      this->timer->onTimer();
    }
  }

  bool read()
  {
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif

    return EB_read(btnPin) ^ bf.read(EB_INV);
  }

  bool tick()
  {
    bool tick = VirtButton::tick(EB_read(btnPin));
    if (tick && this->workEn)
    {
      #ifdef DEBUG_FUNC
        Serial.println(__func__);
        

      #endif

    #ifdef DEBUG
      Serial.print("check");
    #endif
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
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif
      switch (VirtButton::action())
      {

      case EB_HOLD:
        // FAN_ON;
        fan = true;
        toggleLed();
        if (this->relay != NULL)
        {
          relay->toggleFlag();
        }
        callCallback();
        #ifdef DEBUG
          Serial.println("HOLD");
        #endif
        
        break;

      case EB_RELEASE:
        // FAN_OFF;
        #ifdef DEBUG_FUNC
          Serial.println(__func__);
        #endif
        menu.curr = STOP;
        if(this->relay != NULL){
          relay->toggleFlag();
        }

        this->LedOff();
        fan = false;
        FLAG_LCD = true;

        #ifdef DEBUG
          Serial.println("RELEASE");
        #endif

        break;
      default:
        break;
      }
    }
  }

  bool tickRaw()
  {
    return VirtButton::tickRaw(EB_read(btnPin));
  }

  void setLed(uint8_t ledPin, uint8_t ledState = LOW)
  {

    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif

    #ifdef DEBUG
      Serial.print("Led");
    #endif
    
    this->ledPin = ledPin;
    this->ledState = ledState;
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, ledState);
  }

  void toggleLed()
  {
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }

  void pressedBtn()
  {
    uint16_t btnState = VirtButton::action();
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif

    switch (btnState){

    case EB_CLICK:
      this->state = !(this->state);
      toggleLed();
      if (relay != NULL){
        relay->toggleFlag();
      }
      callCallback();
      this->swichTimer();
      FLAG_LCD = true;
      break;

    default:
      #ifdef DEBUG
        Serial.println("other action");
      #endif
      break;
      
    }
  }

  void attachCallback(void (*callback)())
  {
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif
    this->callbackOnPress = callback;
  }

  void callCallback()
  {
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif
    if (callbackOnPress != NULL)
    {
      callbackOnPress();
    }
  }

  bool attachRelay(Relay *relay)
  {
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif
    if (relay == NULL)
    {
      return false;
    }
    this->relay = relay;
    return true;
  }

  void LedOff(){
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif
    ledState = LOW;
    digitalWrite(ledPin, ledState);
  }
  void LedOn(){
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif
    ledState = HIGH;
    digitalWrite(ledPin, ledState);
  }

  void OffMode(){
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif

    this->LedOff();
    this->offTimer();

    if(this->relay != NULL){
      this->relay->relayOff();
    }

    this->state = false;
  }

  void EnWork(){
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif

    this->workEn = true;
  }
  void DeWork(){

    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif

    this->workEn = false;
    OffMode();
    this->state = false;
  }

  bool getState(){
    return this->state;
  }

private:
  uint8_t btnPin;
  uint8_t ledPin;
  uint8_t ledState;
  bool workEn = false;
  TimerCount* timer = NULL;
  bool state = false;


  Relay *relay = NULL;
};



#ifdef BTN_S

ButtonSwitch btn1(BTN1_PIN, LED_PIN1, INPUT_PULLUP, LOW); //todo external
ButtonSwitch btn2(BTN2_PIN, LED_PIN2, INPUT_PULLUP, LOW);
ButtonSwitch btnSwitch(BTN3_PIN, LED_PIN3, INPUT_PULLUP, LOW);

#define ISR_BTN_MODE FALLING 

IRAM_ATTR void isrBtn() {
  btn1.tickRaw();
  btn2.tickRaw();
  btn3.tickRaw();
}


void callbackBtn1()
{
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif
  switch (btn1.action()){

  case EB_CLICK:
    btn2.OffMode();
    
    break;

  default:
    break;
  }
}

void callbackBtn2()
{
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif
  switch (btn2.action()){

  case EB_CLICK:
    btn1.OffMode();
    break;

  default:
    break;
  }
}

void btnsSetup()
{
  #ifdef DEBUG_FUNC
    Serial.println(__func__);
  #endif
  Serial.println(__FILE__);

  attachInterrupt(digitalPinToInterrupt(BTN1_PIN), isrBtn, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BTN2_PIN), isrBtn, ISR_BTN_MODE);
  attachInterrupt(digitalPinToInterrupt(BTN3_PIN), isrBtn, ISR_BTN_MODE);
  
  btnSwitch.EnWork();
  btn1.attachCallback(callbackBtn1);
  btn2.attachCallback(callbackBtn2);


  #ifdef RELAY_S
    btn1.attachRelay(&relayHeat);
    btn2.attachRelay(&relayCool);
    btnSwitch.attachRelay(&relayFan);
  #endif

  btn1.addTimer(&timerHeat);
  btn2.addTimer(&timerCool);

  
}

void btnsLoop()
{
  if(fan){
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif
    btn1.EnWork();
    btn2.EnWork();
    if(!(btn2.getState() || btn1.getState()) && menu.curr != FAN){
      menu.curr = FAN;
      FLAG_LCD = true;
    }
    btn1.tick();
    btn2.tick();
  }else{
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif
    btn1.DeWork();
    btn2.DeWork();
  }

  btnSwitch.tickSwitch();
  
}
#endif



#endif

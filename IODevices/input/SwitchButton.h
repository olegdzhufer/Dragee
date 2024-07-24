#ifndef BTNS_DEF_H
#define BTNS_DEF_H


#include "EncButton.h"
#include "../../mDef.h"
#include "../output/Relay.h"

typedef enum
{
  BTN_TYPE,
  SWITCH_TYPE
} BTN_PRESS_t;

class SwitchButton : public VirtButton
{
private:
  uint8_t btnPin=0;

public:
  BTN_PRESS_t type = BTN_TYPE;
  Relay *attached_relay_p = nullptr;
  func_p callbackOnPress = nullptr;

  SwitchButton(uint8_t btnPin, BTN_PRESS_t pressType, Relay *attachRelay_p=nullptr, uint8_t btnMode = INPUT, uint8_t btnLevel = HIGH)
  {
    DEBUG_PRINT("Creating switchbutton");

    init(btnPin, pressType);//, btnMode, btnLevel);
    
    if (attachRelay_p != nullptr)
    {
      attachRelay(attachRelay_p);
    }
  }


  void init(uint8_t btnPin, BTN_PRESS_t pressType, uint8_t btnMode = INPUT, uint8_t btnLevel = HIGH)
  {
    this->btnPin = btnPin;
    EB_mode(btnPin, btnMode);
    setBtnLevel(btnLevel);
  }

  uint8_t getPin()
  {
    if (this->btnPin == 0)
    {
      DEBUG_PRINT("ERROR: Button pin is not set");
    }
    
    return this->btnPin;
  }

  bool read()//get button current state immediately
  {
    return EB_read(btnPin) ^ bf.read(EB_INV);
  }


  bool tick()
  {
    bool tick = VirtButton::tick(EB_read(this->btnPin));
    if (tick)
    {
      DEBUG_PRINT("Button action in tick");
      action();

      // if (attached_relay_p)
      // {
      //   DEBUG_PRINT("Button attached_relay_p tick");
      //   attached_relay_p->tick();
      // }
      
      return true;
    }
    return false;
  }


  bool tickRaw()
  {
    // if (this->attached_relay_p != NULL)
    // {
    //     attached_relay_p->toggleFlag();
    // }
    return VirtButton::tickRaw(EB_read(btnPin));
  }

  void pressISR()
  {
    VirtButton::pressISR();
  }


  void action()
  {
    uint16_t btnState = VirtButton::action();
    if (type == SWITCH_TYPE)
    {
      DEBUG_PRINT("Action for type %d", (int)type);

      switch (btnState)
      {

      case EB_HOLD:
        DEBUG_PRINT("Call btn action is EB_HOLD");
        if (this->attached_relay_p != nullptr)
        {
          attached_relay_p->toggleFlag();
        }
        callCallback();
        break;

      case EB_RELEASE:
        DEBUG_PRINT("Call btn action is EB_RELEASE");

        if (this->attached_relay_p != nullptr)
        {
          attached_relay_p->toggleFlag();
        }
        break;

      default:
        break;
      }
    }
    else if (type == BTN_TYPE)
    {
       DEBUG_PRINT("Action for type %d", (int)type);
      switch (btnState)
      {
      case EB_CLICK:
        if (this->attached_relay_p != nullptr)
        {
           DEBUG_PRINT("Btn is clicked");
          attached_relay_p->toggleFlag();
        }
        callCallback();
        break;

      default:
        break;
      }
    }
  }


  bool setCallback(func_p callback)
  {
    if (callback != nullptr)
    {
       this->callbackOnPress = callback;
        return true;
    }
   return false;
  }


  void callCallback()
  {
    if (callbackOnPress != nullptr)
    {
       DEBUG_PRINT("Call btn callback");
      callbackOnPress();
    }
  }


  bool attachRelay(Relay *relay)
  {
    if (relay == nullptr)
    {
      return false;
    }
     DEBUG_PRINT("Relay attached");
    this->attached_relay_p = relay;
    return true;
  }
  
};




#endif
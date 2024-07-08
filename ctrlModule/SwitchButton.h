#ifndef BTNS_DEF_H
#define BTNS_DEF_H

#include <EncButton.h>
#include "../mDef.h"
#include "../relayModule/Relay.h"
// #include "Pid.h"

typedef enum
{
  BTN_TYPE,
  SWITCH_TYPE
} BTN_PRESS_t;

class SwitchButton : public VirtButton
{
private:
  uint8_t btnPin;

public:
  BTN_PRESS_t type;
  Relay *attached_relay_p = NULL;
  func_p callbackOnPress = NULL;


  SwitchButton() {}


  SwitchButton(uint8_t btnPin, BTN_PRESS_t pressType, Relay *attachRelay_p=NULL, uint8_t btnMode = INPUT, uint8_t btnLevel = LOW)
  {
    init(btnPin, pressType, btnMode, btnLevel);
    if (attachRelay != NULL)
    {
      attachRelay(attachRelay_p);
    }
  }


  void init(uint8_t btnPin, BTN_PRESS_t pressType, uint8_t btnMode = INPUT, uint8_t btnLevel = LOW)
  {
    this->btnPin = btnPin;
    EB_mode(btnPin, btnMode);
    setBtnLevel(btnLevel);
  }


  bool read()//get button current state immediately
  {
    return EB_read(btnPin) ^ bf.read(EB_INV);
  }


  bool tick()
  {
    bool tick = VirtButton::tick(EB_read(btnPin));
    if (tick)
    {
      action();
      return true;
    }
    return false;
  }


  bool tickRaw()
  {
    return VirtButton::tickRaw(EB_read(btnPin));
  }


  void action()
  {
    uint16_t btnState = VirtButton::action();
    if (type == SWITCH_TYPE)
    {
      switch (btnState)
      {

      case EB_HOLD:
        if (this->attached_relay_p != NULL)
        {
          attached_relay_p->toggleFlag();
        }
        callCallback();
        break;

      case EB_RELEASE:
        if (this->attached_relay_p != NULL)
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
      switch (btnState)
      {
      case EB_CLICK:
        if (relay != NULL)
        {
          relay->toggleFlag();
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
    if (callback != NULL)
    {
       this->callbackOnPress = callback;
        return true;
    }
   return false;
  }


  void callCallback()
  {
    if (callbackOnPress != NULL)
    {
      callbackOnPress();
    }
  }


  bool attachRelay(Relay *relay)
  {
    if (relay == NULL)
    {
      return false;
    }
    this->attached_relay_p = relay;
    return true;
  }
  
};


class BtnList : public SwitchButton
{
public:
  static BtnList *first_p;
  static BtnList *proc_btn_p;
  BtnList *next_p = NULL;

  BtnList() {}
  
  BtnList(uint8_t btnPin, BTN_PRESS_t pressType, Relay *attachRelay_p = NULL, uint8_t btnMode = INPUT, uint8_t btnLevel = LOW)
  {
    SwitchButton::init(btnPin, pressType, attachRelay_p, btnMode, btnLevel);

    if (first_p == NULL)
    {
      first_p = this;
    }
  }


  void setNext(BtnList *next_p)
  {
    if (next_p != NULL)
    {
      this->next_p = next_p;
    }
  }

  static void tickAll()
  {
    if (first_p)
    {
      proc_btn_p = first_p;
      while (proc_btn_p)
      {
        proc_btn_p->tick();
        proc_btn_p = proc_btn_p->next_p;
      }
    }
  }

  void tick()
  {
    SwitchButton::tick();
    if (first_p)
    {
      if (this->next_p != NULL)
      {
        proc_btn_p = this->next_p;
      }
      else
      {
        // proc_btn_p = first_p;
        proc_btn_p = NULL;
      }
    }
  }

  ~BtnList()
  {
    if (this->next_p != NULL)
    {
      if ( this->next_p->next_p != NULL)
      {
        this->next_p = this->next_p->next_p;
      }
    }
    
    if (first_p == this)
    {
      first_p = this->next_p;
    }
  }
};


#endif
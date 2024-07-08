#ifndef BTNRELAY_H
#define BTNRELAY_H

#include <Arduino.h>
#include "mDef.h"
#include "ctrlModule\SwitchButton.h"
#include "relayModule/Relay.h"

class BtnRelay : public SwitchButton, public Relay {
public:
   BtnRelay(){}

   BtnRelay()
   {
    SwitchButton::init()
    Relay::init()
   }

   ~BtnRelay(){}

};


#endif // BTNRELAY_H
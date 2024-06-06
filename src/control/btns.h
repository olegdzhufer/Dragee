#ifndef BTNS_DEF_H
#define BTNS_DEF_H

#include <EncButton.h>
#include "mDef.h"

Button btn1(BTN1_PIN, INPUT_PULLUP, LOW);
Button btn2(BTN2_PIN, INPUT_PULLUP, LOW);
Button btnSwitch(BTN3_PIN, INPUT_PULLUP, LOW);


void callbackBtn1() {
    switch (btn1.action()) {
      
        case EB_CLICK:
            Serial.println("click");
            break;
        default:
            //Serial.println();
    }
}

void callbackBtn2() {
    switch (btn2.action()) {
      
        case EB_CLICK:
            Serial.println("click");
            break;
        default:
            //Serial.println();
    }
}

void callbackSwitch() {
    switch (btnSwitch.action()) {
      
        case EB_HOLD:
            Serial.println("HOLD");
            break;

        case EB_RELEASE:
            Serial.println("RELEASE");
            break;
        default:
            //Serial.println();
    }
}



void btnsSetup() {
    btn1.attach(callbackBtn1);
    btn2.attach(callbackBtn2);
    btnSwitch.attach(callbackBtnSwitch);

    // pinMode(btnGPIO, INPUT_PULLUP);
  // attachInterrupt(digitalPinToInterrupt(btnGPIO), btnIsrHigh, CHANGE);
//   attachInterrupt(digitalPinToInterrupt(btnGPIO), btnIsrHigh, RISING);
//   attachInterrupt(digitalPinToInterrupt(btnGPIO), btnIsrLow, FALLING);

}

void btnsLoop();
{
     btn1.tick();

}
// void btnsSetCallback(void (*callback)(int));
// void btnsSetCallback(void (*callback)());


#endif
#ifndef BTNS_DEF_H
#define BTNS_DEF_H

#include <EncButton.h>
#include <Arduino.h>
#include<freertos/FreeRTOS.h>
#include "mDef.h"

Button btn1(BTN1, INPUT_PULLUP, LOW);
Button btn2(BTN2, INPUT_PULLUP, LOW);
Button btnSwitch(BTN3, INPUT_PULLUP, LOW);


void callbackBtn1() {
    switch (btn1.action()) {
      
        case EB_CLICK:
            
            break;
        default:
            //Serial.println();
    }
}

void callbackBtn2() {
    switch (btn2.action()) {
      
        case EB_CLICK:
            
            break;
        default:
            //Serial.println();
    }
}

void callbackSwitch() {
    switch (btnSwitch.action()) {
      
        case EB_HOLD:
            
            break;

        case EB_RELEASE:
            
            break;
        default:
            //Serial.println();
    }
}



void btnsSetup() {
    btn1.attach(callbackBtn1);
    btn2.attach(callbackBtn2);
    btnSwitch.attach(callbackSwitch);

}

void btnsLoop();
{
     btn1.tick();

}
// void btnsSetCallback(void (*callback)(int));
// void btnsSetCallback(void (*callback)());




#endif
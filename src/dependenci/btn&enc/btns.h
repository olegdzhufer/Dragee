#ifndef BTNS_H
#define BTNS_H

#include "../relay/relay.h"



void buttons_setup(void){
  REG_FLAG &= ~BTN_INT;

  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(BTN3, INPUT_PULLUP);

}

int getBtn(){
    REG_FLAG &= ~BTN_INT;

    return buttonState;
}


void loop_btn(){
  if(debounceDelay + 100  < millis()){

    debounceDelay = millis();

    if(!digitalRead(BTN3))REG_FLAG ^= FAN_STATUS;
    // else REG_FLAG &= ~ FAN_STATUS;

    if(!digitalRead(BTN2)){
      REG_FLAG |=  BTN_INT;
      buttonState = 0x01;
    }else if(!digitalRead(BTN1)){
      REG_FLAG |=  BTN_INT;
      buttonState = 0x02;
    }
  }
}

#endif
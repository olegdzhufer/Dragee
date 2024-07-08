#ifndef INIT_BTNS_H
#define INIT_BTNS_H

#include "SwitchButton.h"

BtnList btn1(BTN1_PIN, SWITCH_TYPE, &relayFan);//, &relayFan.toggle);
BtnList btn2(BTN2_PIN, BTN_TYPE, &relayHeat);//, &relayHeat.toggle
BtnList btn3(BTN3_PIN, BTN_TYPE, &relayCool);//, &relayCool.toggle


void buttons.Setup()
{
  btn1.init(BTN1_PIN, SWITCH_TYPE);
  btn2.init(BTN2_PIN, BTN_TYPE);
  btn3.init(BTN3_PIN, BTN_TYPE);

  btn1.setNext(&btn2);
  btn2.setNext(&btn3);
}

//! USE IN MAIN LOOP!!!! 
//!  BtnList::tickAll();

#endif
#ifndef ENC_H
#define ENC_H

#include <EncButton.h>

#include "settings.h"
#include "pins.h"
#include "menu.h"


#ifdef DEBUG
#define D_SerialBegin(...) Serial.begin(__VA_ARGS__);
#define D_print(...)       Serial.print(__VA_ARGS__)
#define D_write(...)       Serial.write(__VA_ARGS__)
#define D_println(...)     D_println(__VA_ARGS__)
#else
#define D_SerialBegin(bauds)
#define D_print(...)
#define D_write(...)
#define D_println(...)
#endif

#ifdef ENC_S

EncButton en(CLK, DT, SW);

IRAM_ATTR void isrEnc() {
  en.tickISR();
}

bool updateTemp = false;
uint8_t enc_pre;

void encoder_setup(){

  attachInterrupt(digitalPinToInterrupt(ENC_R_PIN), isrEnc, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_L_PIN), isrEnc, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_BTN_PIN), isrEnc, FALLING);
  en.setEncISR(true);
  
  en.setEncType(EB_STEP4_LOW);
  en.setBtnLevel(HIGH);
}

int getResult(){
  return enc_pre; 
}

bool flagEnc = false;


void MinusTemp(){
  if(menu.curr == Heat && TargetTemp > MIN_TEMP_HEAT){
    updateTemp = true;
    TargetTemp -= 0.5;
    TempSetH->val->setfloat(TempSetH->val, TargetTemp);
    menu.lineUpdate(&menu, TempSetH);
  }else if(menu.curr == Cooling && FrostTemp > MIN_TEMP_COOL){
    updateTemp = true;
    FrostTemp -= 0.5;
    TempSetC->val->setfloat(TempSetC->val, FrostTemp);
    menu.lineUpdate(&menu, TempSetC);
  }
}

void PlusTemp(){
  if(menu.curr == Heat && TargetTemp < MAX_TEMP_HEAT){
    updateTemp = true;
    TargetTemp += 0.5;
    Serial.println(TargetTemp);
    TempSetH->val->setfloat(TempSetH->val, TargetTemp);
    menu.lineUpdate(&menu, TempSetH);
  }else if(menu.curr == Cooling && FrostTemp < MAX_TEMP_COOL){
    updateTemp = true;
    FrostTemp += 0.5;
    TempSetC->val->setfloat(TempSetC->val, FrostTemp);
    menu.lineUpdate(&menu, TempSetC);
  }
}

void read_encoder(){
    en.tick();

    if(en.leftH()){
      MinusTemp();
    }
    else if(en.rightH()){
      PlusTemp();
    }
    else if (en.left()) {
      MinusTemp();
    }
    else if(en.right()){
      PlusTemp();
    }
     else if (en.press()){
      Serial.println("press");
    }
}

#endif



#endif

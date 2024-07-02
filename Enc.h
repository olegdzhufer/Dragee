#ifndef ENC_H
#define ENC_H

#include <Arduino.h>
#include <EncButton.h>

#include "settings.h"
#include "pins.h"
#include "menu.h"


#ifdef ENC_S
  EncButton en(CLK, DT, SW);
  
bool updateTemp = false;



uint8_t enc_pre;
void encoder_setup(){
  en.setEncType(EB_STEP4_LOW);
  en.setBtnLevel(HIGH);
}

int getResult(){
  return enc_pre; 
}

bool flagEnc = false;


void read_encoder(){

  int currtime;
  if(!currtime)currtime = 0;
  if( millis() > currtime + 10){
    currtime += millis();
    
    en.tick();

    if(en.leftH()){
      if(menu.curr == Heat && TargetTemp > 30){
        updateTemp = true;
        TargetTemp -= 0.5;
      }else if(menu.curr == Cooling && FrostTemp > 0){
        updateTemp = true;
        FrostTemp -= 0.5;
        TempSetC->val->setfloat(TempSetC->val, FrostTemp);
        menu.lineUpdate(&menu, TempSetC);
      }
    }
    else if(en.rightH()){
      if(menu.curr == Heat && TargetTemp < 60){
        updateTemp = true;
        TargetTemp += 0.5;
        Serial.println(TargetTemp);
      }else if(menu.curr == Cooling && FrostTemp < 30){
        updateTemp = true;
        FrostTemp += 0.5;
        TempSetC->val->setfloat(TempSetC->val, FrostTemp);
        menu.lineUpdate(&menu, TempSetC);
      }
    }

    else if (en.left()) {
        enc_pre = 0x03;
        Serial.println("3");
    }
    else if(en.right()){
        enc_pre = 0x04;
        Serial.println("4");
    }
     else if (en.press())  
    {
        enc_pre = 0x05;
        Serial.println("5");
    }
  }


  if(updateTemp){
    updateTemp = false;
    TempSetH->val->setfloat(TempSetH->val, TargetTemp);
    menu.lineUpdate(&menu, TempSetH);
  }
}

#endif



#endif

#ifndef ENC_H
#define ENC_H

#include <EncButton.h>

#include "settings.h"
#include "pins.h"
#include "menu.h"
#include "relay.h"


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
uint8_t clickVal = 0;
uint32_t buferClick = 0;
bool settingStatus = false;


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
  }else
}


void switchLeftSetting();
void switchRighSetting();

void nextLineSetting();
void prevLineSetting();

void settingTick();

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
      // if(clickVal >= 5){
      //   settingStatus = !settingStatus;
      // }

      // if(millis() - buferClick <= 1000){
      //   buferClick = millis();
      //   clickVal += 1;
      // }else clickVal = 0;

      // settingTick();
    }
}

void settingTick(){
  if(settingStatus){
    menu.curr = Setting;
  }
}

void updView(double value){
  if(menu.curr == Setting){
    menu.curr->current->val->setfloat(menu.curr->current->val, (float)value);
    menu.lineUpdate(&menu, menu.curr->current);
  }
}

void switchNextSetting(){
  if(menu.curr == Setting){
    menu.nextLine(&menu);
    FLAG_LCD = true;
  }
}

void switchPrevSetting(){
  if(menu.curr == Setting){
    menu.prevLine(&menu);
    FLAG_LCD = true;
  }
}
void switchLeftSetting(){
  if(menu.curr == Setting){
    switch (menu.curr->current)
    {
    case KpLine:
      Kp -= 0.1;
      relayHeat.pidElement->SetTunings(Kp, Ki, Kd);
      relayCool.pidElement->SetTunings(Kp, Ki, Kd);
      updView(Kp);
      break;

    case KiLine:
      Ki -= 0.1;
      relayHeat.pidElement->SetTunings(Kp, Ki, Kd);
      relayCool.pidElement->SetTunings(Kp, Ki, Kd);
      updView(Ki);
      break;

    case KdLine:
      Kd -= 0.1;
      relayHeat.pidElement->SetTunings(Kp, Ki, Kd);
      relayCool.pidElement->SetTunings(Kp, Ki, Kd);
      updView(Kd);
      break;
    
    default:
      break;
    }
  }
}
void prevLineSetting(){
  {
  if(menu.curr == Setting){
    Line* sel = menu.curr->current;
    if(sel == KpLine){
      Kp += 0.1;
      relayHeat.pidElement->SetTunings(Kp, Ki, Kd);
      relayCool.pidElement->SetTunings(Kp, Ki, Kd);
      updView(Kp);
    }else if(sel == KpLine){
      Kp += 0.1;
      relayHeat.pidElement->SetTunings(Kp, Ki, Kd);
      relayCool.pidElement->SetTunings(Kp, Ki, Kd);
      updView(Kp);
    
    
    default:
      break;
    }
  }
}
}

#endif



#endif

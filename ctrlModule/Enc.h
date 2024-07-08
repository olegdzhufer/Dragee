#ifndef ENC_H
#define ENC_H

#include <EncButton.h>
#include "../mDef.h"


void enc_cb() {
    Serial.print("callback: ");
    switch (eb.action()) {
        case EB_PRESS:
            Serial.println("press");
            break;
        case EB_HOLD:
            Serial.println("hold");
            break;
        case EB_STEP:
            Serial.println("step");
            break;
        case EB_RELEASE:
            Serial.print("release. steps: ");
            Serial.print(eb.getSteps());
            Serial.print(", press for: ");
            Serial.print(eb.pressFor());
            Serial.print(", hold for: ");
            Serial.print(eb.holdFor());
            Serial.print(", step for: ");
            Serial.println(eb.stepFor());
            break;
        case EB_CLICK:
            Serial.println("click");
            break;
        case EB_CLICKS:
            Serial.print("clicks ");
            Serial.println(eb.getClicks());
            break;
        case EB_TURN:
            Serial.print("turn ");
            Serial.print(eb.dir());
            // tempToHold+=eb.dir();

            Serial.print(" ");
            Serial.print(eb.fast());
            Serial.print(" ");
            Serial.println(eb.pressing());
            break;
        case EB_REL_HOLD:
            Serial.println("release hold");
            break;
        case EB_REL_HOLD_C:
            Serial.print("release hold clicks ");
            Serial.println(eb.getClicks());
            break;
        case EB_REL_STEP:
            Serial.println("release step");
            break;
        case EB_REL_STEP_C:
            Serial.print("release step clicks ");
            Serial.println(eb.getClicks());
            break;
        default:
            Serial.println();
    }
}


// #ifdef ENC_S
  // EncButton en(CLK, DT, SW);
  
// bool updateTemp = false;


// uint8_t enc_pre;
// void encoder_setup(){
  // en.setEncType(EB_STEP4_LOW);
  // en.setBtnLevel(HIGH);
// }

// int getResult(){
  // return enc_pre; 
// }

// bool flagEnc = false;

// void read_encoder(){

//     en.tick();

//     if(en.leftH()){
//       if(menu.curr == Heat && TargetTemp > MIN_TEMP_HEAT){
//         updateTemp = true;
//         TargetTemp -= 0.5;
//         TempSetH->val->setfloat(TempSetH->val, TargetTemp);
//         menu.lineUpdate(&menu, TempSetH);
//       }else if(menu.curr == Cooling && FrostTemp > MIN_TEMP_COOL){
//         updateTemp = true;
//         FrostTemp -= 0.5;
//         TempSetC->val->setfloat(TempSetC->val, FrostTemp);
//         menu.lineUpdate(&menu, TempSetC);
//       }
//     }
//     else if(en.rightH()){
//       if(menu.curr == Heat && TargetTemp < MAX_TEMP_HEAT){
//         updateTemp = true;
//         TargetTemp += 0.5;
//         Serial.println(TargetTemp);
//         TempSetH->val->setfloat(TempSetH->val, TargetTemp);
//         menu.lineUpdate(&menu, TempSetH);
//       }else if(menu.curr == Cooling && FrostTemp < MAX_TEMP_COOL){
//         updateTemp = true;
//         FrostTemp += 0.5;
//         TempSetC->val->setfloat(TempSetC->val, FrostTemp);
//         menu.lineUpdate(&menu, TempSetC);
//       }
//     }

//     else if (en.left()) {
//         enc_pre = 0x03;
//         Serial.println("3");
//     }
//     else if(en.right()){
//         enc_pre = 0x04;
//         Serial.println("4");
//     }
//      else if (en.press())  
//     {

//     }
  
// }

// #endif



#endif

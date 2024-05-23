#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>
#include <EncButton.h>
#include <PIDController.h>

EncButton en(CLK, DT, SW);

int set_temperature = 1;
int clockPinState;
float debounce = 0;
int encoder_btn_count = 0;
float temperature_value_c = 0.0;

void enc_cb(){
  switch (en.action())
  {
  case EB_CLICK:
    break;
  
  default:
    break;
  }
}

void encoder_setup(){
  en.setEncType(EB_STEP4_LOW);
  en.setBtnLevel(HIGH);
}

int read_encoder(){
    if(en.leftH()){
      Serial.print("1");
      return 0x01;
    }
    if(en.rightH()){
      Serial.print("2");
      return 0x02;
    }
    if (en.left()) {
      Serial.print("3");
        return 0x03; 
    }
    if(en.right()){
      Serial.print("4");
        return 0x04;
    }
    if(en.press())  
    {
      Serial.print("5");
        return 0x05;
    }

    return 0x00;
}

void change_temperature(){
  int action = read_encoder(); 
  switch(action) {
    case 0x01:
    case 0x03:
      desiredTemp--;
      break;
    case 0x02:
    case 0x04:
      desiredTemp++;
      break;
    default:
      break;
  }
}

#endif
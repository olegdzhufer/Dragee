#include <Arduino.h>
#include <Menulib.h>
#include "menu.h"
#include "encoder.h"

#include "menu.h"

void encWork_loop(){
    int enc = 0x00;
    enc = read_encoder();

    if(enc){
        switch (enc){
        case 0x01:
            delay(100);
            Serial.print("LeftH");
        break;

        case 0x02:
            delay(100);
            Serial.print("RightH");
        break;

        case 0x03:
            delay(100);
            Serial.print("Left");
        break;

        case 0x04:
            delay(100);
            Serial.print("Right");
        break;

        case 0x05:
            delay(100);
            Serial.print("Click");
        break;
        
        default:
        break;
        }
  }
}
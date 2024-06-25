#include "core/Encoder.h"
#ifndef ENC_H
#define ENC_H

#include <Arduino.h>
#include <EncButton.h>

#include "settings.h"
#include "pins.h"
#include "menu.h"

class MyEncoder {
private:
  EncButton en;

public:
  bool updateTemp = false;
  uint8_t enc_pre;
  bool flagEnc = false;

  MyEncoder()
    : en(CLK, DT, SW) {}

  void read_encoder() {
    static unsigned long currtime = 0;

    if (millis() > currtime + 10) {
      currtime += 10;

      en.tick();

      if (en.leftH()) {
        if (menu.curr == Heat && TargetTemp > 0) {
          updateTemp = true;
          TargetTemp -= 1;
          Serial.println(TargetTemp);
        }
      } else if (en.rightH()) {
        if (menu.curr == Heat && TargetTemp < 60) {
          updateTemp = true;
          TargetTemp += 1;
          Serial.println(TargetTemp);
        }
      } else if (en.left()) {
        enc_pre = 0x03;
        Serial.println("3");
      } else if (en.right()) {
        enc_pre = 0x04;
        Serial.println("4");
      } else if (en.press()) {
        enc_pre = 0x05;
        Serial.println("5");
      }
    }

    if (updateTemp) {
      updateTemp = false;
      TempSetH->val->setfloat(TempSetH->val, TargetTemp);
      FLAG_LCD = true;
    }
  }

  int getResult() {
    return enc_pre;
  }

  void setup() {
    en.setEncType(EB_STEP4_LOW);
    en.setBtnLevel(HIGH);
  }
};

MyEncoder encoder;

void encoder_setup() {
  encoder.setup();
}

void encoder_loop() {
  encoder.read_encoder();
}

#endif

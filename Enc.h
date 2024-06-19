#ifndef ENC_H
#define ENC_H

#include <Arduino.h>
#include <EncButton.h>

#include "settings.h"
#include "pins.h"

class EncoderWork {
public:
    EncoderWork() : enc(nullptr), temp(nullptr), callBackFuncClick(nullptr), callBackFuncRight(nullptr), callBackFuncLeft(nullptr) {}

    void setCallBackClick(void (*callBack)()) {
        this->callBackFuncClick = callBack;
    }
    void setCallBackRight(void (*callBack)()) {
        this->callBackFuncRight = callBack;
    }
    void setCallBackLeft(void (*callBack)()) {
        this->callBackFuncLeft = callBack;
    }

    bool autoEnc(uint8_t clk, uint8_t dt, uint8_t sw) {
        enc = new EncButton(clk, dt, sw);
        return (enc != nullptr);
    }

    void setEnc(EncButton* enc){
      if(enc){
        this->enc = enc;
      }
    }

    void changeTemp(float* temp) {
        this->temp = temp;
    }

    void tick() {
        if (enc) {
          enc->tick();
          uint8_t Ho = enc->action();
          if(Ho){
            Serial.println(Ho);
          }
      }
    }

private:
    EncButton* enc;
    float* temp;
    void (*callBackFuncClick)();
    void (*callBackFuncRight)();
    void (*callBackFuncLeft)();
};

EncoderWork en;

EncButton ent (CLK, DT, SW);

void EncoderSetup() {
    en.setEnc(&ent);

}

void EncoderLoop(){
  en.tick();
}
#endif

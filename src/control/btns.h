#ifndef BTNS_DEF_H
#define BTNS_DEF_H

#include <Arduino.h>
#include <EncButton.h>
#include "mDef.h"


class ButtonSwitch : public VirtButton {
   public:

    void (*callbackOnPress)() = NULL;

    ButtonSwitch() {}

    ButtonSwitch(uint8_t btnPin, uint8_t ledPin, uint8_t btnMode = INPUT_PULLUP, uint8_t btnLevel = LOW, uint8_t ledInitState = LOW) {
        init(btnPin, ledPin, btnMode, btnLevel, ledInitState);
    }

    void init(uint8_t btnPin, uint8_t ledPin, uint8_t btnMode = INPUT_PULLUP, uint8_t btnLevel = LOW, uint8_t ledInitState = LOW) {
        self.btnPin = btnPin;
        EB_mode(btnPin, btnMode);
        setBtnLevel(btnLevel);

        setLed(ledPin, ledInitState);
    }

    bool read() {
        return EB_read(btnPin) ^ bf.read(EB_INV);
    }

    bool tick() {
        bool tick = VirtButton::tick(EB_read(btnPin));
        if (tick) {
            pressedBtn();
            
            return true;
        }
        return false;
    }

    bool tickRaw() {
        return VirtButton::tickRaw(EB_read(btnPin));
    }


    void setLed(uint8_t ledPin, uint8_t ledState = LOW) {
        self.ledPin = ledPin;
        self.ledState = ledState;
        pinMode(ledPin, OUTPUT);
        digitalWrite(ledPin, ledState);
    }

    

    void toggleLed() {
        ledState = !ledState;
        digitalWrite(ledPin, ledState);
    }


    void pressedBtn() {
        uint16_t btnState = VirtButton::action();
        switch (btnState) {
        
            case EB_CLICK:
                Serial.println("click");
                toggleLed();
                callCallback();
                break;
            default:
                Serial.println("other action");
        }
    }

    void attachCallback(void (*callback)()) {
        self.callbackOnPress = callback;
    }

    void callCallback() {
        if (callbackOnPress != NULL) {
            callbackOnPress();
        }
    }

   private:
    uint8_t btnPin;
    uint8_t ledPin;
    uint8_t ledState;

};


ButtonSwitch btn1(BTN1_PIN, LED_PIN1, INPUT_PULLUP, LOW);
ButtonSwitch btn2(BTN2_PIN, LED_PIN2, INPUT_PULLUP, LOW);
ButtonSwitch btnSwitch(BTN3_PIN, LED_PIN3, INPUT_PULLUP, LOW);


void callbackSwitch() {
    switch (btnSwitch.action()) {
      
        case EB_HOLD:
            Serial.println("HOLD");
            break;

        case EB_RELEASE:
            Serial.println("RELEASE");
            break;
        default:
            //Serial.println();
    }
}



void btnsSetup() {
    btnSwitch.attachCallback(callbackBtnSwitch);
}

void btnsLoop();
{
     btn1.tick();
     btn2.tick();
     btnSwitch.tick();

}


#endif
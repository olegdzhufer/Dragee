#pragma once
#include <Arduino.h>

#include "../../mDef.h"

#include "eb_core/VirtButton.h"
#include "eb_core/VirtEncoder.h"
#include "eb_core/VirtEncButton.h"
// #include "eb_core/Button.h"
// #include "eb_core/Encoder.h"
// #include "eb_core/EncButton.h"

// #define EB_DEB_TIME 50      // таймаут гашения дребезга кнопки (кнопка)
// #define EB_CLICK_TIME 500   // таймаут ожидания кликов (кнопка)
// #define EB_HOLD_TIME 600    // таймаут удержания (кнопка)
// #define EB_STEP_TIME 200    // таймаут импульсного удержания (кнопка)
// #define EB_FAST_TIME 30 
// Switch() = delete;


class MenuEncButton : public VirtEncButton {
   public:
    // configure pins (encoder, encoder, button, pinmode encoder, pinmode button)
    
    MenuEncButton(uint8_t encA = 0, uint8_t encB = 0, uint8_t btn = 0, uint8_t modeEnc = INPUT, uint8_t modeBtn = INPUT, uint8_t btnLevel = HIGH) {
        init(encA, encB, btn, modeEnc, modeBtn, btnLevel);
    }

    // configure pins (encoder, encoder, button, pinmode encoder, pinmode button)
    void init(uint8_t encA = 0, uint8_t encB = 0, uint8_t btn = 0, uint8_t modeEnc = INPUT, uint8_t modeBtn = INPUT, uint8_t btnLevel = HIGH) {
        setPins(encA, encB, btn);
        EB_mode(encA_pin, modeEnc);
        EB_mode(encB_pin, modeEnc);
        EB_mode(btn_pin, modeBtn);
        setBtnLevel(btnLevel);
        initEnc(readEnc());

        this->counter = 0;


    // eb.setBtnLevel(LOW);
    // eb.setClickTimeout(500);
    // eb.setDebTimeout(50);
    // eb.setHoldTimeout(600);
    // eb.setStepTimeout(200);
// default values btw
    // eb.setEncReverse(0);
    // eb.setEncType(EB_STEP4_LOW);
    // eb.setFastTimeout(30);

    }

    void setPins(uint8_t encA = 0, uint8_t encB = 0, uint8_t btn = 0){
        // if (encA < 0 || encB < 0 || btn < 0)
        // {
        //     DEBUG_PRINT("Invalid pin number");
        //     return;
        // }
        
        encA_pin = encA;
        encB_pin = encB;
        btn_pin = btn;
    }

    // ====================== TICK ======================

    // function for processing to be called in the encoder interrupt
    int8_t tickISR() {
        return VirtEncButton::tickISR(readEnc());
    }

    // function for processing, to be called in loop
    bool tick() {
        bool ticked;
        if (ef.read(EB_EISR))
        {
            ticked = VirtEncButton::tick(EB_read(btn_pin));
        } else {
            ticked = VirtEncButton::tick(readEnc(), EB_read(btn_pin));
        }
          
        if (ticked)
        {
            action();
        }
        return ticked;
    }

    // function for processing without resetting events
    bool tickRaw() {
        if (ef.read(EB_EISR)) return VirtEncButton::tickRaw(EB_read(btn_pin));
        else return VirtEncButton::tickRaw(readEnc(), EB_read(btn_pin));
    }

    // ====================== READ ======================
    // read the button value
    bool readBtn() {
        return EB_read(btn_pin) ^ bf.read(EB_INV);
    }

    // read the encoder value
    int8_t readEnc() {
        return EB_read(encA_pin) | (EB_read(encB_pin) << 1);
    }
    

    uint16_t action()
    {
        uint16_t actionType=VirtEncButton::action();
        switch (actionType)
        {
            case EB_TURN:
                DEBUG_PRINT("TURN");
                // var += 5 * enc.dir();
                // var += enc.fast() ? 10 : 1;
                // var += enc.pressing() ? 10 : 1;

                break;

            case EB_PRESS:
                DEBUG_PRINT("PRESS");
                break;

            case EB_HOLD:
                DEBUG_PRINT("HOLD");
                // if (btn.hold()) mode = btn.getClicks();

                break;

            case EB_STEP:
                DEBUG_PRINT("STEP");
                break;
            
            case EB_RELEASE:
                DEBUG_PRINT("RELEASE");
                break;

            case EB_CLICK:
                DEBUG_PRINT("CLICK");
                break;

            case EB_CLICKS:
                DEBUG_PRINT("CLICKS");
                // if (btn.hasClicks()) mode = btn.getClicks();

                break;

            case EB_REL_HOLD:
                DEBUG_PRINT("REL_HOLD");
                break;

            case EB_REL_HOLD_C:
                DEBUG_PRINT("REL_HOLD_C");
                break;
            
            case EB_REL_STEP:
                DEBUG_PRINT("REL_STEP");
                break;

            case EB_REL_STEP_C:
                DEBUG_PRINT("REL_STEP_C");
                break;

            default:
                break;
        }
        return actionType;
    }

    

    // ====================== ISR ======================

//std::function<void(void)>
    void attachISR(funcVoid_t isrEnc, funcVoid_t isrBtn){ 
        if (isrEnc == NULL || isrBtn == NULL)
        {
            return;
        }
        
        attachInterrupt(digitalPinToInterrupt(this->encA_pin), isrEnc, CHANGE);
        attachInterrupt(digitalPinToInterrupt(this->encB_pin), isrEnc, CHANGE);
        attachInterrupt(digitalPinToInterrupt(this->btn_pin),  isrBtn, FALLING);
        this->setEncISR(true);
    }

    // ===================== PRIVATE =====================
   private:
    uint8_t encA_pin, encB_pin, btn_pin;
    // Menu *ptr;
};






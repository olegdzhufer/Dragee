#pragma once
#include <Arduino.h>

#include "VirtEncButton.h"
#include "io.h"

// ===================== CLASS =====================

class EncButton : public VirtEncButton {
   public:
    // configure pins (encoder, encoder, button, pinmode encoder, pinmode button)
    EncButton(uint8_t encA = 0, uint8_t encB = 0, uint8_t btn = 0, uint8_t modeEnc = INPUT, uint8_t modeBtn = INPUT_PULLUP, uint8_t btnLevel = LOW) {
        init(encA, encB, btn, modeEnc, modeBtn, btnLevel);
    }

    // configure pins (encoder, encoder, button, pinmode encoder, pinmode button)
    void init(uint8_t encA = 0, uint8_t encB = 0, uint8_t btn = 0, uint8_t modeEnc = INPUT, uint8_t modeBtn = INPUT_PULLUP, uint8_t btnLevel = LOW) {
        e0 = encA;
        e1 = encB;
        b = btn;
        EB_mode(e0, modeEnc);
        EB_mode(e1, modeEnc);
        EB_mode(b, modeBtn);
        setBtnLevel(btnLevel);
        initEnc(readEnc());
    }

    // ====================== TICK ======================
    // function for processing to be called in the encoder interrupt
    int8_t tickISR() {
        return VirtEncButton::tickISR(readEnc());
    }

    // function for processing, to be called in loop
    bool tick() {
        if (ef.read(EB_EISR)) return VirtEncButton::tick(EB_read(b));
        else return VirtEncButton::tick(readEnc(), EB_read(b));
    }

    // function for processing without resetting events
    bool tickRaw() {
        if (ef.read(EB_EISR)) return VirtEncButton::tickRaw(EB_read(b));
        else return VirtEncButton::tickRaw(readEnc(), EB_read(b));
    }

    // ====================== READ ======================
    // read the button value
    bool readBtn() {
        return EB_read(b) ^ bf.read(EB_INV);
    }

    // read the encoder value
    int8_t readEnc() {
        return EB_read(e0) | (EB_read(e1) << 1);
    }

    // ===================== PRIVATE =====================
   private:
    uint8_t e0, e1, b;
};

// ===================== T CLASS =====================
template <uint8_t ENCA, uint8_t ENCB, uint8_t BTN>
class EncButtonT : public VirtEncButton {
   public:
    // configure pins (enc, enc, button, pinmode enc, pinmode button)
    EncButtonT(uint8_t modeEnc = INPUT, uint8_t modeBtn = INPUT_PULLUP, uint8_t btnLevel = LOW) {
        init(modeEnc, modeBtn, btnLevel);
    }

    // configure pins (pinmode enc, pinmode button)
    void init(uint8_t modeEnc = INPUT, uint8_t modeBtn = INPUT_PULLUP, uint8_t btnLevel = LOW) {
        EB_mode(ENCA, modeEnc);
        EB_mode(ENCB, modeEnc);
        EB_mode(BTN, modeBtn);
        setBtnLevel(btnLevel);
        initEnc(readEnc());
    }

    // ====================== TICK ======================
    // function for processing to be called in the encoder interrupt
    int8_t tickISR() {
        return VirtEncButton::tickISR(readEnc());
    }

    // processing function, to be called in loop
    bool tick() {
        if (ef.read(EB_EISR)) return VirtEncButton::tick(EB_read(BTN));
        else return VirtEncButton::tick(readEnc(), EB_read(BTN));
    }

    // processing function without resetting events
    bool tickRaw() {
        if (ef.read(EB_EISR)) return VirtEncButton::tickRaw(EB_read(BTN));
        else return VirtEncButton::tickRaw(readEnc(), EB_read(BTN));
    }

    // ====================== READ ======================
    // read the button value
    bool readBtn() {
        return EB_read(BTN) ^ bf.read(EB_INV);
    }

    // read the encoder value
    int8_t readEnc() {
        return EB_read(ENCA) | (EB_read(ENCB) << 1);
    }

    // ===================== PRIVATE =====================
   private:
};
#pragma once
#include <Arduino.h>

#include "VirtButton.h"
#include "utils.h"

// ============= VAR PIN =============
class Button : public VirtButton {
   public:
    Button(uint8_t npin = 0, uint8_t mode = INPUT_PULLUP, uint8_t btnLevel = LOW) {
        init(npin, mode, btnLevel);
    }

    // указать пин и его режим работы
    void init(uint8_t npin = 0, uint8_t mode = INPUT_PULLUP, uint8_t btnLevel = LOW) {
        setPin(npin);
        setBtnMode(mode);
        setBtnLevel(btnLevel);
    }

    void setPin(uint8_t npin = 0){
        pin = npin;
    }

    void setBtnMode(uint8_t mode){
        pinMode(pin, mode);
        VirtButton::setBtnMode(mode);
    }

    // прочитать текущее значение кнопки (без дебаунса)
    bool read() {
        return EBread(pin) ^ read_bf(EB_INV);
    }

    // функция обработки, вызывать в loop
    bool tick() {
        checkCallback();
        return VirtButton::tick(EBread(pin));
    }

    // обработка кнопки без сброса событий и вызова коллбэка
    bool tickRaw() {
        return VirtButton::tickRaw(EBread(pin));
    }

    // ===================================== CALLBACK =====================================
    void attach_call(eb_callback type, void (*handler)()) {
        _callback[type] = *handler;
    }

    void exec(uint8_t num) {
        if (*_callback[num]) _callback[num]();
    }

    void checkCallback() 
    {
        #ifndef EB_NO_CALLBACK
        if (press()) exec(PRESS_HANDLER);
        if (hold()) exec(HOLD_HANDLER);
        if (click()) exec(CLICK_HANDLER);
        if (release()) exec(RELEASE_HANDLER);
        #endif
    }


   private:
    uint8_t pin;
#ifndef EB_NO_CALLBACK
    void (*_callback[14])() = {};
#endif
};

// ============= TEMPLATE PIN =============
template <uint8_t PIN>
class ButtonT : public VirtButton {
   public:
    ButtonT(uint8_t mode = INPUT_PULLUP, uint8_t btnLevel = LOW) {
        init(mode, btnLevel);
    }

    // указать режим работы пина
    void init(uint8_t mode = INPUT_PULLUP, uint8_t btnLevel = LOW) {
        pinMode(PIN, mode);
        setBtnLevel(btnLevel);
    }

    // прочитать текущее значение кнопки (без дебаунса)
    bool read() {
        return EBread(PIN) ^ read_bf(EB_INV);
    }

    // функция обработки, вызывать в loop
    bool tick() {
        return VirtButton::tick(EBread(PIN));
    }

    // обработка кнопки без сброса событий и вызова коллбэка
    bool tickRaw() {
        return VirtButton::tickRaw(EBread(PIN));
    }

   private:
};
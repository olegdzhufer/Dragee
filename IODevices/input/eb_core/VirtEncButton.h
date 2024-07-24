#pragma once
#include <Arduino.h>

#include "VirtButton.h"
#include "VirtEncoder.h"
#include "io.h"

#ifdef EB_FAST_TIME
#define EB_FAST_T (EB_FAST_TIME)
#endif

// Base class of encoder with button
class VirtEncButton : public VirtButton, public VirtEncoder {
   public:

    // ====================== SET ======================

    // set the fast turn timeout, ms
    void setFastTimeout(const uint8_t tout) {
#ifndef EB_FAST_TIME
        EB_FAST_T = tout;
#endif
    }

    // reset encoder and button flags
    void clear() {
        VirtButton::clear();
        VirtEncoder::clear();
    }

    // ====================== GET ======================

    // pressed turn of the encoder [event]
    bool turnH() {
        return turn() && bf.read(EB_EHLD);
    }

    // fast turn of the encoder [state]
    bool fast() {
        return ef.read(EB_FAST);
    }

    // turn to the right [event]
    bool right() {
        return ef.read(EB_DIR) && turn() && !bf.read(EB_EHLD);
    }

    // turn to the left [event]
    bool left() {
        return !ef.read(EB_DIR) && turn() && !bf.read(EB_EHLD);
    }

    // pressed turn to the right [event]
    bool rightH() {
        return ef.read(EB_DIR) && turnH();
    }

    // pressed turn to the left [event]
    bool leftH() {
        return !ef.read(EB_DIR) && turnH();
    }

    // encoder button pressed. Analog of pressing() [state]
    bool encHolding() {
        return bf.read(EB_EHLD);
    }

    // action from button or encoder occurred, will return event code [event]
    uint16_t action() {
        if (turn()) return EB_TURN;
        else return VirtButton::action();
    }

    // ====================== POLL ======================
    // ISR
    // processing in interrupt (encoder only). Will return 0 at rest, 1 or -1 on turn
    int8_t tickISR(const bool e0, const bool e1) {
        return tickISR(e0 | (e1 << 1));
    }

    // processing in interrupt (encoder only). Will return 0 at rest, 1 or -1 on turn
    int8_t tickISR(int8_t state) {
        state = VirtEncoder::pollEnc(state);
        if (state) {
#ifdef EB_NO_BUFFER
            ef.set(EB_ISR_F);
            ef.write(EB_DIR, state > 0);
            ef.write(EB_FAST, checkFast());
#else
            for (uint8_t i = 0; i < 15; i += 3) {
                if (!(ebuffer & (1 << i))) {
                    ebuffer |= (1 << i);                         // turn
                    if (state > 0) ebuffer |= (1 << (i + 1));    // dir
                    if (checkFast()) ebuffer |= (1 << (i + 2));  // fast
                    break;
                }
            }
#endif
        }
        return state;
    }

    // TICK
    // processing of encoder and button
    bool tick(const bool e0, const bool e1, const bool btn) {
        return tick(e0 | (e1 << 1), btn);
    }

    // processing of encoder and button. state = -1 to skip encoder processing
    bool tick(const int8_t state, const bool btn) {
        clear();
        bool f = tickRaw(state, btn);

#ifndef EB_NO_CALLBACK
        if (cb && f) cb();
#endif
        return f;
    }

    // processing of encoder (in interrupt) and button
    bool tick(const bool btn) {
        return tick(-1, btn);
    }

    // RAW
    // processing without resetting events and calling callback
    bool tickRaw(const bool e0, const bool e1, const bool btn) {
        return tickRaw(e0 | (e1 << 1), btn);
    }

    // processing without resetting events and calling callback
    bool tickRaw(int8_t state, bool btn) {
        btn = VirtButton::tickRaw(btn);

        bool encf = 0;
#ifdef EB_NO_BUFFER
        if (ef.read(EB_ISR_F)) {
            ef.clear(EB_ISR_F);
            encf = 1;
        }
#else
        if (ebuffer) {
            ef.write(EB_DIR, ebuffer & 0b10);
            ef.write(EB_FAST, ebuffer & 0b100);
            ebuffer >>= 3;
            encf = 1;
        }
#endif
        else if ((state >= 0) && (state = VirtEncoder::pollEnc(state))) {
            ef.write(EB_DIR, state > 0);
            ef.write(EB_FAST, checkFast());
            encf = 1;
        }
        if (encf) {
            if (bf.read(EB_PRS)) bf.set(EB_EHLD);    // press the encoder
            else clicks = 0;
            if (!bf.read(EB_TOUT)) bf.set(EB_TOUT);  // timeout flag
            ef.set(EB_ETRN_R);                       // rotation flag
        }
        return encf | btn;
    }

    // processing without resetting events and calling callback (button)
    bool tickRaw(const bool btn) {
        return tickRaw(-1, btn);
    }

    // ===================== PRIVATE =====================
   protected:
#ifndef EB_FAST_TIME
    uint8_t EB_FAST_T = 30;
#endif

#ifndef EB_NO_BUFFER
    uint16_t ebuffer = 0;
#endif

   private:
    bool checkFast() {
        uint16_t ms = EB_uptime();
        bool f = 0;
        if (ms - tmr < EB_FAST_T) f = 1;
        tmr = ms;
        return f;
    }
};
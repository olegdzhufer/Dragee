#pragma once
#include <Arduino.h>

#include "io.h"
#include "flags.h"



// ===================== CONST ======================
#define EB_STEP4_LOW 0
#define EB_STEP4_HIGH 1
#define EB_STEP2 2
#define EB_STEP1 3

// ===================== FLAGS ======================
#define EB_TYPE (1 << 0)
#define EB_REV (1 << 2)
#define EB_FAST (1 << 3)
#define EB_DIR (1 << 4)
#define EB_ETRN_R (1 << 5)
#define EB_ISR_F (1 << 6)
#define EB_EISR (1 << 7)

// ===================== GLOBAL_FLAGS ======================
#define EB_TURN (1 << 6)         // encoder turn


class VirtEncoder {
   public:
    VirtEncoder() {
        prev = ecount = 0;
    }
    // ====================== SET ======================
    // invert encoder direction
    void setEncReverse(const bool rev) {
        if (rev) ef.set(EB_REV);
        else ef.clear(EB_REV);
    }

    // set encoder type (EB_STEP4_LOW, EB_STEP4_HIGH, EB_STEP2, EB_STEP1)
    void setEncType(const uint8_t type) {
        ef.flags = (ef.flags & 0b11111100) | type;
    }

    // use encoder processing in interrupt
    void setEncISR(const bool use) {
        ef.write(EB_EISR, use);
    }

    // encoder initialization
    void initEnc(const bool e0, const bool e1) {
        initEnc(e0 | (e1 << 1));
    }

    // encoder initialization with combined value
    void initEnc(const int8_t v) {
        prev = v;
    }

    // reset event flags
    void clear() {
        if (ef.read(EB_ETRN_R)) ef.clear(EB_ETRN_R);
    }

    // ====================== POLL ======================
    // was there a turn [event]
    bool turn() {
        return ef.read(EB_ETRN_R);
    }

    // encoder direction (1 or -1) [state]
    int8_t dir() {
        return ef.read(EB_DIR) ? 1 : -1;
    }

    // ====================== POLL ======================
    // ISR
    // Poll the encoder in the interrupt. Returns 1 or -1 on rotation, 0 on stop
    int8_t tickISR(const bool e0, const bool e1) {
        return tickISR(e0 | (e1 << 1));
    }

    // Poll the encoder in the interrupt. Returns 1 or -1 on rotation, 0 on stop
    int8_t tickISR(int8_t state) {
        state = pollEnc(state);
        if (state) {
            ef.set(EB_ISR_F);
            ef.write(EB_DIR, state > 0);
        }
        return state;
    }

    // TICK
    // Poll the encoder. Returns 1 or -1 on rotation, 0 on stop
    int8_t tick(const bool e0, const bool e1) {
        return tick(e0 | (e1 << 1));
    }

    // Poll the encoder. Returns 1 or -1 on rotation, 0 on stop
    int8_t tick(int8_t state) {
        state = tickRaw(state);
        if (state) return state;
        clear();
        return 0;
    }

    // Poll the encoder (the actual polling is in the interrupt)
    int8_t tick() {
        return tick(-1);
    }

    // RAW
    // Poll the encoder without resetting the rotation event
    int8_t tickRaw(const bool e0, const bool e1) {
        return tickRaw(e0 | (e1 << 1));
    }

    // Poll the encoder without resetting the rotation event
    int8_t tickRaw(int8_t state) {
        if (ef.read(EB_ISR_F)) {
            ef.clear(EB_ISR_F);
            ef.set(EB_ETRN_R);
            return dir();
        }
        if ((state >= 0) && (state = pollEnc(state))) {
            ef.write(EB_DIR, state > 0);
            ef.set(EB_ETRN_R);
            return state;
        }
        return 0;
    }

    // Poll the encoder without resetting the rotation event (the actual polling is in the interrupt)
    int8_t tickRaw() {
        return tickRaw(-1);
    }

    // POLL
    // Poll the encoder without setting the rotation event (faster). Returns 1 or -1 on rotation, 0 on stop
    int8_t pollEnc(const bool e0, const bool e1) {
        return pollEnc(e0 | (e1 << 1));
    }

    // Poll the encoder without setting the rotation event (faster). Returns 1 or -1 on rotation, 0 on stop
    int8_t pollEnc(int8_t state) {
        if (prev != state) {
            ecount += ((0x49941661 >> ((state | (prev << 2)) << 1)) & 0b11) - 1;
            prev = state;
            if (!ecount) return 0;
            switch (ef.mask(0b11)) {
                case EB_STEP4_LOW:
                    if (state != 0b11) return 0;  // skip 00, 01, 10
                    break;
                case EB_STEP4_HIGH:
                    if (state) return 0;  // skip 01, 10, 11
                    break;
                case EB_STEP2:
                    if (state == 0b10 || state == 0b01) return 0;  // skip 10 01
                    break;
            }
            state = ((ecount > 0) ^ ef.read(EB_REV)) ? 1 : -1;
            ecount = 0;
#ifndef EB_NO_COUNTER
            counter += state;
#endif
            return state;
        }
        return 0;
    }

#ifndef EB_NO_COUNTER
    int32_t counter = 0;
#endif

    // ===================== PRIVATE =====================
   protected:
    encb::Flags<uint8_t> ef;

   private:
    int8_t prev : 4;
    int8_t ecount : 4;
};
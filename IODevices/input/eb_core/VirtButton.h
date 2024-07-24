#pragma once
#include <Arduino.h>

#include "../../../mDef.h"
#include "flags.h"
#include "io.h"

#ifndef __AVR__
#include <functional>
#endif

// ===================== FLAGS ======================


#define EB_PRESS (1 << 0)        // button press
#define EB_HOLD (1 << 1)         // button hold
#define EB_STEP (1 << 2)         // step hold
#define EB_RELEASE (1 << 3)      // button release
#define EB_CLICK (1 << 4)        // single click
#define EB_CLICKS (1 << 5)       // multiple clicks
// #define EB_TURN (1 << 6)         // encoder turn
#define EB_REL_HOLD (1 << 7)     // button release after hold
#define EB_REL_HOLD_C (1 << 8)   // button release after hold with previous clicks
#define EB_REL_STEP (1 << 9)     // button release after step
#define EB_REL_STEP_C (1 << 10)  // button release after step with previous clicks


// =================== TOUT BUILD ===================
#define EB_SHIFT 4

// debounce timeout, ms
#ifdef EB_DEB_TIME
#define EB_DEB_T (EB_DEB_TIME)
#endif

// timeout between clicks, ms
#ifdef EB_CLICK_TIME
#define EB_CLICK_T (EB_CLICK_TIME)
#endif

// hold timeout, ms
#ifdef EB_HOLD_TIME
#define EB_HOLD_T (EB_HOLD_TIME)
#endif

// step period, ms
#ifdef EB_STEP_TIME
#define EB_STEP_T (EB_STEP_TIME)
#endif

// =================== PACK FLAGS ===================
#define EB_CLKS_R (1 << 0)
#define EB_PRS_R (1 << 1)
#define EB_HLD_R (1 << 2)
#define EB_STP_R (1 << 3)
#define EB_REL_R (1 << 4)

#define EB_PRS (1 << 5)
#define EB_HLD (1 << 6)
#define EB_STP (1 << 7)
#define EB_REL (1 << 8)

#define EB_BUSY (1 << 9)
#define EB_DEB (1 << 10)
#define EB_TOUT (1 << 11)

// =================== TOUT BUILD ===================
#define EB_SHIFT 4

// debounce timeout, ms
#ifdef EB_DEB_TIME
#define EB_DEB_T (EB_DEB_TIME)
#endif

// timeout between clicks, ms
#ifdef EB_CLICK_TIME
#define EB_CLICK_T (EB_CLICK_TIME)
#endif

// hold timeout, ms
#ifdef EB_HOLD_TIME
#define EB_HOLD_T (EB_HOLD_TIME)
#endif

// step period, ms
#ifdef EB_STEP_TIME
#define EB_STEP_T (EB_STEP_TIME)
#endif
#define EB_INV (1 << 12)
#define EB_BOTH (1 << 13)
#define EB_BISR (1 << 14)

#define EB_EHLD (1 << 15)

// base class for button
class VirtButton {


   public:
    // ====================== SET ======================
    // set hold timeout, default 600 (max 4000 ms)
    void setHoldTimeout(const uint16_t tout) {
    #ifndef EB_HOLD_TIME
            EB_HOLD_T = tout >> EB_SHIFT;
    #endif
        }


    // set pulse hold timeout, default 200 (max 4000 ms)
    void setStepTimeout(const uint16_t tout) {
    #ifndef EB_STEP_TIME
            EB_STEP_T = tout >> EB_SHIFT;
    #endif
        }


    // set click wait timeout, default 500 (max 4000 ms)
    void setClickTimeout(const uint16_t tout) {
    #ifndef EB_CLICK_TIME
            EB_CLICK_T = tout >> EB_SHIFT;
    #endif
        }


    // set debounce timeout, default 50 (max 255 ms)
    void setDebTimeout(const uint8_t tout) {
    #ifndef EB_DEB_TIME
            EB_DEB_T = tout;
    #endif
        }


    // set button level (HIGH - button connects to VCC, LOW - connects to GND)
    void setBtnLevel(const bool level) {
            bf.write(EB_INV, !level);
        }


    // button pressed in interrupt (does not consider btnLevel!)
    void pressISR() {
            if (!bf.read(EB_DEB)) tmr = EB_uptime();
            bf.set(EB_DEB | EB_BISR);
        }


    // reset system flags (forcibly finish processing)
    void reset() {
            clicks = 0;
            bf.clear(~EB_INV);
        }


    // forcibly clear event flags
    void clear() {
            if (bf.read(EB_CLKS_R)) clicks = 0;
            if (bf.read(EB_CLKS_R | EB_STP_R | EB_PRS_R | EB_HLD_R | EB_REL_R)) {
                bf.clear(EB_CLKS_R | EB_STP_R | EB_PRS_R | EB_HLD_R | EB_REL_R);
            }
        }


    // ignore all events until the button is released
    void skipEvents() {
            bf.set(EB_EHLD);
        }


    // attach event handler function (of type void f())
    void attach(func_p handler) {
    #ifndef EB_NO_CALLBACK
            if (handler!=nullptr){
                cb = handler;
            }
    #endif
        }


    // detach the event handler function
    void detach() {
    #ifndef EB_NO_CALLBACK
            cb = nullptr;
    #endif
        }


    // ====================== GET ======================
    // button pressed [event]
    bool press() {
            return bf.read(EB_PRS_R);
        }


    // button pressed with preliminary clicks [event]
    bool press(const uint8_t num) {
            return (clicks == num) && press();
        }


    // button released (in any case) [event]
    bool release() {
            return bf.eq(EB_REL_R | EB_REL, EB_REL_R | EB_REL);
        }


    // button released (in any case) with preliminary clicks [event]
    bool release(const uint8_t num) {
            return (clicks == num) && release();
        }


    // button click (released without holding) [event]
    bool click() {
            return bf.eq(EB_REL_R | EB_REL | EB_HLD, EB_REL_R);
        }


    // button click (released without holding) with preliminary clicks [event]
    bool click(const uint8_t num) {
            return (clicks == num) && click();
        }


    // button is being pressed (between press() and release()) [state]
    bool pressing() {
            return bf.read(EB_PRS);
        }


    // button is being pressed (between press() and release()) with preliminary clicks [state]
    bool pressing(const uint8_t num) {
            return (clicks == num) && pressing();
        }


    // button was held (longer than timeout) [event]
    bool hold() {
            return bf.read(EB_HLD_R);
        }


    // button was held (longer than timeout) with preliminary clicks [event]
    bool hold(const uint8_t num) {
            return (clicks == num) && hold();
        }


    // button is being held (longer than timeout) [state]
    bool holding() {
            return bf.eq(EB_PRS | EB_HLD, EB_PRS | EB_HLD);
        }


    // button is being held (longer than timeout) with preliminary clicks [state]
    bool holding(const uint8_t num) {
            return (clicks == num) && holding();
        }


    // pulse holding [event]
    bool step() {
            return bf.read(EB_STP_R);
        }


    // pulse holding with preliminary clicks [event]
    bool step(const uint8_t num) {
            return (clicks == num) && step();
        }


    // multiple clicks detected [event]
    bool hasClicks() {
            return bf.eq(EB_CLKS_R | EB_HLD, EB_CLKS_R);
        }


    // specified number of clicks detected [event]
    bool hasClicks(const uint8_t num) {
            return (clicks == num) && hasClicks();
        }


    // get the number of clicks
    uint8_t getClicks() {
            return clicks;
        }


    // get the number of steps
    uint16_t getSteps() {
    #ifndef EB_NO_FOR
    #ifdef EB_STEP_TIME
            return ftmr ? ((stepFor() + EB_STEP_T - 1) / EB_STEP_T) : 0;  // (x + y - 1) / y
    #else
            return ftmr ? ((stepFor() + (EB_STEP_T << EB_SHIFT) - 1) / (EB_STEP_T << EB_SHIFT)) : 0;
    #endif
    #endif
            return 0;
        }


    // button released after holding [event]
    bool releaseHold() {
            return bf.eq(EB_REL_R | EB_REL | EB_HLD | EB_STP, EB_REL_R | EB_HLD);
        }


    // button released after holding with preliminary clicks [event]
    bool releaseHold(const uint8_t num) {
            return clicks == num && bf.eq(EB_CLKS_R | EB_HLD | EB_STP, EB_CLKS_R | EB_HLD);
        }


    // button released after pulse holding [event]
    bool releaseStep() {
            return bf.eq(EB_REL_R | EB_REL | EB_STP, EB_REL_R | EB_STP);
        }


    // button released after pulse holding with preliminary clicks [event]
    bool releaseStep(const uint8_t num) {
            return clicks == num && bf.eq(EB_CLKS_R | EB_STP, EB_CLKS_R | EB_STP);
        }


    // button released after holding or pulse holding [event]
    bool releaseHoldStep() {
            return releaseHold() || releaseStep();
        }


    // button released after holding or pulse holding with preliminary clicks [event]
    bool releaseHoldStep(const uint8_t num) {
            return releaseHold(num) || releaseStep(num);
        }


    // button waiting for repeated clicks [state]
    bool waiting() {
            return clicks && bf.eq(EB_PRS | EB_REL, 0);
        }


    // processing ongoing [state]
    bool busy() {
            return bf.read(EB_BUSY);
        }


    // an action from the button occurred, returns event code [event]
    uint16_t action() {
            switch (bf.mask(0b111111111)) {
                case (EB_PRS | EB_PRS_R):
                    return EB_PRESS;
                case (EB_PRS | EB_HLD | EB_HLD_R):
                    return EB_HOLD;
                case (EB_PRS | EB_HLD | EB_STP | EB_STP_R):
                    return EB_STEP;
                case (EB_REL | EB_REL_R):
                case (EB_REL | EB_REL_R | EB_HLD):
                case (EB_REL | EB_REL_R | EB_HLD | EB_STP):
                    return EB_RELEASE;
                case (EB_REL_R):
                    return EB_CLICK;
                case (EB_CLKS_R):
                    return EB_CLICKS;
                case (EB_REL_R | EB_HLD):
                    return EB_REL_HOLD;
                case (EB_CLKS_R | EB_HLD):
                    return EB_REL_HOLD_C;
                case (EB_REL_R | EB_HLD | EB_STP):
                    return EB_REL_STEP;
                case (EB_CLKS_R | EB_HLD | EB_STP):
                    return EB_REL_STEP_C;
            }
            return 0;
        }


    // ====================== TIME ======================
    // specified time has passed since interaction with the button (or EncButton encoder), ms [event]
    bool timeout(const uint16_t tout) {
            if (bf.read(EB_TOUT) && (uint16_t)((uint16_t)EB_uptime() - tmr) > tout) {
                bf.clear(EB_TOUT);
                return 1;
            }
            return 0;
        }


    // time the button has been held (from the start of pressing), ms
    uint16_t pressFor() {
    #ifndef EB_NO_FOR
            if (ftmr) return (uint16_t)EB_uptime() - ftmr;
    #endif
            return 0;
        }


    // button is held longer than (from the start of pressing), ms [state]
    bool pressFor(const uint16_t ms) {
            return pressFor() > ms;
        }
        


    // time the button has been held (from the start of holding), ms
    uint16_t holdFor() {
    #ifndef EB_NO_FOR
            if (bf.read(EB_HLD)) {
    #ifdef EB_HOLD_TIME
                return pressFor() - EB_HOLD_T;
    #else
                return pressFor() - (EB_HOLD_T << EB_SHIFT);
    #endif
            }
    #endif
            return 0;
        }



    // the button is held longer than (from the start of holding), ms [state]
    bool holdFor(const uint16_t ms) {
        return holdFor() > ms;
    }

    // the time the button is held (from the start of the step), ms
    uint16_t stepFor() {
#ifndef EB_NO_FOR
        if (bf.read(EB_STP)) {
#ifdef EB_HOLD_TIME
            return pressFor() - EB_HOLD_T * 2;
#else
            return pressFor() - (EB_HOLD_T << EB_SHIFT) * 2;
#endif
        }
#endif
        return 0;
    }

    // the button is held longer than (from the start of the step), ms [state]
    bool stepFor(uint16_t ms) {
        return stepFor() > ms;
    }

    // ====================== POLL ======================
    // processing the virtual button as simultaneous pressing of two other buttons
    bool tick(VirtButton& b0, VirtButton& b1) {
        if (bf.read(EB_BOTH)) {
            if (!b0.pressing() && !b1.pressing()) bf.clear(EB_BOTH);
            if (!b0.pressing()) b0.reset();
            if (!b1.pressing()) b1.reset();
            b0.clear();
            b1.clear();
            return tick(1);
        } else {
            if (b0.pressing() && b1.pressing()) bf.set(EB_BOTH);
            return tick(0);
        }
    }

    // processing the button by value
    bool tick(bool s) {
        clear();
        s = pollBtn(s);
#ifndef EB_NO_CALLBACK
        if (cb && s) cb();
#endif
        return s;
    }

    // processing the button without resetting events and calling the callback
    bool tickRaw(const bool s) {
        return pollBtn(s);
    }

    uint8_t clicks;

    // deprecated
    void setButtonLevel(bool level) {
        bf.write(EB_INV, !level);
    }

    // ====================== PRIVATE ======================
   protected:
    uint16_t tmr = 0;
    encb::Flags<uint16_t> bf;

#ifndef EB_NO_CALLBACK
    func_p cb = nullptr;
#endif

   private:
#ifndef EB_NO_FOR
    uint16_t ftmr = 0;//todo in 32 bit
#endif
#ifndef EB_DEB_TIME
    uint8_t EB_DEB_T = 50;
#endif
#ifndef EB_CLICK_TIME
    uint8_t EB_CLICK_T = (500 >> EB_SHIFT);
#endif
#ifndef EB_HOLD_TIME
    uint8_t EB_HOLD_T = (600 >> EB_SHIFT);
#endif
#ifndef EB_STEP_TIME
    uint8_t EB_STEP_T = (200 >> EB_SHIFT);
#endif

    bool pollBtn(bool s) {
        if (bf.read(EB_BISR)) {
            bf.clear(EB_BISR);
            s = 1;
        } else s ^= bf.read(EB_INV);

        if (!bf.read(EB_BUSY)) {
            if (s) bf.set(EB_BUSY);
            else return 0;
        }

        uint16_t ms = EB_uptime();
        uint16_t deb = ms - tmr;

        if (s) {                                         // button pressed
            if (!bf.read(EB_PRS)) {                      // button was not pressed before
                if (!bf.read(EB_DEB) && EB_DEB_T) {      // debounce has not triggered yet
                    bf.set(EB_DEB);                      // we will wait for debounce
                    tmr = ms;                            // reset timeout
                } else {                                 // first press
                    if (deb >= EB_DEB_T || !EB_DEB_T) {  // wait for EB_DEB_TIME
                        bf.set(EB_PRS | EB_PRS_R);       // flag for press
#ifndef EB_NO_FOR
                        ftmr = ms;
#endif
                        tmr = ms;  //reset timeout
                    }
                }
            } else {  // the button was already pressed
                if (!bf.read(EB_EHLD)) {
                    if (!bf.read(EB_HLD)) {  // hold not yet registered
#ifdef EB_HOLD_TIME
                        if (deb >= (uint16_t)EB_HOLD_T) {  // waiting for EB_HOLD_TIME - it's a hold
#else
                        if (deb >= (uint16_t)(EB_HOLD_T << EB_SHIFT)) {  // waiting for EB_HOLD_TIME - it's a hold
#endif
                            bf.set(EB_HLD_R | EB_HLD);  // flag that there was a hold
                            tmr = ms;                   // reset timeout
                        }
                    } else {  // hold registered
#ifdef EB_STEP_TIME
                        if (deb >= (uint16_t)(bf.read(EB_STP) ? EB_STEP_T : EB_HOLD_T)) {
#else
                        if (deb >= (uint16_t)(bf.read(EB_STP) ? (EB_STEP_T << EB_SHIFT) : (EB_HOLD_T << EB_SHIFT))) {
#endif
                            bf.set(EB_STP | EB_STP_R);  // step flag
                            tmr = ms;                   // reset timeout
                        }
                    }
                }
            }
        } else {                                       // button not pressed
            if (bf.read(EB_PRS)) {                     // but was pressed
                if (deb >= EB_DEB_T) {                 // wait for EB_DEB_TIME
                    if (!bf.read(EB_HLD)) clicks++;    // not held - it's a click
                    if (bf.read(EB_EHLD)) clicks = 0;  //
                    bf.set(EB_REL | EB_REL_R);         // release flag
                    bf.clear(EB_PRS);                  // button released
                }
            } else if (bf.read(EB_REL)) {
                if (!bf.read(EB_EHLD)) {
                    bf.set(EB_REL_R);  // releaseHold / releaseStep flag
                }
                bf.clear(EB_REL | EB_EHLD);
                tmr = ms;         //reset timeout
            } else if (clicks) {  // if there are clicks, wait for EB_CLICK_TIME
#ifdef EB_CLICK_TIME
                if (bf.read(EB_HLD | EB_STP) || deb >= (uint16_t)EB_CLICK_T) bf.set(EB_CLKS_R);  // clicks flag
#else
                if (bf.read(EB_HLD | EB_STP) || deb >= (uint16_t)(EB_CLICK_T << EB_SHIFT)) bf.set(EB_CLKS_R);  // clicks flag
#endif
#ifndef EB_NO_FOR
                else if (ftmr) ftmr = 0;
#endif
            } else if (bf.read(EB_BUSY)) {
                bf.clear(EB_HLD | EB_STP | EB_BUSY);
                bf.set(EB_TOUT);
#ifndef EB_NO_FOR
                ftmr = 0;
#endif
                tmr = ms;  // test!!
            }
            if (bf.read(EB_DEB)) bf.clear(EB_DEB);  // reset debounce wait
        }
        return bf.read(EB_CLKS_R | EB_PRS_R | EB_HLD_R | EB_STP_R | EB_REL_R);
    }
};
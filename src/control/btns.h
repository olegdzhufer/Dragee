#ifndef BTNS_DEF_H
#define BTNS_DEF_H


#include "inc.h"
#include "mDef.h"

Button btn1(BTN1, INPUT_PULLUP, LOW);
Button btn2(BTN2, INPUT_PULLUP, LOW);
Button btnSwitch(BTN3, INPUT_PULLUP, LOW);

#define FULL_OFF_COOLING { \
    COOLING_OURSCREEN; \
    COOLING_OFF; \
}

#define FULL_OFF_HEAP { \
    HEAP_OURSCREEN; \
    HEAP_OFF; \
}


void callbackBtn1() {
    switch (btn1.action()) {
      
        case EB_CLICK:
            if(!(HEAP_ONSCREEN)){
                HEAP_ONSCREEN;
                FULL_OFF_COOLING;
                STOP_OFF;
            }
            else if (HEAP_ONSCREEN && FAN_CHECK && !(HEAP_CHECK)){
                HEAP_ON;
                FULL_OFF_COOLING;
                STOP_OFF;
            }else if(HEAP_ONSCREEN && !(HEAP_CHECK) && !(FAN_CHECK)){
                //Here plase code to print in MENU such as "FAN is not on !"

            }else if(HEAP_ONSCREEN && HEAP_CHECK){
                FULL_OFF_HEAP;
                STOP_ON;
            }
            break;

        default:
        break;
    }
}

void callbackBtn2() {
    switch (btn2.action()) {
        
        case EB_CLICK:
            if(!(COOLING_ONSCREEN)){
                COOLING_ONSCREEN;
                FULL_OFF_HEAP;
                STOP_OFF;
            }
            else if (COOLING_ONSCREEN && FAN_CHECK && !(COOLING_CHECK)){
                COOLING_ON;
                FULL_OFF_HEAP;
                STOP_OFF;
            }else if(COOLING_ONSCREEN && !(COOLING_CHECK) && !(FAN_CHECK)){
                //Here plase code to print in MENU such as "FAN is not on !"

            }else if(COOLING_ONSCREEN && COOLING_CHECK){
                FULL_OFF_COOLING;
                STOP_ON;
            }
            break;

        default:
        break;
    }
}

void callbackSwitch() {
    switch (btnSwitch.action()) {
      
        case EB_HOLD:
            
            break;

        case EB_RELEASE:
            
            break;
        default:
            //Serial.println();
    }
}



void btnsSetup() {
    btn1.attach(callbackBtn1);
    btn2.attach(callbackBtn2);
    btnSwitch.attach(callbackSwitch);

}

void btnsLoop(){
     btn1.tick();

}
// void btnsSetCallback(void (*callback)(int));
// void btnsSetCallback(void (*callback)());




#endif
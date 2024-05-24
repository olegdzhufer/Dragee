#include <Arduino.h>
#include <Menulib.h>



static Menu menu;
Screen* mainS;


//flag to use

// 0 - bit flag updata LCD
// 1 - bit flag updata tepm data
// 2 - bit flag data in enc
// 3 - bit flag button pres
// 4 - bit flag FAN is on
// 5 - bit flag
// 6 - bit flag setup LCD
// 7 - bit flag end init Menu


uint8_t REG_FLAG;



#include "dependenci/pins.h"
#include "dependenci/btns.h"
#include "dependenci/dallas_sensor.h"
#include "dependenci/led.h"
#include "dependenci/menu.h"
#include "dependenci/encoder.h"
#include "dependenci/TimerSet.h"

int encderVal = 0x00;
int prin = 0;
int press = 0;

int key;






void setup() {


    Serial.begin(9600);
    encoder_setup();
    menu = *(initMenu());
    init_Screen(&menu);
    dallas_setup();
    setup_Menu(&menu);
    timer_setup();

    mainS = menu.curr;  
}


void loop() {

    read_encoder();
    if(REG_FLAG & (1 << 2)){
        press = getResult();
    }

    timer_loop();


    if(REG_FLAG & (1 << 0)){
        TempCurH->val->setfloat(TempCurH->val, most_recent_temperature_measurement);
        TempCurC->val->setfloat(TempCurC->val, most_recent_temperature_measurement);
        TempCurF->val->setfloat(TempCurF->val, most_recent_temperature_measurement);

        menu.printScreen(&menu);
        REG_FLAG &= ~(1 << 0);
    }


    if(press){

        Screen* curr;
        switch (press)
        {
        case 1:
            menu.prevLine(&menu);
        break;
        case 2:
            menu.nextLine(&menu);
        break;
        case 5:            
            menu.nextLine(&menu);

        }

        press = 0;
    }
}


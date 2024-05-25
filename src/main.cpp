#include "dependenci/inc&var.h"


void updataTemp();

void flagCheker();
void lcdSenter();

void btnWork();


void setup() {


    Serial.begin(9600);
    encoder_setup();
    menu = *(initMenu());
    init_Screen(&menu);
    dallas_setup();
    buttons_setup();
    setup_Menu(&menu);
    timer_setup();

    mainS = menu.curr;  

    ActiveTime time;
}




void loop() {
    


    read_encoder();
    loop_btn();
    flagCheker();

    updataTemp();
    timer_loop();

    


    if(pressbtn){

        btnWork();
        pressbtn = 0;
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


void updataTemp(){
    if(REG_FLAG & (1 << 4)){
        Serial.print(1);
    }

    if(REG_FLAG & (1 << 0)){
        TempCurH->val->setfloat(TempCurH->val, most_recent_temperature_measurement);
        TempCurC->val->setfloat(TempCurC->val, most_recent_temperature_measurement);
        TempCurF->val->setfloat(TempCurF->val, most_recent_temperature_measurement);

        menu.printScreen(&menu);
        REG_FLAG &= ~(1 << 0);
    }
}

void flagCheker(){
    if(REG_FLAG & (1 << 2)){
        press = getResult();
    }
    if(REG_FLAG & (1 << 3)){
        pressbtn = getBtn();
    }
    if(REG_FLAG & FAN_STATUS)
}

void btnWork(){
    Serial.printf("");
    switch (pressbtn)
        {
        case 0x01:

            if(!(REG_FLAG & (1 << 4)) | (REG_STATUS & (1 << 0))){
                REG_STATUS = 0;
            }else if(REG_FLAG & (1 << 4)){
                menu.curr = Heap;
                REG_STATUS |= (1 << 0);
            }

        break;


        case 0x02:
            if(!(REG_FLAG & (1 << 4)) | (REG_STATUS & (1 << 1))){
                REG_STATUS &= ~(1 << 1);
            }else if(REG_FLAG & (1 << 4)){
                menu.curr = Heap;
                REG_STATUS |= (1 << 1);
            }
        break;

        }
}
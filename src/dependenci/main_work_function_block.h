
#define HEAP_DISPLAY    REG_MENU_STATUS & HEAP_SELECT
#define COOLING_DISPLAY REG_MENU_STATUS & COOLING_SELECT

#define HEAP_ON_OFF     REG_MENU_STATUS & HEAP_STATUS
#define COOLING_ON_OFF  REG_MENU_STATUS & COOLING_STATUS

#define FAN_DISPLAY     REG_MENU_STATUS & FAN_SELECT
#define FAN_ON_OFF      REG_FLAG_S & FAN_STATUS



void updataTemp();

void flagCheker();
void lcdSenter();

void btnWork();
void encWork();


void init_main(){
        Serial.begin(9600);
        encoder_setup();
        menu = *(initMenu());
        init_Screen(&menu);
        dallas_setup(); 
        buttons_setup();
        setup_Menu(&menu);
        timer_setup();

        mainS = menu.curr;  
}

void main_loop(){
    read_encoder();
    loop_btn();
    flagCheker();

    btnWork();
    encWork();
}



//______________________________________________________________________________________


void updataTemp(){

    if(REG_FLAG & RELOAD_LCD){
        TempCurH->val->setfloat(TempCurH->val, most_recent_temperature_measurement);
        TempCurC->val->setfloat(TempCurC->val, most_recent_temperature_measurement);
        TempCurF->val->setfloat(TempCurF->val, most_recent_temperature_measurement);

        menu.printScreen(&menu);
        REG_FLAG &= ~(1 << 0);
    }
}


void flagCheker(){

    if(REG_FLAG & FAN_STATUS){
        Serial.printf("\n DS \n");
    }

    if(REG_MENU_STATUS)
    updataTemp();
    // timer_loop();
    SwichMenu();

    
}


/*!
    @brief If btn is press check her and clear press to corectabele work
*/

void HeapBTN(){

    if(!REG_MENU_STATUS & HEAP_DISPLAY){
        REG_MENU_STATUS &= ~(COOLING_SELECT | STOP_SELECT | FAN_SELECT) | ~(COOLING_STATUS);
        REG_MENU_STATUS |= HEAP_SELECT ;
    }else if(REG_MENU_STATUS & HEAP_DISPLAY && !(REG_MENU_STATUS & HEAP_ON_OFF) && REG_FLAG & FAN_ON_OFF){
        REG_MENU_STATUS |= HEAP_STATUS;
    }else if(REG_MENU_STATUS & HEAP_DISPLAY && !(REG_MENU_STATUS & HEAP_ON_OFF)){
        ExeptDropFanIsNotEnable();
        REG_FLAG |= RELOAD_LCD;
    }else if(REG_MENU_STATUS & HEAP_DISPLAY && REG_MENU_STATUS & HEAP_ON_OFF){
        REG_MENU_STATUS &= ~HEAP_STATUS | HEAP_ON_OFF;
    }
    REG_FLAG |= CHANGEMOD;
}

void CoolingBTN(){
    if(!REG_MENU_STATUS & COOLING_DISPLAY){
        REG_MENU_STATUS &= ~(HEAP_SELECT | STOP_SELECT | FAN_SELECT) | ~(HEAP_STATUS);
        REG_MENU_STATUS |= COOLING_SELECT ;
    }else if(REG_MENU_STATUS & COOLING_DISPLAY && !(REG_MENU_STATUS & COOLING_ON_OFF) && REG_FLAG & FAN_ON_OFF){
        REG_MENU_STATUS |= COOLING_STATUS;
    }else if(REG_MENU_STATUS & HEAP_DISPLAY && !(REG_MENU_STATUS & HEAP_ON_OFF)){
        ExeptDropFanIsNotEnable();
        REG_FLAG |= RELOAD_LCD;
    }else if(REG_MENU_STATUS & HEAP_DISPLAY && REG_MENU_STATUS & HEAP_ON_OFF){
        REG_MENU_STATUS &= ~COOLING_STATUS | COOLING_ON_OFF;
    }
    REG_FLAG |= CHANGEMOD;
}


void btnWork(){

    if(REG_FLAG & BTN_INT){

        Serial.printf("12");

        switch (buttonState)
        {
        case 0x01:
            HeapBTN();
        break;


        case 0x02:
            CoolingBTN();
        break;

        }
        REG_FLAG &= ~BTN_INT;
    }
    
}

void encWork(){

    if(press){
        Screen* curr;

        switch (press){

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
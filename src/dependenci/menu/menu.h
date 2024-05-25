#ifndef MENU_H
#define MENU_H
#include "charList.h"

void setTemp();

void setup_Menu(Menu* menu );


void init_Screen(Menu* menu){
    
unsigned long timer = millis();
unsigned long start_time = millis();




while (!(REG_FLAG & (1 << 7))) {
    unsigned long current_time = millis();
    
    if (current_time - timer >= 600) {
        timer = current_time;
        menu->lcd->clear();
        menu->lcd->setCursor(0, 0);
        menu->lcd->printf(initFLine);
        
        if (current_time - start_time >= 600) {
            menu->lcd->setCursor(0, 1);
            menu->lcd->printf(initSLine);
        }
        
        if (current_time - start_time >= 1200) {
            menu->lcd->setCursor(0, 2);
            menu->lcd->printf(initTLine);
        }
        
        if (current_time - start_time >= 1800) {
            REG_FLAG |= (1 << 7);
            REG_FLAG |= (1 << 0);
        }
    }

    setup_Menu(menu);
}
menu->printScreen(menu);

}


void setup_Menu(Menu* menu ){

    if(!(REG_FLAG & (1 << 6))){




        Heap = menu->addScreen_ptr(menu, (char*)HeapName);

        TempSetH = Heap->newLine_ptr(Heap, (char*)TSet, (char*)TempSet, NULL);
        TempSetH->val->setfloat(TempSetH->val, tcH);
        TempCurH = Heap->newLine_ptr(Heap, (char*)TCur ,(char*)TempCurr, NULL);
        TempCurH->val->setfloat(TempCurH->val, 60.1);

        Cooling = menu->addScreen_ptr(menu, (char*)CoolingName);

        TempSetC = Cooling->newLine_ptr(Cooling, (char*)TSet, (char*)TempCurr, NULL);
        TempSetC->val->setfloat(TempSetC->val, tcC);
        TempCurC = Cooling->newLine_ptr(Cooling, (char*)TCur, (char*)TempCurr, NULL);
        TempCurC->val->setfloat(TempCurC->val, 60.1);


        FAN = menu->addScreen_ptr(menu, (char*)Fan);
        TempCurF = FAN->newLine_ptr(FAN, (char*)TCur, (char*)TempCurr, NULL);
        TempCurF->val->setfloat(TempCurF->val, 60.1);

        STOP = menu->addScreen_ptr(menu, (char*)Stop);
        TempCurS = STOP->newLine_ptr(STOP, (char*)Stop, (char*)Empty, NULL);


        menu->curr = Heap;
        REG_FLAG |= (1 << 6);
    }
}




#endif
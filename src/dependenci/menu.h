#ifndef MENU_H
#define MENU_H

#include <Menulib.h>

Screen* Heap, *Cooling, *FAN, *STOP;
Line* TempSetH, *TempCurH, *TempSetC, *TempCurC, *TempCurF, *TempCurS;


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
        menu->lcd->printf("      INIT.....   ");
        
        if (current_time - start_time >= 600) {
            menu->lcd->setCursor(0, 1);
            menu->lcd->printf(" Slava Ukraine");
        }
        
        if (current_time - start_time >= 1200) {
            menu->lcd->setCursor(0, 2);
            menu->lcd->printf("     Smert Moskalam");
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
        Heap = menu->addScreen_ptr(menu, "HEAP");

        TempSetH = Heap->newLine_ptr(Heap, "TSet","TempSet:", NULL);
        TempSetH->val->setfloat(TempSetH->val, 45.60);
        TempCurH = Heap->newLine_ptr(Heap, "TCur","TempCurr:", NULL);
        TempCurH->val->setfloat(TempCurH->val, 60.1);

        Cooling = menu->addScreen_ptr(menu, "COOLING");

        TempSetC = Cooling->newLine_ptr(Cooling,"TSet", "TempSet:", NULL);
        TempSetC->val->setfloat(TempSetC->val, 60.1);
        TempCurC = Cooling->newLine_ptr(Cooling, "TCur", "TempCurr:", NULL);
        TempCurC->val->setfloat(TempCurC->val, 60.1);


        FAN = menu->addScreen_ptr(menu, "FAN");
        TempCurF = FAN->newLine_ptr(FAN, "TCur", "TempCurr:", NULL);
        TempCurF->val->setfloat(TempCurF->val, 60.1);

        STOP = menu->addScreen_ptr(menu, "STOP");
        TempCurS = STOP->newLine_ptr(STOP, "STOP", "", NULL);


        menu->curr = Heap;
        REG_FLAG |= (1 << 6);
    }
}


#endif
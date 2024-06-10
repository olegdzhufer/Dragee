#ifndef MENU_SETUP_H
#define MENU_SETUP_H

#include <MenuLib.h>
//#include "lcd.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "mDef.h"
#include "charList.h"


Menu menu;

//menu
Screen* mainS;
Screen* Heat, *Cooling, *FAN, *STOP;
Line* TempSetH, *TempCurH, *TempSetC, *TempCurC, *TempCurF, *TempCurS;
float tcH = 0, tcC = 0 ;
//________________________________


STATUS_t menuSetup()
{
    
    menu = *(initMenu());

    Heat = menu.addScreen_ptr(&menu, (char*)HeatName);

    TempSetH = Heat->newLine_ptr(Heat, (char*)TSet, (char*)TempSet, NULL);
    TempSetH->val->setfloat(TempSetH->val, tcH);
    TempCurH = Heat->newLine_ptr(Heat, (char*)TCur ,(char*)TempCurr, NULL);
    TempCurH->val->setfloat(TempCurH->val, 60.1);

    Cooling = menu.addScreen_ptr(&menu, (char*)CoolingName);

    TempSetC = Cooling->newLine_ptr(Cooling, (char*)TSet, (char*)TempCurr, NULL);
    TempSetC->val->setfloat(TempSetC->val, tcC);
    TempCurC = Cooling->newLine_ptr(Cooling, (char*)TCur, (char*)TempCurr, NULL);
    TempCurC->val->setfloat(TempCurC->val, 60.1);


    FAN = menu.addScreen_ptr(&menu, (char*)Fan);
    TempCurF = FAN->newLine_ptr(FAN, (char*)TCur, (char*)TempCurr, NULL);
    TempCurF->val->setfloat(TempCurF->val, 60.1);

    STOP = menu.addScreen_ptr(&menu, (char*)Stop);
    TempCurS = STOP->newLine_ptr(STOP, (char*)Stop, (char*)Empty, NULL);

    menu.printScreen(&menu);

    
    return STATUS_OK;
}


void menuLoop()
{
    
}

#endif
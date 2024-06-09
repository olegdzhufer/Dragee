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
Screen* Heap, *Cooling, *FAN, *STOP;
Line* TempSetH, *TempCurH, *TempSetC, *TempCurC, *TempCurF, *TempCurS;
float tcH = 0, tcC = 0 ;
//________________________________

STATUS_C initSection();


STATUS_C menuSetup()
{
    
    return STATUS_OK;
}


void menuLoop()
{
    
}


//________________________________________________________________________

STATUS_C initSection(){
    menu = *(initMenu());

    if(&menu){

        Heap = menu.addScreen_ptr(&menu, (char*)HeapName);
        Cooling = menu.addScreen_ptr(&menu, (char*)CoolingName);
        FAN = menu.addScreen_ptr(&menu, (char*)Fan);
        STOP = menu.addScreen_ptr(&menu, (char*)Stop);

        if(Heap){
            TempSetH = Heap->newLine_ptr(Heap, (char*)TSet, (char*)TempSet, NULL);
            TempSetH->val->setfloat(TempSetH->val, tcH);
            TempCurH = Heap->newLine_ptr(Heap, (char*)TCur ,(char*)TempCurr, NULL);
            TempCurH->val->setfloat(TempCurH->val, 0.0);
        }else{
            return FAILURE;
        }


        if(Cooling){
            TempSetC = Cooling->newLine_ptr(Cooling, (char*)TSet, (char*)TempCurr, NULL);
            TempSetC->val->setfloat(TempSetC->val, tcC);
            TempCurC = Cooling->newLine_ptr(Cooling, (char*)TCur, (char*)TempCurr, NULL);
            TempCurC->val->setfloat(TempCurC->val, 0.0);
        }else{
            return FAILURE;
        }

        if(FAN){
            TempCurF = FAN->newLine_ptr(FAN, (char*)TCur, (char*)TempCurr, NULL);
            TempCurF->val->setfloat(TempCurF->val, 0.0);
        }else{
            return FAILURE;
        }

        if(STOP){
            TempCurS = STOP->newLine_ptr(STOP, (char*)Stop, (char*)Empty, NULL);
        }else{
            return FAILURE;
        }
        return STATUS_OK;
    }
    return FAILURE;
} 

#endif
#ifndef MENU_SETUP_H

#define MENU_SETUP_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "settings.h"
#include "charList.h"

Menu menu;

Screen *Heat, *Cooling, *FAN, *STOP, *Setting, *PIDScreen;
Line *TempSetH, *TempCurH, *TempSetC, *TempCurC, *TempCurF, *TempCurS, *footerHeat, *footerCool, *PIDLine;

  #ifdef MENU_S

    void initScreen(){
      menu.lcd->clear();
      menu.lcd->setCursor(0, 0);
      menu.lcd->printf(initFirstLine);
      
      delay(600);
      menu.lcd->setCursor(0, 1);
      menu.lcd->printf(initSecondLine);
      
      
      delay(600);
      menu.lcd->setCursor(0, 2);
      menu.lcd->printf(initThirdLine);
      
      delay(500);
    }

    STATUS_t initSection() {
        #ifdef DEBUG_FUNC
          Serial.println(__func__);
        #endif
      menu = *(initMenu());

      Heat = menu.addScreen_ptr(&menu, (char*)HeatName);
      Cooling = menu.addScreen_ptr(&menu, (char*)CoolingName);
      FAN = menu.addScreen_ptr(&menu, (char*)Fan);
      STOP = menu.addScreen_ptr(&menu, (char*)Stop);

      if (Heat) {
        TempSetH = Heat->newLine_ptr(Heat, (char*)TSet, (char*)TempSet, NULL);
        TempSetH->val->setfloat(TempSetH->val, TargetTemp);
        TempCurH = Heat->newLine_ptr(Heat, (char*)TCur, (char*)TempCurr, NULL);
        TempCurH->val->setfloat(TempCurH->val, Temperature);
      } else {
        return FAILURE;
      }


      if (Cooling) {
        TempSetC = Cooling->newLine_ptr(Cooling, (char*)TSet, (char*)TempSet, NULL);
        TempSetC->val->setfloat(TempSetC->val, FrostTemp);
        TempCurC = Cooling->newLine_ptr(Cooling, (char*)TCur, (char*)TempCurr, NULL);
        TempCurC->val->setfloat(TempCurC->val, Temperature);
      } else {
        return FAILURE;
      }

      if (FAN) {
        TempCurF = FAN->newLine_ptr(FAN, (char*)TCur, (char*)TempCurr, NULL);
        TempCurF->val->setfloat(TempCurF->val, Temperature);
      } else {
        return FAILURE;
      }

      if (STOP) {
        TempCurS = STOP->newLine_ptr(STOP, (char*)Stop, (char*)Empty, NULL);
      }else {
        return FAILURE;
      }



      footerHeat =  initLine("HeatFooter", " ", NULL);
      footerCool =  initLine("CoolFooter", " ", NULL);

      footerHeat->val->setChar(footerHeat->val, " ");
      footerCool->val->setChar(footerCool->val, " ");

      initScreen();
      menu.lcd->clear();
        return STATUS_OK;

    }

    void lcdLoop(){
      if(FLAG_LCD){
        #ifdef DEBUG_FUNC
          Serial.println(__func__);
        #endif
        menu.printScreen(&menu);
        FLAG_LCD = false;
      }
    }
  #endif


#endif

#ifndef MENU_SETUP_H

#define MENU_SETUP_H


#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "coreMenu/MenuLib.h"
#include "settings.h"
#include "charList.h"
#include "countTimer.h"


uint8_t timeRecover = 0;


STATUS_t initSection() {
  Serial.println(__func__);
  menu = *(initMenu());

  // if (&menu) {//always not null

  Heat = menu.addScreen_ptr(&menu, (char *)HeatName);
  Cooling = menu.addScreen_ptr(&menu, (char *)CoolingName);
  FAN = menu.addScreen_ptr(&menu, (char *)Fan);
  STOP = menu.addScreen_ptr(&menu, (char *)Stop);

  if (Heat) {
    TempSetH = Heat->newLine_ptr(Heat, (char *)TSet, (char *)TempSet, NULL);
    TempSetH->val->setfloat(TempSetH->val, TargetTemp);
    TempCurH = Heat->newLine_ptr(Heat, (char *)TCur, (char *)TempCurr, NULL);
    TempCurH->val->setfloat(TempCurH->val, Temperature);

    
  } else {
    return FAILURE;
  }


  if (Cooling) {
    TempSetC = Cooling->newLine_ptr(Cooling, (char *)TSet, (char *)TempCurr, NULL);
    TempSetC->val->setfloat(TempSetC->val, TargetTemp);
    TempCurC = Cooling->newLine_ptr(Cooling, (char *)TCur, (char *)TempCurr, NULL);
    TempCurC->val->setfloat(TempCurC->val, Temperature);

  } else {
    return FAILURE;
  }

  if (FAN) {
    TempCurF = FAN->newLine_ptr(FAN, (char *)TCur, (char *)TempCurr, NULL);
    TempCurF->val->setfloat(TempCurF->val, Temperature);
  } else {
    return FAILURE;
  }

  if (STOP) {
    TempCurS = STOP->newLine_ptr(STOP, (char *)Stop, (char *)Empty, NULL);
  } else {
    return FAILURE;
  }

  footerLine = initLine( "Timer: ", "Timer", NULL);
  footerLine->val->setChar(footerLine->val, "");
  FAN->footer = footerLine;



  return STATUS_OK;
  // }
  // return FAILURE;
}

void lcdLoop() {

  if (FLAG_LCD) {
    timeRecover = millis();
    menu.printScreen(&menu);
    FLAG_LCD = false;
  }
}


#endif

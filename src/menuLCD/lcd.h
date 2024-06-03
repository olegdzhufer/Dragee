#ifndef LCD_SETUP_H
#define LCD_SETUP_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "mDef.h"
#include "charList.h"



bool lcdFlag = false;

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

STATUS_C lcdSetup()
{
    lcd.init();
   
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hello, world!");
    lcd.setCursor(0, 1);
    lcd.print("Hello, world!");
    delay(2000);
    lcd.clear();
    return STATUS_OK;
}


// void lcdLoop();


#endif

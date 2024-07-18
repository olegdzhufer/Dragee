#ifndef LCD_THERMO_PID_H
#define LCD_THERMO_PID_H


#include <Arduino.h>
// #include <Wire.h>
#include <LiquidCrystal_I2C.h>


#include "../mDef.h"
#include "Thermostat.h"


class LcdThermoPid : public Thermostat
{
public:
    LiquidCrystal_I2C *lcd;

    LcdThermoPid(){}; // default constructor

    LcdThermoPid(uint8_t pinRelay, uint8_t pinLed, VirtTempSensor *tempSensor, LiquidCrystal_I2C *lcd)
    : Thermostat(pinRelay, pinLed, tempSensor)
    {
        attachLcd(lcd);
    }

    void attachLcd(LiquidCrystal_I2C *lcd)
    {
        this->lcd = lcd;
        lcd->begin(20, 4);
        // lcd->setBacklightPin(xxx, POSITIVE);
        lcd->setBacklight(HIGH);
        lcd->clear();
    }

    void updateLcd()
    {
        if (lcd == NULL)
        {
            return;
        }
  

        lcd->setCursor(8, 0);
        lcd->print(name);

        lcd->setCursor(0, 1);
        lcd->print("Temp: ");
        lcd->print(temp);
        lcd->print(" C");

        lcd->setCursor(0, 2);
        lcd->print("Setpoint: ");
        lcd->print(setpoint);
        lcd->print(" C");

        lcd->setCursor(0, 3);
        lcd->print("State: ");
        lcd->print(state == HIGH ? "ON" : "OFF");
    }




}

#endif // LCD_THERMO_PID_H

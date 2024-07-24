#ifndef LCD_THERMO_PID_H
#define LCD_THERMO_PID_H


#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


#include "../mDef.h"
#include "Thermostat.h"
// #include "IODevices/input/Enc.h"


class LcdThermoPid : public Thermostat
{
public:
    LiquidCrystal_I2C *lcd_p=NULL;

    LcdThermoPid():Thermostat()
    {} // default constructor

    LcdThermoPid(uint8_t pinRelay, uint8_t pinLed, DallasTemperature *tempSensor=NULL, double Kp=DEFAULT_KP, double Ki=DEFAULT_KI, double Kd=DEFAULT_KD,  LiquidCrystal_I2C *lcd=NULL)
    : Thermostat(pinRelay, pinLed,tempSensor, Kp, Ki, Kd)
    {
        if(lcd!=NULL)
        {
            attachLcd(lcd);
        }

        init();
    }

    void attachLcd(LiquidCrystal_I2C *lcd)
    {
        if(lcd==NULL)
        {
            return;
        }
        this->lcd_p = lcd;
        lcd_p->begin(20, 4);
        // lcd->setBacklightPin(xxx, POSITIVE);
        lcd_p->setBacklight(HIGH);
        lcd_p->clear();
    }

    void init()
    {
        if(lcd_p==NULL)
        {
            return;
        }

        lcd_p->init();

        Thermostat::init();
    }

    void updateLcd()
    {
        if (lcd_p == NULL)
        {
            return;
        }
  

        lcd_p->setCursor(8, 0);
        lcd_p->print(name);

        lcd_p->setCursor(0, 1);
        lcd_p->print("Temp: ");
        lcd_p->print(temp);
        lcd_p->print(" C");

        lcd_p->setCursor(0, 2);
        lcd_p->print("Setpoint: ");
        lcd_p->print(setpoint);
        lcd_p->print(" C");

        lcd_p->setCursor(0, 3);
        lcd_p->print("State: ");
        lcd_p->print(state == HIGH ? "ON" : "OFF");
    }

};

#endif // LCD_THERMO_PID_H

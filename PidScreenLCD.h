#ifndef PID_SCREEN_LCD_H
#define PID_SCREEN_LCD_H

#include "Thermostat.h"
#include "Enc.h"
#include <LiquidCrystal_I2C.h>

#define LCD_ADDR 0x3F
#define LCD_ROWS 4
#define LCD_COLS 20

class PidScreenLCD : public Thermostat {
private:
  EncButton *attached_encoder_p = NULL;

public:
  LiquidCrystal_I2C lcd;

  PidScreenLCD(VirtTempSensor *tempSensor, uint8_t pinRel, uint8_t pinLed, uint8_t initState = OFF, bool isNormallyOpen = false)
    : Thermostat(tempSensor, pinRel, pinLed, initState, isNormallyOpen), lcd(LCD_ADDR, LCD_COLS, LCD_ROWS) {}

  void initScreen() {
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Initializing...");
    delay(1000);
    lcd.setCursor(0, 1);
    lcd.print("Thermostat Ready");
    delay(1000);
    lcd.clear();
  }

  void displayHeatingScreen() {
    lcd.setCursor(0, 0);
    lcd.print("Heating Mode");
    lcd.setCursor(0, 1);
    lcd.print("Desired Temp:");
    lcd.print(getDesiredTemperature());
    lcd.setCursor(0, 2);
    lcd.print("Current Temp:");
    lcd.print(attached_tempSensor_p->getTemperature());
  }

  void displayCoolingScreen() {
    lcd.setCursor(0, 0);
    lcd.print("Cooling Mode");
    lcd.setCursor(0, 1);
    lcd.print("Desired Temp:");
    lcd.print(getDesiredTemperature());
    lcd.setCursor(0, 2);
    lcd.print("Current Temp:");
    lcd.print(attached_tempSensor_p->getTemperature());
  }

  void updateScreen() {
    if (isHeatingOn()) {
      displayHeatingScreen();
    } else if (isCoolingOn()) {
      displayCoolingScreen();
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("System Off");
    }
  }

  bool isHeatingOn() {
    return this->getState() && (this->attached_tempSensor_p->getTemperature() <= this->getDesiredTemperature() - this->getLowerTemperatureMargin());
  }

  bool isCoolingOn() {
    return this->getState() && (this->attached_tempSensor_p->getTemperature() >= this->getDesiredTemperature() + this->getUpperTemperatureMargin());
  }

  void controlHeating() {
    Thermostat::controlHeating();
    updateScreen();
  }

  void controlCooling() {
    Thermostat::controlCooling();
    updateScreen();
  }
};

#endif

#include "lcd.h"

int buttonState = 0;
unsigned long debounceDelay = 100; 

struct Button{
  uint16_t pin;
  uint16_t lastDebTime ;
  uint16_t lastButtState ;
};

struct Button btn1 = {5, 0, 0};
struct Button btn2 = {6, 0, 0};
struct Button btn3 = {7, 0, 0};

void buttons_setup(void)
{
    pinMode(BTN1, INPUT);
    pinMode(BTN2, INPUT);
    pinMode(BTN3, INPUT);
}

void controlLEDAndLCD(bool isLedOn, uint16_t led, const char *text) {
    if (isLedOn) {
        digitalWrite(led, LOW);
        lcd.clear();  
        lcd.setCursor(0, 0);
        lcd.print(text);
    } else {
        digitalWrite(led, HIGH);
        lcd.clear();                       
        lcd.setCursor(0, 1);
        lcd.print(text);
    }
}

void loop_buttons(){
int reading = digitalRead(BTN1);  

  if (millis() - btn1.lastDebTime > debounceDelay) {
    btn1.lastDebTime = millis();
    if (reading != btn1.lastButtState) {
      btn1.lastButtState = reading;
      if (reading == HIGH) {
        controlLEDAndLCD(true, LED1, "Green on");
      }
      else {
        bool isLedOn = false;
        controlLEDAndLCD(false, LED1, "Green off");
      }
    }
  }

  int reading_2 = digitalRead(BTN2);  
  
  if (millis() - btn2.lastDebTime > debounceDelay) {
    btn2.lastDebTime = millis();
    if (reading_2 != btn2.lastButtState) {
      btn2.lastButtState = reading_2;
      if (reading_2 == HIGH) {
        controlLEDAndLCD(true, LED2, "Blue on");
      }
      else {
        bool isLedOn = false;
        controlLEDAndLCD(false, LED2, "Blue off");
      }
    }
  }

  int reading_3 = digitalRead(BTN3);  
  
  if (millis() - btn3.lastDebTime > debounceDelay) {
    btn3.lastDebTime = millis();
    if (reading_3 != btn3.lastButtState) {
      btn3.lastButtState = reading_3;
      if (reading_3 == HIGH) {
        controlLEDAndLCD(true, LED3, "Yellow on");
      }
      else {
        bool isLedOn = false;
        controlLEDAndLCD(false, LED3, "Yellow off");
      }
    }
  }
}
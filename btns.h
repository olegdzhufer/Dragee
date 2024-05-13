#include "lcd.h"

int buttonState = 0;
unsigned long debounceDelay = 100; 
bool changeRelayState1 = false;
bool changeRelayState2 = false;
bool changeRelayState3 = false;

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

void singleBtnHandler(struct Button btnX) {
  int reading = digitalRead(btnX.pin);
  if (millis() - btnX.lastDebTime > debounceDelay) {
    btnX.lastDebTime = millis();
    if (reading != btnX.lastButtState) {
      btnX.lastButtState = reading;
      if (btnX.pin == BTN1) {
        controlLEDAndLCD(true, LED1, "Green on");
        changeRelayState1 = true;
      } else if (btnX.pin == BTN2) {
        controlLEDAndLCD(true, LED2, "Blue on");
        changeRelayState2 = true;
      } else if (btnX.pin == BTN3) {
        controlLEDAndLCD(true, LED3, "Yellow on");
        changeRelayState3 = true;
      }
    } else {
      if (btnX.pin == BTN1) {
        controlLEDAndLCD(false, LED1, "Green off");
        changeRelayState1 = false;
      } else if (btnX.pin == BTN2) {
        controlLEDAndLCD(false, LED2, "Blue off");
        changeRelayState2 = false;
      } else if (btnX.pin == BTN3) {
        controlLEDAndLCD(false, LED3, "Yellow off");
        changeRelayState3 = false;
      }
    }
  }
}

void loop_buttons(){

  singleBtnHandler(btn1);
  singleBtnHandler(btn2);
  singleBtnHandler(btn3);

}
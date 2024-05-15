#include "led.h"
#include "relay.h"
#ifndef BTNS_H
#define BTNS_H

int buttonState = 0;
unsigned long debounceDelay = 100;

struct MyButton
{
  uint8_t pin;
  uint8_t lastDebTime;
  uint8_t lastButtState;
};

struct MyButton btn1 = {5, 0, 0};
struct MyButton btn2 = {6, 0, 0};
struct MyButton btn3 = {7, 0, 0};

void buttons_setup(void)
{
  pinMode(BTN1, INPUT);
  pinMode(BTN2, INPUT);
  pinMode(BTN3, INPUT);

  btn1.lastButtState = HIGH;
  btn2.lastButtState = HIGH;
  btn3.lastButtState = HIGH;
}

void controlLEDAndLCD(bool isLedOn, uint16_t led, const char *text)
{
  if (isLedOn)
  {
    digitalWrite(led, LOW);

  }
  else
  {
    digitalWrite(led, HIGH);

  }
}

void singleBtnHandler(struct MyButton btnX)
{
  int reading = digitalRead(btnX.pin);
  if (millis() - btnX.lastDebTime > debounceDelay)
  {
    btnX.lastDebTime = millis();
    if (reading != btnX.lastButtState)
    {
      btnX.lastButtState = reading;
      if (btnX.pin == BTN1)
      {
        controlLEDAndLCD(true, LED1, "Green on");
        changeRelayState1 = true;
      }
      else if (btnX.pin == BTN2)
      {
        controlLEDAndLCD(true, LED2, "Blue on");
        changeRelayState2 = true;
      }
      else if (btnX.pin == BTN3)
      {
        controlLEDAndLCD(true, LED3, "Yellow on");
        changeRelayState3 = true;
      }
    }
    else
    {
      if (btnX.pin == BTN1)
      {
        controlLEDAndLCD(false, LED1, "Green off");
        changeRelayState1 = false;
      }
      else if (btnX.pin == BTN2)
      {
        controlLEDAndLCD(false, LED2, "Blue off");
        changeRelayState2 = false;
      }
      else if (btnX.pin == BTN3)
      {
        controlLEDAndLCD(false, LED3, "Yellow off");
        changeRelayState3 = false;
      }
    }
  }
}

void loop_buttons()
{

  singleBtnHandler(btn1);
  singleBtnHandler(btn2);
  singleBtnHandler(btn3);
}

#endif
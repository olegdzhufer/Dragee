#include "lcd.h"

int buttonState = 0;
int lastButtonState = LOW;  
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 100; 

int lastButtonState2 = LOW;  
unsigned long lastDebounceTime2 = 0; 

int lastButtonState3 = LOW;  
unsigned long lastDebounceTime3 = 0; 

void buttons_setup(void)
{
    pinMode(BTN1, INPUT);
    pinMode(BTN2, INPUT);
    pinMode(BTN3, INPUT);
}
void loop_buttons(){
int reading = digitalRead(BTN1);  

  if (millis() - lastDebounceTime > debounceDelay) {
    lastDebounceTime = millis();
    if (reading != lastButtonState) {
      lastButtonState = reading;
      if (reading == HIGH) {
        digitalWrite(LED1, LOW);
        lcd.clear();  
        lcd.setCursor(0, 0);
        lcd.print("Green");
      } else {
        digitalWrite(LED1, HIGH);
        lcd.clear();                       
        lcd.setCursor(0, 1);
        lcd.print("Green off");  
      }
    }
  }

  int reading_2 = digitalRead(BTN2);  
  
  if (millis() - lastDebounceTime2 > debounceDelay) {
    lastDebounceTime2 = millis();
    if (reading_2 != lastButtonState2) {
      lastButtonState2 = reading_2;
      if (reading_2 == HIGH) {
        digitalWrite(LED2, LOW);
        lcd.clear();  
        lcd.setCursor(0, 0);
        lcd.print("Blue");
      } else {
        digitalWrite(LED2, HIGH);
        lcd.clear();                       
        lcd.setCursor(0, 1);
        lcd.print("Blue off");  
      }
    }
  }

  int reading_3 = digitalRead(BTN3);  
  
  if (millis() - lastDebounceTime2 > debounceDelay) {
    lastDebounceTime3 = millis();
    if (reading_3 != lastButtonState3) {
      lastButtonState3 = reading_3;
      if (reading_3 == HIGH) {
        digitalWrite(LED3, LOW);
        lcd.clear();  
        lcd.setCursor(0, 0);
        lcd.print("Yellow");
      } else {
        digitalWrite(LED3, HIGH);
        lcd.clear();                       
        lcd.setCursor(0, 1);
        lcd.print("Yellow off");  
      }
    }
  }
}
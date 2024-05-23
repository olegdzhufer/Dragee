#ifndef TMR_H
#define TMR_H
#include <Arduino.h>

bool is_timing = false;
unsigned long start_time;
bool flagIsTimerOn = false;

void timer_setup_2() {
  
  int is_timing = 0; 
}

void timer_loop_2(){
if (flagIsTimerOn) {
    if (is_timing == 0) {
      is_timing = 1; 
      start_time = millis(); 
    } else {
      unsigned long elapsed_time = millis() - start_time; 
      int seconds = elapsed_time / 1000; 
      int hours = seconds / 3600; 
      int minutes = (seconds - hours * 3600) / 60; 

    //   lcd.setCursor(0, 0); 
    //   if (hours < 10) lcd.print('0'); 
    //   lcd.print(hours); 
    //   lcd.print(':');
    //   if (minutes < 10) lcd.print('0'); 
    //   lcd.print(minutes); 
    //   lcd.print(':');
    //   if (seconds < 10) lcd.print('0'); 
    //   lcd.print(seconds);
  } 
  }
 else {
    if (is_timing == 1) {
      is_timing = 0; 
  } 
}
}


#endif

#ifndef CNTUPTMR
#define CNTUPTMR

#include <Arduino.h>
#include <Countimer.h>
#include "menu.h"

Countimer countimer;
extern Menu menu;

void onInterval() {
  menu.lcd->setCursor(10, 1);
  menu.lcd->print(countimer.getCurrentTime()); 
}

void timer_setup() {
  countimer.setCounter(0, 0, 0, Countimer::COUNT_UP, NULL); 
  countimer.setInterval(onInterval, 1000); 
}

void timer_loop() {
  countimer.run();
}

#endif

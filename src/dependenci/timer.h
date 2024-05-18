#ifndef TM_H
#define TM_H

#include <Arduino.h>
#include "dallas_sensor.h"
#include "relay.h"

bool should_read_temperature = false;

void temperatureTimerISR()
{
  should_read_temperature = 1;
}

void timer_setup(){

  pinMode(REL1, OUTPUT);

  timer1_attachInterrupt(temperatureTimerISR);
  timer1_enable(TIM_DIV16, TIM_EDGE, TIM_LOOP);
  timer1_write(5000000 * 5);
}

void timer_loop(){}

#endif
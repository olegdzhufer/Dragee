#ifndef TM_H
#define TM_H

#include "dallas_sensor.h"
#include "../relay/relay.h"




void temperatureTimerISR(){
  REG_FLAG |= (1 << 0 ) | (1 << 1);
}



void timer_setup(){
  pinMode(REL1, OUTPUT);
  digitalWrite(V33, HIGH);

  temperatureTicker.attach(1, temperatureTimerISR);
}

void timer_loop(){
  if (REG_FLAG & (1 << 1))
  {
    REG_FLAG &= ~(1 << 1);
    most_recent_temperature_measurement = readTemperatureSensor(temperatureSensor);
  }
}

#endif
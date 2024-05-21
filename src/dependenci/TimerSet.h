#ifndef TM_H
#define TM_H

#include <Arduino.h>
#include "dallas_sensor.h"
#include "menu.h"
#include "relay.h"
#include <Ticker.h>

bool should_read_temperature = false;
float most_recent_temperature_measurement;

void temperatureTimerISR()
{
  bool should_read_temperature = false;
}

// Глобальний об'єкт Ticker
Ticker temperatureTicker;

void timer_setup(){
  pinMode(REL1, OUTPUT);
  // Налаштування таймера з інтервалом 5 секунд
  temperatureTicker.attach(1, temperatureTimerISR);
}

void timer_loop(){
  if (should_read_temperature)
  {
    should_read_temperature = false;
    most_recent_temperature_measurement = readTemperatureSensor(temperatureSensor);
    Serial.print("Temperature: ");
    Serial.println(most_recent_temperature_measurement);
  }
}

#endif
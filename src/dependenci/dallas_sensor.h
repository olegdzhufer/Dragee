#pragma once

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "pins.h"

const float BETA = 3950;

OneWire oneWire(10);
DallasTemperature sensor(&oneWire);

float readNTC()
{ 
  int analogValue = analogRead(NTC_PIN);
  float celsius = 1 / (log(1 / (1023. / analogValue - 1)) / BETA + 1.0 / 298.15) - 273.15;
  return celsius;
}


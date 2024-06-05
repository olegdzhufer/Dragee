#ifndef DLS_H
#define DLS_H

// #include <Arduino.h>
// #include <OneWire.h>
// #include <DallasTemperature.h>
#include "mDef.h"


OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature temperatureSensor(&oneWire);

void dallas_setup(void)
{
  temperatureSensor.begin();
  temperatureSensor.setResolution(12);
  temperatureSensor.requestTemperatures();
}

float readTemperatureSensor(DallasTemperature sensor) 
{
  sensor.requestTemperatures();

  uint32_t timeout = millis();
  while (!sensor.isConversionComplete())
  {
    if (millis() - timeout >= 800) 
    {
      Serial.println("ERROR: timeout or disconnect");
      return -127.0; 
    }
  }

  float temperature = sensor.getTempCByIndex(0);

  Serial.println(temperature); 
  return temperature;
}

#endif
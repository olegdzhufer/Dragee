#ifndef DLS_H
#define DLS_H

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 13


OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature temperatureSensor(&oneWire);
float temperature;



void dallas_setup(void)
{
  Serial.begin(115200);

  temperatureSensor.begin();
  temperatureSensor.setResolution(12);
  temperatureSensor.requestTemperatures();
}

float readTemperatureSensor(DallasTemperature sensor) 
{
  temperatureSensor.requestTemperatures();

  uint32_t timeout = millis();
  while (!temperatureSensor.isConversionComplete())
  {
    if (millis() - timeout >= 800) 
    {
      Serial.println("ERROR: timeout or disconnect");
      return -127.0; 
    }
  }

  temperature = temperatureSensor.getTempCByIndex(0);

  Serial.println(temperature); 
  return temperature;
}


#endif
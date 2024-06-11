#ifndef tempSensor_h
#define tempSensor_h

#include <Arduino.h>
#include "settings.h"

#define VIRT_SENSOR 1

float readSensorComplete()
{
#if(VIRT_SENSOR == 0)
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
#else//VIRT_SENSOR
  float temperature = random(20, 30);
#endif

  Serial.println(temperature);
  return temperature;
}


float readSensor()
{
#if(VIRT_SENSOR == 0)
  sensor.requestTemperatures();
  float temperature = sensor.getTempCByIndex(0);
#else//VIRT_SENSOR
  float temperature = random(20, 30);
#endif
  Serial.println(temperature);
  return temperature;
}

void startSensor()
{
#if(VIRT_SENSOR == 0)

  sensor.begin();
  sensor.setResolution(12);
  sensor.requestTemperatures();
  Temperature = readSensorComplete();
#else//VIRT_SENSOR
  Temperature = readSensor();
#endif
  
  for (int r = 0; r < SensorReadings; r++)
  {
    sensordata[1][r].Temp = Temperature;
  }
  //actuateHeating(OFF);
  // readSensorComplete();
}



#endif
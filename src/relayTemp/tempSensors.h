#ifndef DLS_H
#define DLS_H

#include "mDef.h"

#define DEBUG_TEMP DEBUG_PRINT
#define DEBUGLN_TEMP DEBUG_PRINTLN

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature temperatureSensor(&oneWire);

struct
{
  int id;
  DeviceAddress addr;
} T[4];

uint8_t  deviceCount = 0;


float getTempByID(int id)
{
  for (uint8_t index = 0; index < deviceCount; index++)
  {
    if (T[index].id == id)
    {
      return sensors.getTempC(T[index].addr);
    }
  }
  return -999; //todo err codes 
}


void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) DEBUG_TEMP("0");
    DEBUG_TEMP(deviceAddress[i], HEX);
  }
}
//wait a bit

void dallas_setup(void)
{
  temperatureSensor.begin();
  temperatureSensor.setResolution(12);
   deviceCount = sensors.getDeviceCount();
   DEBUG_TEMP("#devices: ");
   DEBUGLN_TEMP(deviceCount);

  for (uint8_t index = 0; index < deviceCount; index++)
  {
    // go through sensors
    sensors.getAddress(T[index].addr, index);
    T[index].id = sensors.getUserData(T[index].addr);
  }

  for (uint8_t index = 0; index < deviceCount; index++)
  {
    DEBUGLN_TEMP();
    DEBUGLN_TEMP(T[index].id);
    printAddress(T[index].addr);
    DEBUGLN_TEMP();
  }

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

  DEBUGLN_TEMP(temperature); 
  return temperature;
}

#endif
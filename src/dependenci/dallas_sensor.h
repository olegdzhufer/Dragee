#ifndef DLS_H
#define DLS_H

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 13

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature temperatureSensor(&oneWire);

bool isFlagTemp = false;

int count = 0;

void dallas_setup(void)
{
  Serial.begin(9600);

  pinMode(V33, OUTPUT);
  pinMode(Gnd, OUTPUT);

  digitalWrite(V33, HIGH);
  digitalWrite(Gnd, LOW);

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

  float temperature = temperatureSensor.getTempCByIndex(0);

  Serial.println(temperature); 
  return temperature;
}


#endif
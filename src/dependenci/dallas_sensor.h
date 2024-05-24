#ifndef DLS_H
#define DLS_H

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 13
#define GPIO_OUTPUT_PIN_SEL  (1ULL<<V33)

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature temperatureSensor(&oneWire);

bool isFlagTemp = false;

int count = 0;

void dallas_setup(void)
{
  Serial.begin(9600);

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
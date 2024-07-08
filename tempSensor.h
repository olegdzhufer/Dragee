#ifndef tempSensor_h
#define tempSensor_h

#include <Arduino.h>
#include <ThingSpeak.h>

#include "settings.h"

// unsigned long myChannelNumber = 2590643;
// const char* myWriteAPIKey = "22BXOEMQ44JEL405";

// void speak_setup() {
//   ThingSpeak.begin(client);
// }

float readSensorComplete() {
  sensor.requestTemperatures();
  uint32_t timeout = millis();
  while (!sensor.isConversionComplete()) {
    if (millis() - timeout >= 800) {
      Serial.println("ERROR: timeout or disconnect");
      return -127.0;
    }
  }

  float temperature = sensor.getTempCByIndex(0);
  Serial.println(temperature);
  return temperature;
}

float readSensor() {
  sensor.requestTemperatures();
  float temperature = sensor.getTempCByIndex(0);
  Serial.println(temperature);
  return temperature;
}

void startSensor() {

  sensor.begin();
  sensor.setResolution(12);
  sensor.requestTemperatures();
  Temperature = readSensorComplete();
}

#endif 

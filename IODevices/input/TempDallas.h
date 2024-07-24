
#pragma once 

#include <OneWire.h>
#include <DallasTemperature.h>
#include "VirtTempSensor.h"

class TempDallas : public VirtTempSensor
{
public:
    double tempCurrent = 0.0;

  TempDallas(u8 pin) : pin_(pin)
  {
    oneWire_ = new OneWire(pin_);
    dallasSensor_ = new DallasTemperature(oneWire_);

    init();
  }

  void init() override
  {
    dallasSensor_->begin();
    dallasSensor_->getAddress(sensorDeviceAddress_, 0);
    // dallasSensor_->setResolution(sensorDeviceAddress_, 10);
    dallasSensor_->requestTemperaturesByAddress(sensorDeviceAddress_);
  }

  double getTemperature() override
  {
    auto temp = dallasSensor_->getTempC(sensorDeviceAddress_);
    
    if (tempCurrent == DEVICE_DISCONNECTED_C) {
        DEBUG_PRINT("Error: Could not read temperature data");
    }

    tempCurrent = (double)temp;
    dallasSensor_->requestTemperaturesByAddress(sensorDeviceAddress_);
    return tempCurrent;
  }

  bool isParasitePowerMode()
  {
    return dallasSensor_->isParasitePowerMode();
  }

private:
    u8 pin_;                      // The pin connected to the OneWire bus
    OneWire *oneWire_;                   // The OneWire instance
    DallasTemperature* dallasSensor_;
    DeviceAddress sensorDeviceAddress_;
};
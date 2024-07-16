#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include "mDef.h"
#include "Relay.h"
#include "VirtTempSensor.h"
#include "PID.h"

#define MAX_TEMP_LIMIT 30.0
#define MIN_TEMP_LIMIT 5.0

class Thermostat : public Relay, public simpPid {
private:
  VirtTempSensor *attached_tempSensor_p = NULL;

  float desiredTemperature = 19.0;
  float lowerTemperatureMargin = 3.0;
  float upperTemperatureMargin = 3.0;

  bool isPlausibleTemperature(float temperature) const {
    return (MIN_TEMP_LIMIT <= temperature && temperature <= MAX_TEMP_LIMIT);
  }

  bool isPlausibleMargin(float margin) const {
    return (0.0 <= margin && margin <= 3.0);
  }

public:
  Thermostat(VirtTempSensor *tempSensor, uint8_t pinRel, uint8_t pinLed, uint8_t initState = OFF, bool isNormallyOpen = false)
    : Relay(pinRel, pinLed, initState, isNormallyOpen) {
    if (tempSensor != NULL) {
      this->attached_tempSensor_p = tempSensor;
    }
    this->setTemp(&desiredTemperature);
  }

  bool shouldHeatBeOn(float temperature, bool heatCurrentlyOn) {
    if (!isPlausibleTemperature(temperature)) {
      return false;
    }

    this->tempNow(temperature);
    this->tickPIDUp();

    return (temperature <= this->desiredTemperature - this->lowerTemperatureMargin) && !heatCurrentlyOn;
  }

  bool shouldCoolBeOn(float temperature, bool coolCurrentlyOn) {
    if (!isPlausibleTemperature(temperature)) {
      return false;
    }

    this->tempNow(temperature);
    this->tickPIDDown();

    return (temperature >= this->desiredTemperature + this->upperTemperatureMargin) && !coolCurrentlyOn;
  }

  void controlHeating() {
    if (attached_tempSensor_p == NULL) {
      return;
    }

    float currentTemperature = attached_tempSensor_p->getTemperature();
    bool currentRelayState = this->getState();

    if (shouldHeatBeOn(currentTemperature, currentRelayState)) {
      this->turnOn();
      this->PidActivate();
    } else {
      this->turnOff();
      this->PidDeactivate();
    }
  }

  void controlCooling() {
    if (attached_tempSensor_p == NULL) {
      return;
    }

    float currentTemperature = attached_tempSensor_p->getTemperature();
    bool currentRelayState = this->getState();

    if (shouldCoolBeOn(currentTemperature, currentRelayState)) {
      this->turnOn();
      this->PidActivate();
    } else {
      this->turnOff();
      this->PidDeactivate();
    }
  }

  float getDesiredTemperature() const {
    return desiredTemperature;
  }

  int setDesiredTemperature(float temperature) {
    if (isPlausibleTemperature(temperature)) {
      desiredTemperature = temperature;
      return 0;
    }
    return -1;
  }

  float getLowerTemperatureMargin() const {
    return lowerTemperatureMargin;
  }

  int setLowerTemperatureMargin(float margin) {
    if (isPlausibleMargin(margin)) {
      lowerTemperatureMargin = margin;
      return 0;
    }
    return -1;
  }

  float getUpperTemperatureMargin() const {
    return upperTemperatureMargin;
  }

  int setUpperTemperatureMargin(float margin) {
    if (isPlausibleMargin(margin)) {
      upperTemperatureMargin = margin;
      return 0;
    }
    return -1;
  }
};

#endif

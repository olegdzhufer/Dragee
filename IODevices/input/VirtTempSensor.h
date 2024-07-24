
#ifndef VIRT_TEMP_SENSOR_H
#define VIRT_TEMP_SENSOR_H

#include <Arduino.h>

#include "../../mDef.h"

class VirtTempSensor
{
public:

  // VirtTempSensor() = default;

  /**
   * @brief Default destructor
   */
  virtual ~VirtTempSensor() = default;

  virtual void init() = 0;
  
  /**
   * @brief Get the temperature from the sensor
   * @return The temperature in degrees Celsius
   */
  virtual double getTemperature() = 0;
};


#endif

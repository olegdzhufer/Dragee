#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#define MAX_TEMP_LIMIT 30.0
#define MIN_TEMP_LIMIT 5.0

#include <Arduino.h>

#include "mDef.h"
#include "relayModule/Relay.h"
#include "sensorModule/VirtTempSensor.h"

class Thermostat 
{
    /// @brief Holds the state for a Bang-Bang Thermostat with Hysteresis. All values are in degrees Celcius.
    /*
    behavior:
    idea is to avoid switching off and on too frequently (most heating devices will have a protection against this but still..)
    so have an 'interval' of temperatures instead of tracking an exact temperature.

    when heating:
        - if temp > desired + uppermargin: turn off
        - else: keep heating
    when not heating:
        if temp < desired - lowermargin: start heating
        else: keep off

    keep in mind that there will be residual heat dissipation afther the CV
    turns of, this depends on the state of the radiator valves, so unless you known this,
    you cannot really take this into account. Best you could do is register an average, by e.g.
    measuring how much the temperature keeps increasing after you turn the thermostat off on average
    and subtracting this from the upper limit.

    */

private:
    Relay *attached_relay_p = NULL;
    VirtTempSensor *attached_tempSensor_p = NULL;

    float desiredTemperature = 19.0;
    float lowerTemperatureMargin = 3.0;
    float upperTemperatureMargin = 3.0;

    bool isPlausibleTemperature(float temperature)
    {
        return (MIN_TEMP_LIMIT <= temperature && temperature <= MAX_TEMP_LIMIT);
    }

    bool isPlausibleMargin(float margin)
    {
        return (0.0 <= margin && margin <= 3.0);
    }

public:
    Thermostat(Relay *attached_relay_p , VirtTempSensor *attached_tempSensor_p)
    {
        if (attached_relay_p != NULL)
        {
            this->attached_relay_p = attached_relay_p;
        }

        if (attached_tempSensor_p != NULL)
        {
            this->attached_tempSensor_p = attached_tempSensor_p;
        }
    }



    bool shouldHeatBeOn(float temperature, bool heatCurrentlyOn)
    {
        if (!isPlausibleTemperature(temperature))
        {
            return false;
        }

        if (!this->attached_relay_p->getState())
        {
            return false;
        }

        bool shouldOn = (temperature <= this->desiredTemperature - this->lowerTemperatureMargin) && !heatCurrentlyOn;         // should truly start
        shouldOn = shouldOn || ((temperature <= this->desiredTemperature + this->upperTemperatureMargin) && heatCurrentlyOn); // still heating
        return shouldOn;
    }

    float getDesiredTemperature()
    {
        return desiredTemperature;
    }

    int setDesiredTemperature(float temperature)
    {
        if (isPlausibleTemperature(temperature))
        {
            desiredTemperature = temperature;
            return 0;
        }
        return -1;
    }

    float getLowerTemperatureMargin()
    {
        return lowerTemperatureMargin;
    }

    int setLowerTemperatureMargin(float margin)
    {
        if (isPlausibleMargin(margin))
        {
            lowerTemperatureMargin = margin;
            return 0;
        }
        return -1;
    }

    float getUpperTemperatureMargin()
    {
        return upperTemperatureMargin;
    }

    int setUpperTemperatureMargin(float margin)
    {
        if (isPlausibleMargin(margin))
        {
            upperTemperatureMargin = margin;
            return 0;
        }
        return -1;
    }
};

#endif

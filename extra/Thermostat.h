#ifndef THERMOSTAT_H
#define THERMOSTAT_H

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

    But a proxy is to just set the upper margin to 0.
    */

private:
    bool _isActive = false;
    float desiredTemperature = 19.0;
    float lowerTemperatureMargin = 1.0;
    float upperTemperatureMargin = 0.0; 

    bool isPlausibleTemperature(float);
    bool isPlausibleMargin(float);

public:
    bool isActive();
    void activate();
    void deactivate();
    bool shouldHeatBeOn(float,bool);
    float getDesiredTemperature();
    int setDesiredTemperature(float);
    float getLowerTemperatureMargin();
    int setLowerTemperatureMargin(float);
    float getUpperTemperatureMargin();
    int setUpperTemperatureMargin(float);
};

#endif

/*

#include "Thermostat.h"

bool Thermostat::isActive(){
    return _isActive;
}
void Thermostat::activate(){
    _isActive = true;
}

void Thermostat::deactivate(){
    _isActive = false;
}
bool Thermostat::isPlausibleMargin(float margin){
    return (0.0 <= margin && margin <= 3.0);
}
bool Thermostat::isPlausibleTemperature(float temperature)
{
    return (5.0 <= temperature && temperature <= 35.0);
}



bool Thermostat::shouldHeatBeOn(float temperature,bool heatCurrentlyOn)
{
    if (!isPlausibleTemperature(temperature))
    {
        return false;
    }

    if (!this->isActive()){
        return false;
    }

    bool shouldOn = (temperature <= this->desiredTemperature - this->lowerTemperatureMargin) && ! heatCurrentlyOn; // should truly start
    shouldOn = shouldOn || ((temperature <= this->desiredTemperature + this->upperTemperatureMargin) && heatCurrentlyOn); // still heating
    return shouldOn;
}

float Thermostat::getDesiredTemperature()
{
    return desiredTemperature;
}

int Thermostat::setDesiredTemperature(float temperature)
{
    if (isPlausibleTemperature(temperature))
    {
        desiredTemperature = temperature;
        return 0;
    }
    return -1;
}

float Thermostat::getLowerTemperatureMargin(){
    return lowerTemperatureMargin;
}

int Thermostat::setLowerTemperatureMargin(float margin){
    if(isPlausibleMargin(margin)){
        lowerTemperatureMargin = margin;
        return 0;
    }
    return -1;
}
float Thermostat::getUpperTemperatureMargin(){
    return upperTemperatureMargin;
}

int Thermostat::setUpperTemperatureMargin(float margin){
    if(isPlausibleMargin(margin)){
        upperTemperatureMargin = margin;
        return 0;
    }
    return -1;
}

*/
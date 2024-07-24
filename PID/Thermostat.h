#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#define MIN_TEMP_HEAT 30
#define MIN_TEMP_COOL 5

#define MAX_TEMP_HEAT 60
#define MAX_TEMP_COOL 30

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "../mDef.h"
#include "../IODevices/input/VirtTempSensor.h"
#include "../IODevices/output/Relay.h"
#include "Pid.h"

#define DEFAULT_KP 1.5
#define DEFAULT_KI 0.3
#define DEFAULT_KD 1.5

class Thermostat : public Relay//, private PID
{
public:
    PID pid;
    double temp = 0.0;//double
    double output;
    double setpoint;

    Thermostat(){}; // default constructor

    Thermostat(uint8_t pinRelay, uint8_t pinLed, DallasTemperature *tempSensor=NULL, double Kp=DEFAULT_KP, double Ki=DEFAULT_KI, double Kd=DEFAULT_KD, PID_DIRECTION controllerDirection=DIRECT, ERROR_PROPORTIONAL POn=P_ON_E)
    : Relay(pinRelay, pinLed , OFF, false)
    {
        attachSensor(tempSensor); 
        pid.init(&temp, &output, &setpoint, Kp, Ki, Kd, POn, controllerDirection);
        init();
    }


    void init()
    {
        pid.setMode(AUTOMATIC);
    }


    void attachSensor(DallasTemperature *tempSensor=NULL)
    {
        if (tempSensor != NULL)
        {
            this->attached_tempSensor_p = tempSensor;
        }
    }

    void begin()
    {
        if (this->attached_tempSensor_p != NULL)
        {
            this->attached_tempSensor_p->begin();

            this->attached_tempSensor_p->requestTemperatures();

            this->temp = this->attached_tempSensor_p->getTempCByIndex(0);//todo multiple sensors

            if (temp == DEVICE_DISCONNECTED_C)
            {
                DEBUG_PRINT("Error: Could not read temperature from sensor");
            }
            else{
            
                DEBUG_PRINT("Thermostat sensor is inited");            
            }
        }
        
        if(!getIsInited())
        {
            DEBUG_PRINT("Thermostat relay is not inited");
            return;
        }

        pid.begin();
    }

// private:
    
    DallasTemperature *attached_tempSensor_p = NULL;

 
};

#endif

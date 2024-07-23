#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#define MIN_TEMP_HEAT 30
#define MIN_TEMP_COOL 5

#define MAX_TEMP_HEAT 60
#define MAX_TEMP_COOL 30

#include <Arduino.h>

#include "../mDef.h"
#include "../IODevices/input/VirtTempSensor.h"
#include "../IODevices/output/Relay.h"
#include "Pid.h"


class Thermostat : public Relay//, private PID
{
public:
    PID pid;
    double temp = 0.0;//double
    double output;
    double setpoint;

    Thermostat(){}; // default constructor

    

    Thermostat(uint8_t pinRelay, uint8_t pinLed, double Kp, double Ki, double Kd, DallasTemperature *tempSensor=NULL, PID_DIRECTION controllerDirection=DIRECT)
    : Relay(pinRelay, pinLed , OFF, false)
    {
        attachSensor(tempSensor); 

        pid.setTunings(Kp, Ki, Kd, P_ON_E);
        init(controllerDirection);
    }


    void init(PID_DIRECTION controllerDirection=DIRECT)
    {
       
        // if(RELAY::getIsInited() == false)
        // {
        //     Relay::init(pinRelay, OFF, false);
        // }
        
        pid.setMode(AUTOMATIC);
    }


    void attachSensor(DallasTemperature *tempSensor=NULL)
    {
        if (tempSensor != NULL)
        {
            this->attached_tempSensor_p = tempSensor;
            // this->attached_tempSensor_p->init();//todo
            // this->temp = this->attached_tempSensor_p->getTemperature();//requestTemperatures
        }
    }

    void begin()
    {
        // if (this->attached_tempSensor_p != NULL)
        // {
        //     this->attached_tempSensor_p->begin();
        // }
        
        if(getIsInited())
        {
            return;
        }

        pid.begin();
    
    }

// private:
    
    DallasTemperature *attached_tempSensor_p = NULL;

 
};

#endif

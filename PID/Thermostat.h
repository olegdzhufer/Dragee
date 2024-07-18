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


class Thermostat : public Relay, private PID
{
public:
    PID pid;
    double temp = 0.0;//double
    double output;
    double setpoint


    Thermostat(){}; // default constructor

    Thermostat(uint8_t pinRelay, uint8_t pinLed, VirtTempSensor *tempSensor=NULL)
    : Relay(pinRelay, pinLed , OFF, false)
    {
        attachSensor(tempSensor); 
    }

    Thermostat(uint8_t pinRelay, uint8_t pinLed, VirtTempSensor *tempSensor, double Kp, double Ki, double Kd, ERROR_PROPORTIONAL POn, PID_DIRECTION controllerDirection)
    : Thermostat::Thermostat(pinRelay, pinLed , tempSensor)
    {
        init(pinRelay, Kp, Ki, Kd, POn, controllerDirection);
    }


    void init(uint8_t pinRelay, double Kp, double Ki, double Kd, VirtTempSensor *tempSensor=NULL, ERROR_PROPORTIONAL POn=P_ON_E, PID_DIRECTION controllerDirection=DIRECT)
    {
        if (this->attached_tempSensor_p == NULL)
        {
            attachSensor(tempSensor);
        }
        else{
            temp = (double) (this->attached_tempSensor_p->getTemperature());
        }

        if(getIsInited() == false)
        {
            Relay::init(pinRelay, OFF, false);
        }
        

        pid.setTunings(Kp, Ki, Kd, POn);
        myPID.SetMode(AUTOMATIC);
    }

    void attachSensor(VirtTempSensor *tempSensor)
    {
        if (tempSensor != NULL)
        {
            this->attached_tempSensor_p = tempSensor;
            this->attached_tempSensor_p->init();
            this->temp = this->attached_tempSensor_p->getTemperature();
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
    
    VirtTempSensor *attached_tempSensor_p = NULL;

 
};

#endif

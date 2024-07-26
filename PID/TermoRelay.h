#ifndef TERMO_RELAY_H
#define TERMO_RELAY_H

#include <Arduino.h>

#include "../mDef.h"

#include "Pid.h"
#include "../IODevices/input/SwitchButton.h"
#include "../IODevices/output/Relay.h"
#include "../IODevices/input/VirtTempSensor.h"

VirtTempSensor *globalSensorInstance = nullptr;

class TermoRelay//: protected PID
{
public:
    friend class Menu;
   float tempCur=0.0;
   float tempSet=0.0;

public:
    TermoRelay(Relay *relay, SwitchButton *button);

    TermoRelay(Relay *relay, SwitchButton *button , VirtTempSensor *sensor) 
    : TermoRelay::TermoRelay(relay, button)
    {   
        if((globalSensorInstance == nullptr) && (sensor != nullptr))
        {
            globalSensorInstance = sensor;
            sensor_p= globalSensorInstance;
        }else if((globalSensorInstance != nullptr) && (sensor == nullptr))
        {
            sensor_p = globalSensorInstance;
        }else if((globalSensorInstance == nullptr) && (sensor == nullptr))
        {
            DEBUG_PRINT("ERROR: TermoRelay: Sensor is NULL");
            return;
        }
    }

    
    ~TermoRelay()
    {
        // delete TermoRelay::sensor_p;
        // TermoRelay::sensor_p = nullptr;
    }



    bool tick()
    {
        btnTick();
        sensorTick();
        bool changed = relayTick();
        return changed;
    }
    

    void btnTick(){
        if (button_p!= nullptr)
        {
            if (firstInstance == this)
            {
                this->button_p->tick();
            }
            else
            {
                if (firstInstance->relay_p->getState() == ON)
                {
                    this->button_p->tick();
                }
            }
        }
    }


    bool relayTick()
    {
        if (relay_p!= nullptr)
        {
            if (firstInstance == this)
            {
                return this->relay_p->tick();
            }else{
                if (firstInstance->relay_p->getState() == ON)
                {
                    return this->relay_p->tick();
                }
            }
        }
        return false;
    }


    void sensorTick(){
        if (sensor_p!= nullptr)
        {
            if (millis() - sensorTimer > this->updateInterval) 
            {
                tempCur = getTemperature();
            }
        }
    }


    double getTemperature()
    {
        tempCur = sensor_p->getTemperature();
        this->sensorTimer = millis();

        DEBUG_PRINT("Temperature timer updated: %ld", sensorTimer);

        return tempCur;
    }

    double getTempCur()
    {
        return tempCur;
    }

    double getTempSet()
    {
        return tempSet;
    }


    // Static method to get the last instance
    static TermoRelay *getLastInstance()
    {
        return lastInstance;
    }


    // Method to get the next instance
    TermoRelay *getNextInstance() const
    {
        return nextInstance_p;
    }


    // Method to get the first instance
    TermoRelay *getFirstInstance() const
    {
        return firstInstance;
    }


private:
    Relay *relay_p = nullptr;
    SwitchButton *button_p = nullptr;
    VirtTempSensor* sensor_p= nullptr;    
    uint32_t updateInterval = 5000;
    uint32_t sensorTimer = 0;

    TermoRelay *nextInstance_p = nullptr;
    TermoRelay *firstInstance = nullptr;
    static TermoRelay *lastInstance;
};

TermoRelay *globalFirstInstance = nullptr;
TermoRelay *TermoRelay::lastInstance = nullptr;

TermoRelay::TermoRelay(Relay *relay, SwitchButton *button) 
            : relay_p(relay), button_p(button)  
{
    if (relay_p == nullptr || button_p == nullptr)
    {
        DEBUG_PRINT("ERROR: TermoRelay: One of the parameters is NULL");
        return;
    }

    if (globalFirstInstance == nullptr)
    {
        globalFirstInstance = this;
    }
    firstInstance = globalFirstInstance;

    if (lastInstance != nullptr)
    {
        nextInstance_p = lastInstance;
    }
    lastInstance = this;

    this->button_p->attachRelay(relay_p);
    this->tempCur = getTemperature();
    }

void termoRelayTick()
{
    TermoRelay *last = TermoRelay::getLastInstance();

    TermoRelay *current = last;
    while (current != nullptr)
    {
        current->tick();
        current = current->getNextInstance();
    }
}

#endif // TERMO_RELAY_H

/*

template <typename T>
class TermoRelay {
public:
    TermoRelay();
    ~TermoRelay();

    void setValue(T value);
    T getValue() const;

private:
    T value;
};

template <typename T>
TermoRelay<T>::TermoRelay() : value(T()) {}

template <typename T>
TermoRelay<T>::~TermoRelay() {}

template <typename T>
void TermoRelay<T>::setValue(T value) {
    this->value = value;
}

template <typename T>
T TermoRelay<T>::getValue() const {
    return value;
}
*/
#ifndef TERMO_RELAY_H
#define TERMO_RELAY_H

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "../mDef.h"

#include "../IODevices/input/SwitchButton.h"
#include "../IODevices/output/Relay.h"
// #include "../IODevices/input/VirtTempSensor.h"

class TermoRelay
{
public:
    float tempC;

public:
    TermoRelay(Relay *relay, SwitchButton *button);//, DallasTemperature *sensor);

    ~TermoRelay()
    {
        // delete TermoRelay::sensor_p;
    // TermoRelay::sensor_p = nullptr;
    }

    void tick()
    {
        btnTick();

        sensorTick();

        relayTick();
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

    void relayTick(){
        if (relay_p!= nullptr)
        {
            if (firstInstance == this)
            {
                this->relay_p->tick();
            }else{
                if (firstInstance->relay_p->getState() == ON)
                {
                    this->relay_p->tick();
                }
            }
            
            
        }
    }

    void sensorTick(){
        if (sensor_p!= nullptr)
        {
            if (millis() - TermoRelay::sensorTimer > this->updateInterval) //this->sensorTimer
            {
                getTemperature();
            }
        }
    }

    float getTemperature()
    {
        TermoRelay::sensor_p->requestTemperatures();
        tempC = TermoRelay::sensor_p->getTempCByIndex(0); // todo add for multiple sensors

        // this->sensorTimer = millis();

        TermoRelay::sensorTimer = millis();
        DEBUG_PRINT("Temperature timer updated: %ld", TermoRelay::sensorTimer);

        return tempC;
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

    static uint32_t sensorTimer;
    static DallasTemperature* sensor_p;
private:
    Relay *relay_p = nullptr;
    SwitchButton *button_p = nullptr;
    // VirtTempSensor* sensor;
    // DallasTemperature *sensor_p = nullptr;
    // DeviceAddress sensorAddress;

    
    uint32_t updateInterval = 5000;
    // uint32_t sensorTimer = 0;

    TermoRelay *nextInstance_p = nullptr;
    TermoRelay *firstInstance = nullptr;
    static TermoRelay *lastInstance;
    
};

TermoRelay *globalFirstInstance = nullptr;
TermoRelay *TermoRelay::lastInstance = nullptr;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature* TermoRelay::sensor_p = new DallasTemperature(&oneWire);

// DallasTemperature* TermoRelay::sensor_p = nullptr;
uint32_t TermoRelay::sensorTimer = 0;

TermoRelay::TermoRelay(Relay *relay, SwitchButton *button)//, DallasTemperature *sensor)
{
    if (relay == nullptr || button == nullptr || TermoRelay::sensor_p == nullptr)
    {
        DEBUG_PRINT("ERROR: TermoRelay: One of the parameters is NULL");
        return;
    }

    if (globalFirstInstance == nullptr)
    {
        globalFirstInstance = this;
    }
    firstInstance = globalFirstInstance;

    this->relay_p = relay;
    this->button_p = button;
    // this->sensor_p = sensor;

    this->button_p->attachRelay(relay);
    
    TermoRelay::sensor_p->begin();
    // sensor->setResolution(12);
    getTemperature();

    if (lastInstance != nullptr)
    {
        nextInstance_p = lastInstance;
    }
    lastInstance = this;
}

void termoRelayTick() //(TermoRelay* instance)
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
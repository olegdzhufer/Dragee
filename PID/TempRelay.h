#ifndef TEMPRELAY_H
#define TEMPRELAY_H


#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "../IODevices/input/SwitchButton.h"
#include "../IODevices/output/Relay.h"
// #include "../IODevices/input/VirtTempSensor.h"

class TempRelay {
public:
    TempRelay();
    ~TempRelay();



private:
    Relay* relay;
    SwitchButton* button;
    // VirtTempSensor* sensor;
    DallasTemperature* sensor;
    // DeviceAddress sensorAddress;
};

#endif // TEMPRELAY_H

/*

template <typename T>
class TempRelay {
public:
    TempRelay();
    ~TempRelay();

    void setValue(T value);
    T getValue() const;

private:
    T value;
};

template <typename T>
TempRelay<T>::TempRelay() : value(T()) {}

template <typename T>
TempRelay<T>::~TempRelay() {}

template <typename T>
void TempRelay<T>::setValue(T value) {
    this->value = value;
}

template <typename T>
T TempRelay<T>::getValue() const {
    return value;
}
*/
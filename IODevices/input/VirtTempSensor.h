
#ifndef VIRT_TEMP_SENSOR_H
#define VIRT_TEMP_SENSOR_H

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "../../../mDef.h"


class VirtTempSensor {
public:
    // float tempCurrent=0.0;
    virtual float getTemperature() const = 0;
    virtual void init() = 0;
    // virtual int32_t getTemp() const = 0;

    // virtual ~VirtTempSensor() {};
	// virtual float getTempC();
	// virtual float getTempF();
};


class DallasTempSensor : public VirtTempSensor{

    private:
        static u8 totalId=0;
        u8 idWire;
        OneWire oneWire(ONE_WIRE_BUS);
        DallasTemperature sensor(&oneWire);
        uint32_t responseTimeout = 1000;
    public:
        DallasTempSensor()
        {
            init();
        }

        void init(){
             this->sensor.begin();
//   sensor.setResolution(12);
//   Temperature = readSensorComplete();
            idWire = totalId;
            totalId++;
        }


        float getTemperature()
        {
            this->sensor.requestTemperatures();
            uint32_t timeout = millis();
            while (!sensor.isConversionComplete()) {
                if (millis() - timeout >= this->responseTimeout) {
                    DEBUG_PRINT("ERROR: Dallas timeout response or disconnected");
                    STATUS_t sts = DALLAS_NO_CALLBACK;
                    return (float)sts;
                }
                float temperature = sensor.getTempCByIndex(this->idWire);
                return temperature;
            }
        }
}








#endif 

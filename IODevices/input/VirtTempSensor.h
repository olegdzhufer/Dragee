
#ifndef VIRT_TEMP_SENSOR_H
#define VIRT_TEMP_SENSOR_H

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
// #include "./../mDef.h"


// OneWire oneWire(ONE_WIRE_BUS);

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

/*
class DallasTempSensor : public VirtTempSensor{

    private:
        OneWire *_wire;
        DallasTemperature *sensor;
        uint8_t idWire=1;
        
        uint32_t responseTimeout = 1000;
    public:
        DallasTempSensor(OneWire *w) :  _wire{w}
        {
            this->sensor = new DallasTemperature(this->_wire);
            init();
        }
        

        void init()
        {
             this->sensor->begin();
//   sensor.setResolution(12);
//   Temperature = readSensorComplete();
        }


        float getTemperature()
        {
            this->sensor->requestTemperatures();
            uint32_t timeout = millis();
            while (!(sensor->isConversionComplete())) {
                if (millis() - timeout >= this->responseTimeout) {
                    // DEBUG_PRINT("ERROR: Dallas timeout response or disconnected");
                    // STATUS_t sts = DALLAS_NO_CALLBACK;
                    return -127.0;
                }
                float temperature = sensor->getTempCByIndex(this->idWire);
                return temperature;
            }
        }
};




uint8_t findDevices(int pin)
{
  OneWire ow(pin);

  uint8_t address[8];
  uint8_t count = 0;


  if (ow.search(address))
  {
    Serial.print("\nuint8_t pin");
    Serial.print(pin, DEC);
    Serial.println("[][8] = {");
    do {
      count++;
      Serial.println("  {");
      for (uint8_t i = 0; i < 8; i++)
      {
        Serial.print("0x");
        if (address[i] < 0x10) Serial.print("0");
        Serial.print(address[i], HEX);
        if (i < 7) Serial.print(", ");
      }
      Serial.println("  },");
    } while (ow.search(address));

    Serial.println("};");
    Serial.print("// nr devices found: ");
    Serial.println(count);
  }

  return count;
}
*/






#endif 

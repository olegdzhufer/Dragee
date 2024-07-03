#ifndef tempSensor_h
#define tempSensor_h

#include <Arduino.h>
#include "menu.h"
#include "settings.h"

  class TermSensor{
    private:
      DallasTemperature* sensor;
      uint8_t period;
      float temp;
      uint16_t TimerBuffer = 0;
      void (*callbackOnChange)() = NULL;

      uint8_t flags = 0;

    
    public:

    //##################### Constructor #######################################

      TermSensor(){
        this->sensor = NULL;
        this->period = 1000;
      }

      TermSensor(DallasTemperature* sensor, uint8_t time){
        if(sensor){
          this->sensor = sensor;
        }
        this->period = time;
      }

    //###################### FLAG #############################################

    uint8_t TempAvaible(){
        if(this->flags & 1){
          this->tempRead();
          return 0x01;
        }else{
          return 0x00;
        }

        
    }

    //###################### GETERS ###########################################
      float getTemp(){
        return this->temp;
      }
    //###################### SETTER ###########################################
      void setSensor(DallasTemperature* sensor){
        if(sensor){
          this->sensor = sensor;
        }
      }
      void setPeriodDouble(double time){
        if(time != 0){
          this->period = time* 1000;
        }
      }
      void setPeriodFloat(float time){
        if(time != 0){
          this->period = time* 1000;
        }
      }
      void setPeriodInt(uint8_t time){
        if(time != 0){
          this->period = time;
        }
      }
      void setCallback(void (*callback)()){
        this->callbackOnChange = callback;
      }

    //###################### Work Part ########################################



      void readData(){
        this->sensor->requestTemperatures();
        this->temp = this->readSensorData();
      }

      void tickSensor(){
          if(millis() - this->TimerBuffer >= this->period){
            this->TimerBuffer = millis();
            this->readData();
            this->Callback();
          }
      }
      //#######################################################################

      private:
      //################# Flag Function #######################################

      void tempReady(){
        this->flags |= 1;
      }
      void tempRead(){
        this->flags &= ~(1);
      }



      //################# Servise Part ########################################

      float readSensorData(){
        uint32_t timeout = millis();
        while (!(this->sensor->isConversionComplete()))
        {
          if (millis() - timeout >= 100)
          {
            Serial.println("ERROR: timeout or disconnect");
            return -127.0;
          }
        }
        this->tempReady();
        return  this->sensor->getTempCByIndex(0);
      }

      void Callback(){
        if(this->callbackOnChange != NULL){
          this->callbackOnChange();
        }
      }

      //#######################################################################


  };

  #ifdef TEMP_S




    #define VIRT_SENSOR 0

    float readSensorComplete()
    {
      #ifdef DEBUG_FUNC
        Serial.println(__func__);
      #endif
    #if(VIRT_SENSOR == 0)
      sensor.requestTemperatures();
      uint32_t timeout = millis();
      while (!sensor.isConversionComplete())
      {
        if (millis() - timeout >= 800)
        {
          Serial.println("ERROR: timeout or disconnect");
          return -127.0;
        }
      }

      float temperature = sensor.getTempCByIndex(0);
    #else//VIRT_SENSOR
      float temperature = random(20, 30);
    #endif

      Serial.println(temperature);

      if(menu.curr == Heat){
        TempCurH->val->setfloat(TempCurH->val, temperature);
        menu.lineUpdate(&menu, TempCurH);
      }else if(menu.curr == Cooling){
        TempCurC->val->setfloat(TempCurC->val, temperature);
        menu.lineUpdate(&menu, TempCurC);
      }else if( menu.curr == FAN){
        TempCurF->val->setfloat(TempCurF->val, temperature);
        menu.lineUpdate(&menu, TempCurF);
      }
      


      return temperature;
    }


    float readSensor()
    {
        #ifdef DEBUG_FUNC
          Serial.println(__func__);
        #endif
    #if(VIRT_SENSOR == 0)
      sensor.requestTemperatures();
      float temperature = sensor.getTempCByIndex(0);
    #else//VIRT_SENSOR
      float temperature = random(20, 30);
    #endif
      Serial.println(temperature);
      return temperature;
    }

    void startSensor()
    {

        #ifdef DEBUG_FUNC
          Serial.println(__func__);
        #endif
    #if(VIRT_SENSOR == 0)

      sensor.begin();
      sensor.setResolution(12);
      sensor.requestTemperatures();
      Temperature = readSensorComplete();
    #else//VIRT_SENSOR
      Temperature = readSensor();
    #endif
      
      for (int r = 0; r < SensorReadings; r++)
      {
        sensordata[1][r].Temp = Temperature;
      }
      if(menu.curr == Heat){
        TempCurH->val->setfloat(TempCurH->val, Temperature);
        menu.lineUpdate(&menu, TempCurH);
      }else if(menu.curr == Cooling){
        TempCurC->val->setfloat(TempCurC->val, Temperature);
        FLAG_LCD = true;
      }else if( menu.curr == FAN){
        TempCurF->val->setfloat(TempCurF->val, Temperature);
        FLAG_LCD = true;
      }
      //actuateHeating(OFF);
      // readSensorComplete();
    }
  #endif

#endif
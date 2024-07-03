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

      void begin(){
        this->sensor->begin();
        this->sensor->setResolution(12);
        this->sensor->requestTemperatures();
      }

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

    TermSensor tempSensor(&sensor, 250);

    void callBackTemp(){

      Temperature = tempSensor.getTemp();

      if(menu.curr == Heat){
        TempCurH->val->setfloat(TempCurH->val, Temperature);
        menu.lineUpdate(&menu, TempCurH);
      }else if(menu.curr == Cooling){
        TempCurC->val->setfloat(TempCurC->val, Temperature);
        menu.lineUpdate(&menu, TempCurC);
      }else if( menu.curr == FAN){
        TempCurF->val->setfloat(TempCurF->val, Temperature);
        menu.lineUpdate(&menu, TempCurF);
      }
    }




    float readSensorComplete()
    {
      return Temperature;
    }


    float readSensor(){
      return Temperature;
    }



    void startSensor(){
      tempSensor.begin();
      tempSensor.setCallback(callBackTemp);
    }

    void sensorTempLoop(){
      tempSensor.tickSensor();
    }
  #endif

#endif
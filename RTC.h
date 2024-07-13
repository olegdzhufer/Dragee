#ifndef RTC_H
#define RTC_H

#include <microDS3231.h>
#include "settings.h"

class MyRTControler{
  private:
    MicroDS3231* myRTC;
    DateTime now;
    bool begStatus = false;
    uint8_t sec = 0;
    void (*callbackOnTime)() = NULL;


  public:
    //###################### Construct ######################
    MyRTControler(){} 

    MyRTControler(MicroDS3231* myRTC){
      if(myRTC){
        this->myRTC = myRTC;
      }
    }
    //###################### Setter #########################

    void setRTC(MicroDS3231* myRTC){
      this->myRTC = myRTC;
    }
    void setCallBack(void (*callback)()){
      this->callbackOnTime = callback;
    }

    //###################### Getter #########################

    String getTimeStd(){

      return this->timeComponer(this->now.hour, this->now.minute, this->now.second);
    }

    char* getTime(){
      char* time ;
      String timeStd = this->timeComponer(this->now.hour, this->now.minute, this->now.second);

      time = this->convectorStrToChar(timeStd);
    }

    //###################### Work Part ######################

    void begin(){
      if(!this->begStatus){
        if(this->myRTC->begin()){
          this->begStatus = true;
        }
      }
    }

    void timeWrite(){
      this->now = myRTC->getTime();
    }

    void tickRTC(){
      this->begin();
      if(this->begStatus){
        this->timeWrite();
        if(sec != now.second){
          this->sec = now.second;
          this->callCallback();
        }
      }
    }

    private:
    //###################### Tech Part ######################
    String timeComponer(uint8_t hours, uint8_t minute, uint8_t second){
      String curr;
      if(hours < 10){
        curr += "0";
      }
      curr += String(hours);
      curr += ":";
      if(minute < 10){
        curr += "0";
      }
      curr += String(minute);
      curr += ":";
      if(second < 10){
        curr += "0";
      }
      curr += String(second);


      return curr;
    }

    char* convectorStrToChar(String text) {
        uint8_t lenText = text.length();

        char* res = (char*)malloc(lenText * sizeof(char) + 1);

        for (uint8_t iter = 0; iter < lenText; iter++) {
          res[iter] = text[iter];
        }
        res[lenText] = '\0';

        return res;
      }

      void callCallback(){
        if(this->callbackOnTime != NULL){
          this->callbackOnTime();
        }
      }

};


#endif
#ifndef PID_H
#define PID_H
#include "settings.h"
#include "relay.h"

class simpPid{

  private:
    bool work = false;
    float* target;
    float temp;
    Relay* relay;
    

  public:
    simpPid(){}

    simpPid(float* target, Relay* relay){
      this->target = target;
      this->relay = relay;
    }
    void PidActivate(){
      this->work = true;
    }
    void PidDeactivate(){
      this->work = true;
    }

    void tempNow(float temp){
      this->temp = temp;
    }

    void tickPIDUp(){
      if((this->target && *(this->target) - 1,5 >= temp || this->temp >= 58 ) && (this->relay && this->work) ){
        this->relay->relayOff();
      }else if(this->work && this->relay){
        this->relay->relayOn();
      }
    }
    void tickPIDDown(){
      if((this->target && *(this->target) <= temp || this->temp <= 1 ) && (this->relay && this->work) ){
        this->relay->relayOff();
      }else if(this->work && this->relay){
        this->relay->relayOn();
      }
    }


    void setTemp(float* target){
      this->target = target;
    }

};

simpPid heatPid(&TargetTemp, &relayHeat);
simpPid coolPid(&FrostTemp, &relayCool);

void setupPID(){

}

void loopPID(){
  heatPid.tickPIDUp();
  coolPid.tickPIDDown();
}


  

    


#endif
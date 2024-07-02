#ifndef PID_H
#define PID_H
#include "settings.h"
#include "relay.h"

class simpPid{

  private:
    bool work = false;
    float* target;
    float temp;
    uint8_t pin;
    uint8_t onTime = 0;
    uint32_t timerBuffer;


    float integral = 0 , prevEr = 0;

  public:
    float kp, ki, kd, dt;

  public:
    simpPid(){}

    simpPid(float* target, uint8_t pin){
      this->target = target;
      this->pin = pin;
    }
    void PidActivate(){
      this->work = true;
    }
    void PidDeactivate(){
      this->work = false;
    }

    void tempNow(float temp){
      this->temp = temp;
    }

    void tickPIDUp(){
      if(this->work){

      }
    }
    
    void tickPIDDown(){
      if(this->work){
        
      }
    }


    void setTemp(float* target){
      this->target = target;
    }

    void offPid(){
      this->work = false;
      digitalWrite(this->pin, LOW);
      this->integral = 0;
      this->prevEr = 0;
    }

    void switchPidMode(){
      this->work = !work;
    }

    private:
      int8_t PIDControler(){
        float err = *(this->target) - this->temp;
        this->integral += err * this->dt;
        float D = (err - this->prevEr) / this->dt;
        this->prevEr = err;
        return (err * this->kp + this->integral* this->ki + D * this->kd);
      }

      void timeCounter(){
        if(this->timerBuffer + this->dt*1000 < millis()){
          this->timerBuffer = millis();
          int8_t val = this->PIDControler();
          if(val <= 0){
            this->onTime = 0;
          }else{

            val = ((val - (val % 1.28)) / 1.28) * 10;
            this->onTime = (this->dt * val);
          }

        }
      }

      

};

simpPid heatPid(&TargetTemp, HEAT_PIN);
simpPid coolPid(&FrostTemp,  COOL_PIN);

void setupPID(){

}

void loopPID(){




  if(Heat->footer != NULL){
    heatPid.PidActivate();
    heatPid.tempNow(Temperature);
    heatPid.tickPIDUp();
  }
  else{
    heatPid.PidDeactivate();
    relayHeat.relayOff();
  }


  if(Cooling->footer != NULL){
    coolPid.PidActivate();
  coolPid.tempNow(Temperature);
  coolPid.tickPIDDown();
  }
  else{
    coolPid.PidDeactivate();
    relayCool.relayOff();
  }
  
}


class PIDInterface{

  private:
    simpPid* pid;

  public:
    PIDInterface(){

    }


};



  

    


#endif
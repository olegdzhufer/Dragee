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
    uint32_t timerBufSec;


    float integral = 0 , prevEr = 0;
    float kp, ki, kd, dt;

  public:

    //#############SETTER##########################
    void setKp(float kp){
      this->kp = kp;
    }
    void setKi(float ki){
      this->ki = ki;
    }
    void setKd(float kd){
      this->kd = kd;
    }
    void setDt(float dt){
      this->dt = dt;
    }

    //#############GETERS##########################

    float getKp(){
      return this->kp;
    }

    float getKi(){
      return this->ki;
    }

    float getKd(){
      return this->kd;
    }

    float getDt(){
      return this->dt;
    }

    // ####### ++, -- Func #################################
    //############# PLUS ########
    void addToKp(){
      this->kp ++;
    }
    void addToKi(){
      this->ki ++;
    }
    void addToKd(){
      this->kd ++;
    }
    void addToDt(){
      this->dt ++;
    }
    //############# MINUS #######
    void SubtractFromKp(){
      this->kp --;
    }
    void SubtractFromKi(){
      this->ki --;
    }
    void SubtractFromKd(){
      this->kd --;
    }
    void SubtractFromDt(){
      this->dt --;
    }

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
        this->timeCounter();
        if(this->onTime && this->timerBufSec){
          this->timerBufSec = millis();
        }

        if(this->timerBufSec && this->timerBufSec + this->onTime < millis() ){
          digitalWrite(this->pin, HIGH);
        }else{
          digitalWrite(this->pin, LOW);
          this->onTime = 0;
          this->timerBufSec = 0;
        }

      }
    }
    
    void tickPIDDown(){
      if(this->work){
        this->timeCounter();
        if(this->onTime && this->timerBufSec){
          this->timerBufSec = millis();
        }

        if(this->timerBufSec && this->timerBufSec + this->onTime < millis() ){
          digitalWrite(this->pin, LOW);
        }else{
          digitalWrite(this->pin, HIGH);
          this->onTime = 0;
          this->timerBufSec = 0;
        }

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
            val = ((val - fmod(val, 1.27)) / 1.27) * 10;
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
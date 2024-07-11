#include "HardwareSerial.h"
#ifndef CNTUPTMR
#define CNTUPTMR

#include <Arduino.h>
#include <Countimer.h>
#include "menu.h"

#ifdef TIMER_S

void callBackToTimer();

class TimerCount{
  
  private:
    Countimer countimer;
    Screen* screen;
    Line* footer;
    String text;
    bool status = false;



  public:

    String name;

    TimerCount(){
      countimer.setCounter(24, 60, 60, Countimer::COUNT_UP, NULL);
      countimer.setInterval(callBackToTimer , 1000);
      Serial.println((unsigned long)&countimer, HEX);
      
    }

    TimerCount(Screen* screen, Line* footer){

      if(screen){
        this->screen = screen;
      }
      if(footer){
        this->footer = footer;
      }
      countimer.setCounter(24, 60, 60, Countimer::COUNT_UP, NULL);
      countimer.setInterval(callBackToTimer , 1000);
      Serial.println((unsigned long)&countimer, HEX);
    }
    

    bool swichTimerMode(){
      this->status =!(this->status);
      if(status){
        this->onTimer();
        return status;
      }
      this->offTimer();
      return status;

    }

    void offTimer(){
      this->status = false;
      this->stopTimer();
    }

    void onTimer(){
      this->status = true;
      this->startTimer();
    }

    void timerTick(){
      this->countimer.run();
    }

    void setScreen(Screen* screen){
      if(screen){
        this->screen = screen;
      }
    }

    void setFooter(Line* line){
      if(line){
        this->footer = line;
      }
    }
    
    void timerChange(){
      if(this->status){
        this->text = this->countimer.getCurrentTime();
        char* textChar = this->convectorStrToChar();
        this->footer->val->setChar(this->footer->val, textChar);
        if(this->name){
          Serial.print(this->name);
        }
        Serial.println(this->footer->val->var.mode);
        menu.footerUpdate(&menu, this->footer->val);
        free(textChar);
      }
    }

    ~TimerCount(){
      if(footer){
        this->footer->destruct(this->footer);
      }
    }

    private:
      char* convectorStrToChar() {
        uint8_t lenText = this->text.length();

        char* res = (char*)malloc(lenText * sizeof(char) + 1);

        for (uint8_t iter = 0; iter < lenText; iter++) {
          res[iter] = text[iter];
        }
        res[lenText] = '\0';

        return res;
      }

      void startTimer() {
        this->countimer.start();

        if(this->screen && this->footer){
          this->screen->footer = this->footer;
        }
      }

      void stopTimer() {
        this->countimer.stop();
        if(this->screen){
          this->screen->footer = NULL;
        }
          
      }

   
};

TimerCount timerHeat(Heat, NULL);
TimerCount timerCool(Cooling, NULL);

void callBackToTimer(){
  timerHeat.timerChange();
  timerCool.timerChange();
}


void timer_setup() {
  timerHeat.name = "Heat :";
  timerCool.name = "Cool :";

  timerHeat.setScreen(Heat);
  timerCool.setScreen(Cooling);

  timerHeat.setFooter(footerHeat);
  timerCool.setFooter(footerCool);


}

void timer_loop() {
  timerHeat.timerTick();
  timerCool.timerTick();
}

#endif

#endif

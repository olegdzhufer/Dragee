#include "dallas_sensor.h"

volatile int interruptCounter;
int totalInterruptCounter;
hw_timer_t * timer = NULL;

portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR onTimer() {      //Defining Inerrupt function with IRAM_ATTR for faster access
 portENTER_CRITICAL_ISR(&timerMux);
 interruptCounter++;
 portEXIT_CRITICAL_ISR(&timerMux);
 isFlagTemp = true;
}

void timer_setup() {
 Serial.begin(115200);
 
 timer = timerBegin(0, 80, true);           	// timer 0, prescalar: 80, UP counting
 timerAttachInterrupt(timer, &onTimer, true); 	// Attach interrupt
 timerAlarmWrite(timer, 1000000, true);  		// Match value= 1000000 for 1 sec. delay.
 timerAlarmEnable(timer); 
}

void timer_loop() {
   if (interruptCounter > 0) {
 
   portENTER_CRITICAL(&timerMux);
   interruptCounter--;
   portEXIT_CRITICAL(&timerMux);
 
   totalInterruptCounter++;         	//counting total interrupt

   isFlagTemp = !isFlagTemp;  				//toggle logic
   
 }
}

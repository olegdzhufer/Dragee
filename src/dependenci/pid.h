#ifndef PID_H
#define PID_H
#include <dependenci/dallas_sensor.h>
#include <dependenci/pins.h>
#include <dependenci/relay.h>

const double P = temperature*1.980354879594423; 
const double I = temperature*0.000002574461343; 
const double D = temperature*99.017743979721166;
bool changeTemp = false;
const float bias = 0;
const float pidDelay = 100;
const float acceptableError = .05;

float error = 0; 
float oldError = 0; 
float integral = 0; 
float derivative = 0; 
float correction = 0; 
bool err; 

float desiredTemp = -1;


void pid_setup() {
  attachInterrupt(digitalPinToInterrupt(5), set, FALLING); 
  attachInterrupt(digitalPinToInterrupt(6), set, FALLING); 
}

void pidControl() {
  if (desiredTemp != -1) {
    if (desiredTemp != temperature) {
      err = true; 
    }
    if (err == true) {
      error = desiredTemp - temperature;

      integral = integral + (error * pidDelay);

      derivative = (error - oldError) / pidDelay;

      correction = P * error + I * integral + D * derivative + bias;

      oldError = error;

      if (error < -acceptableError) {
        if (correction < 0) {
          correction = correction * -1; 
        }

        if (correction > 255) {
          correction = 255;
        }

        turnOnCooling();
        turnOffHeating();

        if (desiredTemp < temperature) {
          temperature = temperature - (correction * 0.005) + 0.005; 
        }
        
        if (desiredTemp > temperature) {
          temperature = temperature + (correction * 0.005) - 0.005; 
        }
    }

    if (error > acceptableError) {
        if (correction > 255) {
          correction = 255;
        }

        turnOnHeating();
        turnOffCooling();

        if (desiredTemp < temperature) {
          temperature = temperature - (correction * 0.005) + 0.005; 
        }

        if (desiredTemp > temperature) {
          temperature = temperature + (correction * 0.005) - 0.005; 
        }
      }
        if (error <= acceptableError && error >= -acceptableError) {
        turnOffCooling(); 
        turnOffHeating();
        err = false;
      }

      delay(pidDelay);
    }
  }
}

void set() {
  changeTemp = true;
}

void serialIO() {
  while(changeTemp == true) {
    desiredTemp =// "сума від поворотів енкодера в конкретну сторону"; 
    changeTemp = false; 
  }
}

void pid_loop(){
    serialIO();
    pidControl();
}

#endif
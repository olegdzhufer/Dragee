#ifndef PID_H
#define PID_H

#include "../mDef.h"
#define DEFAULT_SAMPLE_TIME 100

typedef enum PID_DIRECTION
{
  DIRECT,
  REVERSE
}PID_DIRECTION;

typedef enum ERROR_PROPORTIONAL
{
  P_ON_M,
  P_ON_E
}ERROR_PROPORTIONAL;

typedef enum PID_MODE
{
  MANUAL,
  AUTOMATIC
}PID_MODE;

typedef struct
{
  double Kp;
  double Ki;
  double Kd;
}PID_TUNINGS;

class PID
{
public:
 friend class Thermostat;
  PID(){}

  PID(double *input, double *output, double *setpoint,
      double Kp, double Ki, double Kd, 
      ERROR_PROPORTIONAL POn=P_ON_E, PID_DIRECTION controllerDirection=DIRECT)
  {
    if (input == NULL || output == NULL || setpoint == NULL)
    {
      DEBUG_PRINT("ERROR: Null pointer in PID init");
      return;
    }
    
    init(input, output, setpoint, Kp, Ki, Kd, POn, controllerDirection);
  }


  PID(double *input, double *output, double *setpoint,
      double Kp, double Ki, double Kd, 
      PID_DIRECTION controllerDirection)
      : PID::PID(input, output, setpoint, Kp, Ki, Kd, P_ON_E, controllerDirection)
  {}



  void init(double *input, double *output, double *setpoint,
      double Kp, double Ki, double Kd, ERROR_PROPORTIONAL POn=P_ON_E, PID_DIRECTION controllerDirection=DIRECT)
  {
    if (input == NULL || output == NULL || setpoint == NULL)
    {
      return;
    }
    
    attachValues(input, output, setpoint);

    autoMode = MANUAL;

    setOutputLimits(0, UINT_LEAST8_MAX);

    sampleTime = DEFAULT_SAMPLE_TIME; // default Controller Sample Time is 0.1 seconds

    setControllerDirection(controllerDirection);
    setTunings(Kp, Ki, Kd, POn);

    lastTime = millis() - sampleTime;

  }

  void begin()
  {
    if (myOutput)
    {
      outputSum = *myOutput;
    }

    if (myInput)
    {
      lastInput = *myInput;
    }
 
    if (outputSum > outMax)
    {
      outputSum = outMax;
    }
    else if (outputSum < outMin)
    {
      outputSum = outMin;
    }
  }

  void attachInput(double *input)
  {
    if (input == NULL)
    {
      return;
    }
    myInput = input;
  }

  void attachOutput(double *output)
  {
    if (output == NULL)
    {
      return;
    }
    
    myOutput = output;
  }

  void attachSetpoint(double *setpoint)
  {
    if (setpoint == NULL)
    {
      return;
    }
    mySetpoint = setpoint;
  }

  void attachValues(double *input, double *output, double *setpoint)
  {
    attachInput(input);
    attachOutput(output);
    attachSetpoint(setpoint);
  }


  void setMode(PID_MODE Mode)
  {
    bool newAuto = (bool)(Mode == AUTOMATIC);
    if (newAuto && (autoMode==MANUAL))
    { /*we just went from manual to auto*/
      this->begin();
    }
    autoMode = AUTOMATIC;
  }

  // bool needsCompute(); //  Returns true if calling Compute() will actually  perform a PID computation.
  
  bool compute()
  {
    if (autoMode==MANUAL){
      return false;
    }

    uint32_t now = millis();
    uint32_t timeChange = (now - lastTime);
    if (timeChange >= sampleTime)
    {
      //Compute all the working error variables
      if(myInput == NULL || mySetpoint == NULL){
        return false;
      }

      double input = *myInput;
      double error = *mySetpoint - input;
      double dInput = (input - lastInput);
      outputSum += (ki * error);

      /*Add Proportional on Measurement, if P_ON_M is specified*/
      if (pOnE==P_ON_M){
        outputSum -= kp * dInput;
      }

      if (outputSum > outMax)
      {
        outputSum = outMax;
      }
      else if (outputSum < outMin)
      {
        outputSum = outMin;
      }

      /*Add Proportional on Error, if P_ON_E is specified*/
      double output;
      if (pOnE==P_ON_E){
        output = kp * error;
      }else{
        output = 0;
      }

      /*Compute Rest of PID Output*/
      output += outputSum - kd * dInput;

      if (output > outMax){
        output = outMax;
      }
      else if (output < outMin){
        output = outMin;
      }
      *myOutput = output;

      /*Remember some variables for next time*/
      lastInput = input;
      lastTime = now;
      return true;
    }
    else
      return false;
  }

  void setOutputLimits(double min, double max)
  {
    if (min >= max)
      return;

    outMin = min;
    outMax = max;

    if (autoMode==AUTOMATIC)
    {
      if (*myOutput > outMax)
      {
        *myOutput = outMax;
      }
      else if (*myOutput < outMin)
      {
        *myOutput = outMin;
      }
      
      outputSum = (outputSum > outMax) ? outMax : outputSum;
      outputSum = (outputSum < outMin) ? outMin : outputSum;
    }
  }


  void setTunings(double Kp, double Ki, double Kd, ERROR_PROPORTIONAL POn=P_ON_E)
  {
    if (Kp < 0 || Ki < 0 || Kd < 0)
    {
      return;
    }

    pOn = (int)POn;
    pOnE = POn;

    dispKp = Kp;
    dispKi = Ki;
    dispKd = Kd;

    double SampleTimeInSec = ((double)sampleTime) / 1000;
    kp = Kp;
    ki = Ki * SampleTimeInSec;
    kd = Kd / SampleTimeInSec;

    if (controllerDirection == REVERSE)
    {
      kp = (0 - kp);
      ki = (0 - ki);
      kd = (0 - kd);
    }
  }

  void setControllerDirection(PID_DIRECTION Direction)
  {
    if ((autoMode==AUTOMATIC) && (Direction != controllerDirection))
    {
      kp = (0 - kp);
      ki = (0 - ki);
      kd = (0 - kd);
    }
    controllerDirection = Direction;
  }

  void setSampleTime(int NewSampleTime)
  {
    if (NewSampleTime > 0)
    {
      double ratio = (double)NewSampleTime / (double)sampleTime;
      ki *= ratio;
      kd /= ratio;
      sampleTime = (uint32_t)NewSampleTime;
    }
  }




  double getKp() { return dispKp; } // These functions query the pid for interal values.
  double getKi() { return dispKi; } //  they were created mainly for the pid front-end,
  double getKd() { return dispKd; } // where it's important to know what is actually
  
  int getModeNum() { return (int)autoMode ? AUTOMATIC : MANUAL; }
  PID_MODE getMode() { return autoMode; }

  int getDirectionNum() { return (int)controllerDirection; }
  PID_DIRECTION getDirection() { return controllerDirection; }

  

private:
  double dispKp; //  we'll hold on to the tuning parameters in user-entered
  double dispKi; //   format for display purposes
  double dispKd;

  double kp; // (P)roportional Tuning Parameter
  double ki; // (I)ntegral Tuning Parameter
  double kd; // (D)erivative Tuning Parameter

  PID_DIRECTION controllerDirection;
  int pOn;
  ERROR_PROPORTIONAL pOnE;  

  double *myInput;    // Pointers to the Input, Output, and Setpoint variables
  double *myOutput;   //   This creates a hard link between the variables and the
  double *mySetpoint; //   PID, freeing the user from having to constantly tell us
                      //   what these values are.  with pointers we'll just know.

  uint32_t lastTime;
  double outputSum, lastInput;

  uint32_t sampleTime;
  double outMin, outMax;
  PID_MODE autoMode;
  
   
};
#endif
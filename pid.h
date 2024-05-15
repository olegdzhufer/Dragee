/*#include "encoder.h"
#include "pins.h"
#include "dallas_sensor.h"

#ifndef PID_H
#define PID_H

float PID_output(float process, float setpoint, float Prop, float Integ, float deriv, int Interval, bool action);
float TR_C_filterFunction(float timeConstant, float processGain,float blockIn, float intervalTime);

pid_setup(){
  pinMode(NTC_PIN, OUTPUT);
}

pid_loop(){
  float heaterSetting;
  float contOutNorm;

  heaterSetting = SetpointGenerator();
  contOutNorm  = PID_output(C_Variable/500, heaterSetting/500,propBand, integralTime, derivativeTime, 2000, controlAction);

  if (controlAction==true)
     {
     analogWrite(10,255*contOutNorm);// converts PID controller output toa PWM value 
     }
      else if(controlAction==false)
     {
     analogWrite(11,255*contOutNorm);// converts PID controller output toa PWM value 
     }
  if (Manual==true )
    {
    potA1=analogRead(A1);
    if (controlAction==true)
     {
     analogWrite(10,((float)potA1/1023*255*2.90));// 2.90 added to compensate for 1.66 volts at top of pot
     } else if (controlAction==false)
      {
     analogWrite(11,((float)potA1/1023*255));
    }
 }
}

void Potentiometer(bool action)// fan setting 0 to 100%
{
  float speedPercent;
  potA3=analogRead(A3);

  speedPercent=(float)potA3*100/1023;
  if (action==false)
  {
   analogWrite(10,speedPercent/100*255); 
  } else if (action==true)
  {
   analogWrite(11,speedPercent/100*255);  
  }
  
  lcd.setCursor(17, 3); 
  lcd.print("   ");
  lcd.setCursor(17, 3); 
  lcd.print ((int) (speedPercent));
}

float SetpointGenerator()
{
  float setTemp;
  
  long encoderValue = myEncoder.read();

  setTemp = map(encoderValue, 0, 1023, 0, 110); 
    

    lcd.setCursor( 9, 3); 
    lcd.print("    ");
    lcd.setCursor(9 , 3); 
    lcd.print((int)setTemp); 
    return setTemp;
}
float PID_output(float process, float setpoint, float Prop, float Integ, float deriv, int Interval, bool action)
{
float Er;
static float Olderror, Cont;
static int Limiter_Switch;
static float Integral;
float derivative;
float proportional;
float deltaT;
float filteredDerivative;
deltaT=float(Interval)/1000;
Limiter_Switch = 1;

if (action==false)
  {
  Er = (process-setpoint);
  } else if (action==true)
  {
  Er=(setpoint-process);
  }

if ((Cont >= 1 && Er > 0) || (Cont <= 0 && Er < 0) || (Integ >= 3600)) 
        Limiter_Switch = 0;
else
        Limiter_Switch = 1;     
  
Integral = Integral + 100 / Prop / Integ * Er *deltaT * Limiter_Switch;
derivative = 100 / Prop * deriv * (Er - Olderror) / deltaT;
filteredDerivative=DerivativefilterFunction(5, 1.0,derivative, 1000);
proportional = 100 / Prop * Er;
        
Cont = proportional + Integral + filteredDerivative;
Olderror = Er;

if (Cont > 1) 
    Cont = 1;

if (Cont < 0) 
    Cont = 0;
lcd.setCursor(9 , 2); 
lcd.print("    ");    
lcd.setCursor(9 , 2); 
lcd.print((int)(Cont*100.0));

lcd.setCursor(15 , 0); 
lcd.print("     ");    
lcd.setCursor(15 , 0);
lcd.print((int)(proportional*100.0));
lcd.setCursor(15 , 1); 
lcd.print("    ");    
lcd.setCursor(15 , 1); 
lcd.print((int)(Integral*100.0));

lcd.setCursor(15 , 2); 
lcd.print("     ");    
lcd.setCursor(15 , 2); 
lcd.print((int)(filteredDerivative*100.0));

return  Cont;
}


#endif    
  

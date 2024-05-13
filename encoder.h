
#include <Arduino.h>
#include <EncButton.h>
#include <PIDController.h>
#include "dallas_sensor.h"

EncButton en(CLK, DT, SW);
PIDController pid;

int set_temperature = 1;
int clockPin; 
int clockPinState;
float debounce = 0;
int encoder_btn_count = 0;
float temperature_value_c = 0.0;


void encoder_setup(){
  pinMode(mosfet_pin, OUTPUT); 
  pid.begin();          
  pid.setpoint(150);  
  pid.tune(__Kp, __Ki,__Kd);  
  pid.limit(0, 255);    
  en.setEncType(EB_STEP4_LOW);
  en.setBtnLevel(HIGH);
}

void set_temp()
{
  if (encoder_btn_count == 2) 
  { 
    lcd.clear();
    lcd.setCursor(16, 0); 
    lcd.print("Set Temp."); 
    lcd.setCursor(45, 25);
    lcd.print(set_temperature);
  }
}

void read_encoder() 
{
  if (en.leftH()) {
    Serial.println("left"); 
    set_temperature = set_temperature - 3;  
    if (set_temperature < 1 )set_temperature = 1; 
#ifdef __DEBUG__
    Serial.println("left"); 
#endif
  }
  if(en.rightH()){
    Serial.println("right");
    set_temperature = set_temperature + 3;
    if (set_temperature > 150 ) set_temperature = 150;
#ifdef __DEBUG__
    Serial.println("right"); 
#endif
  }

if (en.press())  
  {
    if ( millis() - debounce > 80) { 
      encoder_btn_count++; 
      if (encoder_btn_count > 2) encoder_btn_count = 1;
#ifdef __DEBUG__
      Serial.println(encoder_btn_count);
#endif
    }
    debounce = millis(); 
  }
}

void encoder_loop(){
   
  en.tick();
  read_encoder(); 
  set_temp(); 
  if (encoder_btn_count == 1) 
  { 
    temperature_value_c = readNTC(); 
    int output = pid.compute(temperature_value_c);   
    analogWrite(mosfet_pin, output);           
    pid.setpoint(set_temperature); 
    lcd.clear(); 
    lcd.setCursor(16, 0); 
    lcd.print("Cur Temp."); 
    lcd.setCursor(16, 4);
    lcd.print(temperature_value_c); 
    lcd.display(); 
#ifdef __DEBUG__
    Serial.print(temperature_value_c); 
    Serial.print("   "); 
    Serial.println(output); 
#endif
    delay(200); 
  }
}
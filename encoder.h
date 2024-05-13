
#include <Arduino.h>
#include <EncButton.h>
#include <PIDController.h>
#include "dallas_sensor.h"
EncButton en(CLK, DT, SW);
int set_temperature = 1;
int clockPin; 
int clockPinState;
float debounce = 0;
int encoder_btn_count = 0;
float temperature_value_c = 0.0;

PIDController pid;


void encoder_setup(){
  pinMode(mosfet_pin, OUTPUT); // MOSFET output PIN
  pid.begin();          // initialize the PID instance
  pid.setpoint(150);    // The "goal" the PID controller tries to "reach"
  pid.tune(__Kp, __Ki,__Kd);    // Tune the PID, arguments: kP, kI, kD
  pid.limit(0, 255);    // Limit the PID output between 0 and 255, this is important to get rid of integral windup!
  en.setEncType(EB_STEP4_LOW);
  en.setBtnLevel(HIGH);
}

void set_temp()
{
  if (encoder_btn_count == 2) // check if the button is pressed twice and its in temperature set mode.
  { 
    lcd.clear(); // clear the display
    lcd.setCursor(16, 0); // set the diplay cursor
    lcd.print("Set Temp."); // Print Set Temp. on the display
    lcd.setCursor(45, 25); // set the cursor
    lcd.print(set_temperature);// print the set temperature value on the display
  }
}

void read_encoder() // In this function we read the encoder data and increment the counter if its rotaing clockwise and decrement the counter if its rotating counter clockwis
{
  if (en.leftH()) {
    Serial.println("left"); // if this condition is true then the encoder is rotaing counter clockwise and we decremetn the counter
    set_temperature = set_temperature - 3;  // decrmetn the counter.
    if (set_temperature < 1 )set_temperature = 1; // if the counter value is less than 1 the set it back to 1
#ifdef __DEBUG__
    Serial.println("left"); // print the set temperature value on the serial monitor window
#endif
  }
  if(en.rightH()){
    Serial.println("right");
    set_temperature = set_temperature + 3;
    if (set_temperature > 150 ) set_temperature = 150;
#ifdef __DEBUG__
    Serial.println("right"); // print the set temperature value on the serial monitor window
#endif
  }

if (en.press())   //If we detect LOW signal, button is pressed
  {
    if ( millis() - debounce > 80) { //debounce delay
      encoder_btn_count++; // Increment the values 
      if (encoder_btn_count > 2) encoder_btn_count = 1;
#ifdef __DEBUG__
      Serial.println(encoder_btn_count);
#endif
    }
    debounce = millis(); // update the time variable
  }
}


void encoder_loop(){
    en.tick();

  en.tick();
  read_encoder(); //Call The Read Encoder Function
  set_temp(); // Call the Set Temperature Function
  if (encoder_btn_count == 1) // check if the button is pressed and its in Free Running Mode -- in this mode the arduino continiously updates the screen and adjusts the PWM output according to the temperature.
  { 
    temperature_value_c = readNTC(); // Read the Temperature using the readCelsius methode from MAX6675 Library.
    int output = pid.compute(temperature_value_c);    // Let the PID compute the value, returns the optimal output
    analogWrite(mosfet_pin, output);           // Write the output to the output pin
    pid.setpoint(set_temperature); // Use the setpoint methode of the PID library to
    lcd.clear(); // Clear the display
    lcd.setCursor(16, 0); // Set the Display Cursor
    lcd.print("Cur Temp."); //Print to the Display
    lcd.setCursor(16, 4);// Set the Display Cursor
    lcd.print(temperature_value_c); // Print the Temperature value to the display in celcius
    lcd.display(); // Update the Display
#ifdef __DEBUG__
    Serial.print(temperature_value_c); // Print the Temperature value in *C on serial monitor
    Serial.print("   "); // Print an Empty Space
    Serial.println(output); // Print the Calculate Output value in the serial monitor.
#endif
    delay(200); 
  }
}
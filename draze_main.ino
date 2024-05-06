

#include "lcd.h"
#include "pins.h"
#include "btns.h"
#include "dallas_sensor.h"
#include "led.h"
#include "encoder.h"


//Encoder enc(CLK, DT, SW);

void setup(void) {
  buttons_setup();
  lcd_setup();
}

void loop(void) {
   loop_buttons();
   lcd_loop();
}


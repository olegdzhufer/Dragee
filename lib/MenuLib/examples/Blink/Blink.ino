/*
  LiquidCrystal Library - Blink

 Demonstrates the use of a 16x2 LCD display. The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "hello, world!" to the LCD and makes the
 cursor block blink.

 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K or 100K potentiometer:
   * ends to +5V and ground
   * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi
 modified 2 Feb 2024
 by Vladislav Vanyuk

 This example code is in the public domain.

 https://docs.arduino.cc/learn/electronics/lcd-displays#blink-example
 https://github.com/arduino-libraries/LiquidCrystal

*/

// include the library code:
#include <LiquidCrystal_Base.h>

#define LCD_TYPE 1 // 0 - LCD, 1 - LCD_I2C

LiquidCrystal_Base *lcd;

#if (LCD_TYPE == 0)
// initialize the library by associating any needed LCD interface pin
// with the Arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd_normal(rs, en, d4, d5, d6, d7);
#elif (LCD_TYPE == 1)
LiquidCrystal_I2C lcd_i2c(0x27, 16, 2); //(0x27, 20, 4)
#else
error("Please select the LCD type")
#endif

void setup() {
#if (LCD_TYPE == 0)
  lcd = &lcd_normal;
#elif (LCD_TYPE == 1)
  lcd = &lcd_i2c;
#endif

  // set up the LCD's number of columns and rows:
  lcd->begin(16, 2);
  // Print a message to the LCD
  lcd->print("Cursor Blinking");
}

void loop() {
  // Turn off the blinking cursor:
  lcd->noBlink();
  delay(3000);
  // Turn on the blinking cursor:
  lcd->blink();
  delay(3000);
}
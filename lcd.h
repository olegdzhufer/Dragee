
#ifndef LCD_H
#define LCD_H

#include <LiquidCrystal_I2C.h> 

#define LCD_ADDR 0x27
#define LCD_ROWS 4
#define LCD_COLS 20

LiquidCrystal_I2C lcd(0x3F,20,4);

void lcd_setup(){
  lcd.init();         
 
}

void lcd_loop(){}


#endif //
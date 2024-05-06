
#ifndef LCD_H
#define LCD_H

#include <LiquidCrystal_I2C.h> 

#define LCD_ADDR 0x27
#define LCD_ROWS 4
#define LCD_COLS 20

LiquidCrystal_I2C lcd2(,20,4);

void lcd_setup(){
  lcd.init();         
  lcd.backlight();  

  lcd2.init();         
  lcd2.backlight();  
  lcd2.setCursor(0,0);            
  lcd2.print("Hello");
  lcd2.setCursor(0,1);            
  lcd2.print("world");
  lcd2.setCursor(0,2);  
  lcd2.print("world2");
  lcd2.setCursor(0,3);  
  lcd2.print("world3");

  sensor.begin();
  lcd.clear();
}

void lcd_loop(){}


#endif //
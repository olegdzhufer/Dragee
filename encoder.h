#include <EncButton>

Encoder enc1(CLK, DT, SW);

void encoder_setup(){
    enc1.setType(TYPE2);
}

void encoder_loop(){
    enc1.tick();
  
  if (enc1.isTurn()) {     // если был совершён поворот (индикатор поворота в любую сторону)
    lcd.clear();
    lcd.setBacklight(true);
    lcd.setCursor(2, 0);
    lcd.println("Turn");
  }
  
  if (enc1.right()) {   // если был поворот
    lcd.setCursor(10, 1);
    lcd.println("Right"); 
  }          
  if (enc1.left()) {
    lcd.setCursor(4, 1);
    lcd.println("Left");
  }
  if (enc1.rightH()) Serial.println("Right holded"); // если было удержание + поворот
  if (enc1.leftH()) Serial.println("Left holded");
  
  if (enc1.Press()) Serial.println("Press");         // нажатие на кнопку (+ дебаунс)
  if (enc1.Click()) Serial.println("Click");         // отпускание кнопки (+ дебаунс)
  //if (enc1.isRelease()) Serial.println("Release");     // то же самое, что isClick
  
  if (enc1.Holded()) Serial.println("Holded");       // если была удержана и энк не поворачивался
  //if (enc1.isHold()) Serial.println("Hold");
}
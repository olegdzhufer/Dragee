// After running the simulator, click on the DS18B20 chip to change the temperature
// Chip by bonnyr, source code: https://github.com/bonnyr/wokwi-ds1820-custom-chip/

#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h> 
//#include <Encoder.h>

#define LED1 8
#define LED2 9
#define LED3 11

#define BTN1 5
#define BTN2 6
#define BTN3 7

#define CLK 2                        
#define DT 3                       
#define SW 4                          

#define NTC_PIN A0

//Encoder enc(CLK, DT, SW);

OneWire oneWire(10);
DallasTemperature sensor(&oneWire);

LiquidCrystal_I2C lcd(0x27,16,2);

LiquidCrystal_I2C lcd2(0x3F,20,4);

const float BETA = 3950;
float readNTC()
{
  int analogValue = analogRead(NTC_PIN);
  float celsius = 1 / (log(1 / (1023. / analogValue - 1)) / BETA + 1.0 / 298.15) - 273.15;
  return celsius;
}

void setup(void) {

  pinMode(BTN1, INPUT);
  pinMode(LED1, OUTPUT);
  
  pinMode(BTN2, INPUT);
  pinMode(LED2, OUTPUT);

  pinMode(BTN3, INPUT);
  pinMode(LED3, OUTPUT);
  //enc.setType(TYPE2)

  Serial.begin(115200);
  delay(2);

  lcd.init();         
  lcd.backlight();  
  lcd.setCursor(0,0);            
  lcd.print("Hello");
  lcd.setCursor(0,1);            
  lcd.print("world");

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

int buttonState = 0;
int lastButtonState = LOW;  
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 100; 

int lastButtonState2 = LOW;  
unsigned long lastDebounceTime2 = 0; 

int lastButtonState3 = LOW;  
unsigned long lastDebounceTime3 = 0; 

void loop(void) {
  int reading = digitalRead(BTN1);  

  if (millis() - lastDebounceTime > debounceDelay) {
    lastDebounceTime = millis();
    if (reading != lastButtonState) {
      lastButtonState = reading;
      if (reading == HIGH) {
        digitalWrite(LED1, LOW);
        lcd.clear();  
        lcd.setCursor(0, 0);
        lcd.print("Green");
      } else {
        digitalWrite(LED1, HIGH);
        lcd.clear();                       
        lcd.setCursor(0, 1);
        lcd.print("Green off");  
      }
    }
  }

  int reading_2 = digitalRead(BTN2);  
  
  if (millis() - lastDebounceTime2 > debounceDelay) {
    lastDebounceTime2 = millis();
    if (reading_2 != lastButtonState2) {
      lastButtonState2 = reading_2;
      if (reading_2 == HIGH) {
        digitalWrite(LED2, LOW);
        lcd.clear();  
        lcd.setCursor(0, 0);
        lcd.print("Blue");
      } else {
        digitalWrite(LED2, HIGH);
        lcd.clear();                       
        lcd.setCursor(0, 1);
        lcd.print("Blue off");  
      }
    }
  }

  int reading_3 = digitalRead(BTN3);  
  
  if (millis() - lastDebounceTime2 > debounceDelay) {
    lastDebounceTime3 = millis();
    if (reading_3 != lastButtonState3) {
      lastButtonState3 = reading_3;
      if (reading_3 == HIGH) {
        digitalWrite(LED3, LOW);
        lcd.clear();  
        lcd.setCursor(0, 0);
        lcd.print("Yellow");
      } else {
        digitalWrite(LED3, HIGH);
        lcd.clear();                       
        lcd.setCursor(0, 1);
        lcd.print("Yellow off");  
      }
    }
  }




   
// unsigned long currentMillis = millis(); // Поточний час у мілісекундах

  //if (currentMillis - previousMillis >= interval) {
    // Збереження часу останнього виконання коду
    //previousMillis = currentMillis;

    // Ваш код, який виконується кожну секунду
    //float ntc = readNTC();
    //sensor.requestTemperatures();
    //float ds = sensor.getTempCByIndex(0);
    //lcd.setCursor(0,0);            
    //lcd.print(ntc);
    //lcd.setCursor(0,1);            
    //lcd.print(ds);

    // Виведення стану кнопки BTN1
    Serial.println(digitalRead(BTN1));
}
//}

//void ON()
//{
//  lcd.display();
//}
   
//void OFF()
//{
//lcd.nodisplay();
//}

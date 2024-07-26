#include "mDef.h"
#include "lcdMenu/Menu.h"
#include "IODevices/input/EncButton.h"
#include "IODevices/input/SwitchButton.h"
#include "IODevices/input/TempDallas.h"
#include "PID/TermoRelay.h"

Relay relayFan (FAN_PIN,  LED_PIN1); 
Relay relayHeat (HEAT_PIN,  LED_PIN2); 
Relay relayCool (COOL_PIN,  LED_PIN3); 


SwitchButton btnSwitch(BTN1_PIN, SWITCH_TYPE);
SwitchButton btn2     (BTN2_PIN, BTN_TYPE);
SwitchButton btn3     (BTN3_PIN, BTN_TYPE);

TempDallas tempSensor(TEMP_PIN);

TermoRelay tempRel1(&relayFan, &btnSwitch, &tempSensor);
TermoRelay tempRel2(&relayHeat, &btn2);
TermoRelay tempRel3(&relayCool, &btn3);


LiquidCrystal_I2C lcd_main(LCD_ADDR_DEFAULT, LCD_COLS, LCD_ROWS); 
MenuEncButton encBtn(DT, SW, CLK, INPUT, INPUT, HIGH);
Menu menu(&lcd_main, &encBtn);


void IRAM_ATTR isrEnc()
{
    encBtn.tickRaw();
}

void IRAM_ATTR isrBtnRaw() 
{
  btnSwitch.tickRaw();
  btn2.tickRaw();
  btn3.tickRaw();
  
 // btn1.pressISR();
  //btn2.pressISR();
  //btn3.pressISR();
}


void manualCtrlSetup()
{
  relayFan.setName("Fan");
  relayHeat.setName("Heat");
  relayCool.setName("Cool");
    
  btnSwitch.setDebTimeout(50);
  btn2.setDebTimeout(75);
  btn3.setDebTimeout(100);

  DEBUG_PRINT("Attaching interrupt to: %d\n", btnSwitch.getPin());
  // attachInterrupt(digitalPinToInterrupt(btnSwitch.getPin()), isrBtnRaw, CHANGE);
  btnSwitch.attachISR(isrBtnRaw, CHANGE);

  DEBUG_PRINT("Attaching interrupt to: %d\n", btn2.getPin());
  // attachInterrupt(digitalPinToInterrupt(btn2.getPin()), isrBtnRaw, FALLING);
//  btn2.attachISR(isrBtnRaw, FALLING);

  DEBUG_PRINT("Attaching interrupt to: %d\n", btn3.getPin());
  // attachInterrupt(digitalPinToInterrupt(btn3.getPin()), isrBtnRaw, FALLING);  
  //btn3.attachISR(isrBtnRaw, FALLING);

  DEBUG_PRINT("Attaching interrupt to: encoder\n");
  // encBtn.attachISR(isrEnc, isrEnc);
}


void setup() {
#if defined(DEBUG) && DEBUG > 0
  Serial.begin(DEBUG_SERIAL_SPD);
	delay(1000);
  Serial.println();
  Serial.println("Started");
#endif

  manualCtrlSetup();

#if defined(DEBUG) && DEBUG > 0
  Serial.print("Parasite power is: ");
  Serial.println(tempSensor.isParasitePowerMode() ? "ON" : "OFF");
#endif

  menu.begin();

  menu.setCurrentItem(&tempRel1);
  menu.displayItem();
}

void loop() 
{  
  menu.tick();
}

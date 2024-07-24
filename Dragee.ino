#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>



#include "mDef.h"
#include "IODevices/input/SwitchButton.h"
// #include "IODevices/input/VirtTempSensor.h"
#include "IODevices/input/Enc.h"
#include "PID/lcdThermoPid.h"

LiquidCrystal_I2C lcd(0x27,20,4); 

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire); 

LcdThermoPid relayFan (FAN_PIN,  LED_PIN1,  &sensor);
LcdThermoPid relayHeat(HEAT_PIN, LED_PIN2,  &sensor);
LcdThermoPid relayCool(COOL_PIN, LED_PIN3,  &sensor);

SwitchButton btnSwitch(BTN1_PIN, SWITCH_TYPE, &relayFan);
SwitchButton btn2(BTN2_PIN, BTN_TYPE,    &relayHeat);
SwitchButton btn3(BTN3_PIN, BTN_TYPE,    &relayCool);

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
  attachInterrupt(digitalPinToInterrupt(btnSwitch.getPin()), isrBtnRaw, CHANGE);

    DEBUG_PRINT("Attaching interrupt to: %d\n", btn2.getPin());
  attachInterrupt(digitalPinToInterrupt(btn2.getPin()), isrBtnRaw, FALLING);

    DEBUG_PRINT("Attaching interrupt to: %d\n", btn3.getPin());
  attachInterrupt(digitalPinToInterrupt(btn3.getPin()), isrBtnRaw, RISING);  
}


void setup() {
#if defined(DEBUG) && DEBUG > 0
  Serial.begin(DEBUG_SERIAL_SPD);
	delay(1000);
  Serial.println();
  Serial.println("Started");
#endif

  // encoderSetup();
  manualCtrlSetup();

}

void loop() 
{  
  // eb.tick();
	// tickBtnList();
  // tickRelayList();
}

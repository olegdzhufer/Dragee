#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>



#include "mDef.h"
// #include "IODevices/input/VirtTempSensor.h"
// #include "IODevices/input/Enc.h"
#include "PID/lcdThermoPid.h"



// Relay relayFan(FAN_PIN, LED_PIN1);
//   Relay relayHeat(HEAT_PIN, LED_PIN2);
//     Relay relayCool(COOL_PIN, LED_PIN3);


// SwitchButton btn1(BTN1_PIN, SWITCH_TYPE, &relayFan);
//    SwitchButton btn2(BTN2_PIN, BTN_TYPE,    &relayHeat);
//       SwitchButton btn3(BTN3_PIN, BTN_TYPE,    &relayCool);


OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire); 

LcdThermoPid r1(FAN_PIN, LED_PIN1, 0.1, 0.1, 0.1, &sensor);

void IRAM_ATTR isrBtnRaw() 
{
  // btn1.tickRaw();
  // btn2.tickRaw();
  // btn3.tickRaw();
  
 // btn1.pressISR();
  //btn2.pressISR();
  //btn3.pressISR();

}


void manualCtrlSetup()
{
  // relayFan.setName("Fan");
  // relayHeat.setName("Heat");
  // relayCool.setName("Cool");
    
  // btn1.setDebTimeout(50);
  // btn2.setDebTimeout(75);
  // btn3.setDebTimeout(100);

  // DEBUG_PRINT("Attaching interrupt to: %d\n", btn1.getPin());
  // attachInterrupt(digitalPinToInterrupt(btn1.getPin()), isrBtnRaw, CHANGE);

  //   DEBUG_PRINT("Attaching interrupt to: %d\n", btn2.getPin());
  // attachInterrupt(digitalPinToInterrupt(btn2.getPin()), isrBtnRaw, FALLING);

  //   DEBUG_PRINT("Attaching interrupt to: %d\n", btn3.getPin());
  // attachInterrupt(digitalPinToInterrupt(btn3.getPin()), isrBtnRaw, RISING);


  
}





void setup() {
  Serial.begin(115200);
	delay(1000);
  Serial.println();
  Serial.println("Started");

  // encoderSetup();
  //manualCtrlSetup();

}

void loop() 
{  
  // eb.tick();
	// tickBtnList();
  // tickRelayList();
}

#include <Arduino.h>





#include "mDef.h"
#include "PID/LinkedList.h"
#include "IODevices/output/Relay.h"
#include "IODevices/input/SwitchButton.h"
#include "IODevices/input/Enc.h"

Relay relayFan(FAN_PIN, LED_PIN1);
  Relay relayHeat(HEAT_PIN, LED_PIN2);
    Relay relayCool(COOL_PIN, LED_PIN3);


SwitchButton btn1(BTN1_PIN, SWITCH_TYPE, &relayFan);
//    SwitchButton btn2(BTN2_PIN, BTN_TYPE,    &relayHeat);
//       SwitchButton btn3(BTN3_PIN, BTN_TYPE,    &relayCool);

  


void IRAM_ATTR isrBtnRaw() 
{ 
  btn1.pressISR();
  // btn2.pressISR();
  // btn3.pressISR();

}


// void manualCtrlSetup()
// {
//   relayFan.setName("Fan");
//   relayHeat.setName("Heat");
//   relayCool.setName("Cool");
    
//   btn1.setDebTimeout(100);
//   btn2.setDebTimeout(100);
//   btn3.setDebTimeout(100);

//   DEBUG_PRINT("Attaching interrupt to: %d\n", btn1.getPin());
//   attachInterrupt(digitalPinToInterrupt(btn1.getPin()), isrBtnRaw, CHANGE);

//     DEBUG_PRINT("Attaching interrupt to: %d\n", btn2.getPin());
//   attachInterrupt(digitalPinToInterrupt(btn2.getPin()), isrBtnRaw, FALLING);

//     DEBUG_PRINT("Attaching interrupt to: %d\n", btn3.getPin());
//   attachInterrupt(digitalPinToInterrupt(btn3.getPin()), isrBtnRaw, RISING);
  
// }


// void tickBtnList()
// {
  

//   if (btn1.tick())
//   {
//     DEBUG_PRINT("YES btn 1 has ticked");
//   }

//   if (btn2.tick()){
//     //DEBUG_PRINT("YES btn 2 has ticked");

//   }

//   if(btn3.tick()){
//     //DEBUG_PRINT("YES btn 3 has ticked");

//   }
// }


// void tickRelayList()
// {
  
//   relayFan.tick();
//   relayHeat.tick();
//   relayCool.tick();

// }

void setup() {
  Serial.begin(115200);
	delay(100);
  Serial.println("Started");
  relayFan.setName("Fan");
  relayHeat.setName("Heat");
  relayCool.setName("Cool");
  btn1.setDebTimeout(100);
  btn1.type = BTN_PRESS_t::SWITCH_TYPE;
  btn1.attachRelay(&relayFan);
  attachInterrupt(digitalPinToInterrupt(btn1.getPin()), isrBtnRaw, CHANGE);

  // // encoderSetup();
  // manualCtrlSetup();

}

uint32_t buferTest = 0;

void loop() 
{  
  if(btn1.tick()){
    DEBUG_PRINT("Work Tick");
  }
  // eb.tick();
	// tickBtnList();
  // tickRelayList();
}

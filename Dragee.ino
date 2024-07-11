#include <Arduino.h>





#include "mDef.h"
#include "PID/LinkedList.h"
#include "IODevices/output/Relay.h"
#include "IODevices/input/SwitchButton.h"
#include "IODevices/input/Enc.h"

Relay relayFan(FAN_PIN, LED_PIN1);
  Relay relayHeat(HEAT_PIN, LED_PIN2);
    Relay relayCool(COOL_PIN, LED_PIN3);


SwitchButton btn1(BTN3_PIN, SWITCH_TYPE, &relayFan );
   SwitchButton btn2(BTN2_PIN, BTN_TYPE,    &relayHeat);
      SwitchButton btn3(BTN1_PIN, BTN_TYPE,    &relayCool);

  
// LinkedList<Relay*> RelayList = LinkedList<Relay*>();
 LinkedList<SwitchButton*> ButtonList = LinkedList<SwitchButton*>();


void IRAM_ATTR isrBtn(void *arg) {
  SwitchButton *sb = static_cast<SwitchButton *>(arg);
  sb->pressISR();
}

void IRAM_ATTR isrBtnRaw() 
{
  btn1.pressISR();
  btn2.pressISR();
  btn3.pressISR();
}


void manualCtrlSetup()
{
  relayFan.setName("Fan");
  relayHeat.setName("Heat");
  relayCool.setName("Cool");
    
	// RelayList.add(&relayFan);
	// RelayList.add(&relayHeat);
	// RelayList.add(&relayCool);
  // Serial.print(RelayList.size());

  
  
  ButtonList.add(&btn1);
	ButtonList.add(&btn2);
	ButtonList.add(&btn3);
  btn1.setDebTimeout(100);
  btn2.setDebTimeout(100);
  btn3.setDebTimeout(100);

  attachInterrupt(digitalPinToInterrupt(btn1.getPin()), isrBtnRaw, CHANGE);
  attachInterrupt(digitalPinToInterrupt(btn2.getPin()), isrBtnRaw, FALLING);
  attachInterrupt(digitalPinToInterrupt(btn3.getPin()), isrBtnRaw, RISING);

  //  SwitchButton *btn;    
	//  for(int i = 0; i < ButtonList.size(); i++){
	// 	 btn = ButtonList.get(i);
  //   //  attachInterruptArg(digitalPinToInterrupt(btn->getPin()), isrBtn, &btn, CHANGE);
  //   }
}


void tickBtnList()
{
  SwitchButton *btn;
	for(int i = 0; i < ButtonList.size(); i++)
  {
		btn = ButtonList.get(i);
    if (btn == NULL) {
      return;
    }
    btn->tick();
	}
}


// void tickRelayList()
// {
//   Relay *relay;
// 	for(int i = 0; i < RelayList.size(); i++)
//   {
// 		relay = RelayList.get(i);
//     if (relay == NULL) {
//       return;
//     }
//     relay->tick();
// 	}
// }

void setup() {
  Serial.begin(115200);
	delay(100);
  Serial.println("Started");

  encoderSetup();
  manualCtrlSetup();

}

void loop() 
{  
  eb.tick();
	tickBtnList();
  // tickRelayList();
}

#include <Arduino.h>





#include "mDef.h"
#include "LinkedList.h"
#include "relayModule/Relay.h"
#include "ctrlModule/SwitchButton.h"


// IRAM_ATTR set in core defines 
void ARDUINO_ISR_ATTR isrBtn(void *arg) {
  SwitchButton *sb = static_cast<SwitchButton *>(arg);
  sb->tickRaw();
}



LinkedList<Relay*> RelayList = LinkedList<Relay*>();
LinkedList<SwitchButton*> ButtonList = LinkedList<SwitchButton*>();

void manualCtrlSetup()
{
    Relay* relayFan = new Relay(FAN_PIN, LED_PIN1);
    Relay* relayHeat = new Relay(HEAT_PIN, LED_PIN2);
    Relay* relayCool = new Relay(COOL_PIN, LED_PIN3);

    relayFan->setName("Fan");
    relayHeat->setName("Heat");
    relayCool->setName("Cool");
    
	RelayList.add(relayFan);
	RelayList.add(relayHeat);
	RelayList.add(relayCool);

   Serial.print(RelayList.size());


   SwitchButton* btn1 = new SwitchButton(BTN1_PIN, SWITCH_TYPE, relayFan , INPUT, LOW);
   SwitchButton* btn2 = new SwitchButton(BTN2_PIN, BTN_TYPE,    relayHeat, INPUT, LOW);
   SwitchButton* btn3 = new SwitchButton(BTN3_PIN, BTN_TYPE,    relayCool, INPUT, LOW);

  
  //  digitalPinToInterrupt(p)
  // attachInterrupt(uint8_t pin, std::function<void ()> intRoutine, int mode)
  // attachInterrupt(uint8_t pin, void (*)(void), int mode)
  // attachInterruptArg(uint8_t pin, void (*)(void *), void *arg, int mode)
  
  ButtonList.add(btn1);
	ButtonList.add(btn2);
	ButtonList.add(btn3);


   SwitchButton *btn;
	for(int i = 0; i < ButtonList.size(); i++){

		btn = ButtonList.get(i);
    // attachInterruptArg(btn1.PIN, isr, &btn, FALLING);
    attachInterruptArg(btn->getPin(), isrBtn, btn, CHANGE);
	}
}




void setup() {
  Serial.begin(115200);
	


  //manualCtrlSetup();

}

void loop() 
{

	
	
  
	while (true); // nothing else to do, loop forever



}

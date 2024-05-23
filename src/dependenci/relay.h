#include <Arduino.h>
#ifndef RELAY_H
#define RELAY_H

#include "pins.h"

uint8_t RelayState1 = LOW;
uint8_t RelayState2 = LOW;
uint8_t RelayState3 = LOW;

bool changeRelayState1 = false;
bool changeRelayState2 = false;
bool changeRelayState3 = false;

bool relayState;

void relay_setup()
{
  digitalWrite(REL1, RelayState1);
  pinMode(REL1, OUTPUT);

  digitalWrite(REL2, RelayState2);
  pinMode(REL2, OUTPUT);

  digitalWrite(REL3, RelayState3);
  pinMode(REL3, OUTPUT);
}

void turnOnHeating(){
  if(changeRelayState1){
    RelayState1 =! RelayState1;
    digitalWrite(REL1, RelayState1);
    changeRelayState1 = false;
  }
}

void turnOnCooling(){
  if(changeRelayState2){
    RelayState2 != RelayState2;
    digitalWrite(REL2, RelayState2);
    changeRelayState2 = false;
  }
}

void relay_handler3(){
  if(changeRelayState3){
    RelayState3 != RelayState3;
    digitalWrite(REL3, RelayState3);
    changeRelayState3 = false;
  }
}

void turnOffHeating(){
  digitalWrite(REL1, LOW);
}

void turnOffCooling(){
  digitalWrite(REL2, LOW);
}

void relay_loop(){
  turnOnHeating();
  turnOnCooling();
  relay_handler3();
}
#endif

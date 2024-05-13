#ifndef RELAY_H
#define RELAY_H

bool changeRelayState = false;
bool relayState;

void relay_setup()
{
  digitalWrite(REL1, LOW);
  pinMode(REL1, OUTPUT);

  digitalWrite(REL2, LOW);
  pinMode(REL2, OUTPUT);

  digitalWrite(REL3, LOW);
  pinMode(REL3, OUTPUT);
}

void relay_handler(){
  if(changeRelayState){
    relayState =!relayState;
    digitalWrite(relayPin, relayState);
      If(relayState ==false){ 
        timerState == fasle;
     }
  }
}

void relay_loop(){
  relay_handler();
}
#endif

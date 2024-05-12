#ifndef RELAY_H
#define RELAY_H

bool changeRelayState;

void relay_setup()
{
  digitalWrite(relayPin, LOW);
  pinMode(REL, OUTPUT);
}
void relay_handler(){
  if(changeRelayState){
    digitalWrite(relayPin, HIGH);
  }
}
#endif

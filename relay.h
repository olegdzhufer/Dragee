#ifndef RELAY_H
#define RELAY_H

void relay_setup()
{
  digitalWrite(relayPin, HIGH);
  pinMode(REL, OUTPUT);
}

#endif

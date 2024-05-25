#ifndef RELAY_H
#define RELAY_H



void relay_setup()
{
  digitalWrite(REL1, RelayState1);
  pinMode(REL1, OUTPUT);

  digitalWrite(REL2, RelayState2);
  pinMode(REL2, OUTPUT);

  digitalWrite(REL3, RelayState3);
  pinMode(REL3, OUTPUT);
}

void relay_handler1(){
  if(changeRelayState1){
    RelayState1 =! RelayState1;
    digitalWrite(REL1, RelayState1);
    changeRelayState1 = false;
  }
}

void relay_handler2(){
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

void relay_loop(){
  relay_handler1();
  relay_handler2();
  relay_handler3();
}
#endif

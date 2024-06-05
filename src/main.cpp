#include "inc.h"
#include "mDef.h"

int timer_46 = 0;

void setup() {
    Serial.begin(115200);
    dallas_setup();
    setupWifi();
}


void loop() {
    wifiLoop();
}


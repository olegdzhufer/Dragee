#include "inc.h"
#include "mDef.h"

int timer_46 = 0;

void setup() {
    // Serial.begin(9600);
    // if(menuSetup() != STATUS_C::STATUS_OK){
    //     Serial.print("\n LCD exeption !\n");
    // }

    siteSetup();
}


void loop() {

    siteLoop();

}



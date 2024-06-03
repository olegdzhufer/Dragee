#include "inc.h"
#include "mDef.h"

void setup() {
    Serial.begin(9600);
    if(menuSetup() != STATUS_C::STATUS_OK){
        Serial.print("\n LCD exeption !\n");
    }



}




void loop() {

}



#include "inc.h"
#include "mDef.h"

#define RUN_MODE 1

void setupWifi()
{
#if(RUN_MODE ==1)
    setupWifi_AP();
#elif(RUN_MODE == 2)
    setupWifi_STA();
#else
#endif
}

void setup() {
    DEBUG_BEGIN
    DEBUG_PRINTLN(__FILE__);
    // dallas_setup();
    setupWifi();
    
}


void loop() {
#if(RUN_MODE ==1)
    loopThingSpeak();
#endif
}


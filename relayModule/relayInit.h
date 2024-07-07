#ifndef RELAY_INIT_H
#define RELAY_INIT_H

#include "mDef.h"
#include "wokwiRelay.h"

RelayList * globalRelayList_p = NULL;

RelayList relayFan(FAN_PIN, LOW);
RelayList relayHeat(HEAT_PIN, LOW);
RelayList relayCool(COOL_PIN, LOW);

// def struct BTN_RELAY{
//   uint8_t id;
//   String name;
//   Button* btn_p=NULL;
//   uint8_t press_flag=0;
//   uint8_t pin_relay=0;
//   uint8_t state_relay=0;
//   BTN_RELAY *next_p=NULL;
// }BTN_RELAY;


void relaySetup()
{
    relayFan.setName("Fan");
    relayHeat.setName("Heat");
    relayCool.setName("Cool");
    
    relayFan.setNext(&relayHeat);
    relayHeat.setNext(&relayCool);
    // relayCool.setNext(&relayFan);

    globalRelayList_p = &relayFan;
}

void relayTick()
{

    while (globalRelayList_p)
    {
        globalRelayList_p->tick(); //if nothing to process next make ptr NULLs
    }
    globalRelayList_p = RelayList::first_p;

    /**
     * SAME AS
     *  relayHeat.tick();
     * relayCool.tick();
     * relayFan.tick();
     */
}

#endif

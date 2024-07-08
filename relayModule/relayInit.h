#ifndef RELAY_INIT_H
#define RELAY_INIT_H

#include "../mDef.h"
#include "Relay.h"

// RelayList * globalRelayList_p = NULL;

RelayList relayFan(FAN_PIN, LOW);
RelayList relayHeat(HEAT_PIN, LOW);
RelayList relayCool(COOL_PIN, LOW);


void relaySetup()
{
    relayFan.setName("Fan");
    relayHeat.setName("Heat");
    relayCool.setName("Cool");
    
    relayFan.setNext(&relayHeat);
    relayHeat.setNext(&relayCool);
    // relayCool.setNext(&relayFan);

    // globalRelayList_p = &relayFan;
}

//!  CALL     RelayList::tickAll();  in main loop

// void relayTick()
// {
    /************ 1 *******/

    // RelayList::tickAll();


    /************ 2 ***********/
    // while (globalRelayList_p)
    // {
    //     globalRelayList_p->tick(); //if nothing to process next make ptr NULLs
    // }
    // globalRelayList_p = RelayList::first_p;



    /**
     * SAME AS     /************ 3 *************
     *  relayHeat.tick();
     * relayCool.tick();
     * relayFan.tick();
     */
// }

#endif

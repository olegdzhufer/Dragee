#include <Arduino.h>
#include <Menulib.h>

Menu menu ;

#include "dependenci/pins.h"
#include "dependenci/btns.h"
#include "dependenci/dallas_sensor.h"
#include "dependenci/led.h"
#include "dependenci/menu.h"
#include "dependenci/encoder.h"

#include "dependenci/encWork.h"
#include "dependenci/timer.h"

Storage store;

int encderVal = 0x00;

int key;
int pinComeBack(String name);


void setup() {
    Serial.begin(9600);
    menu = * (initMenu());

    store = *(initStore());

    menu.newScreen(&menu, "Setup", "Relays");
    
    menu.addLine(&menu, "Relay_1: ", "FAN");
    menu.addLine(&menu, "Relay_2: ", "TEN");
    menu.addLine(&menu, "Relay_3: ", "COOL");

    store.inStore(menu.currentScreen, &store);
    store.allUp(&store);

    // buttons_setup();
    encoder_setup();
    // relay_setup();
    dallas_setup();
    timer_setup();
}


void loop() {
//     delay(10);
//     Line* line;
//     Liner* liner;
    
//     en.tick();
//     key = read_encoder();

//     if(key == 0x01){
//         key = 0x00;
//         menu.nextLine(&menu);
//     }else if(key == 0x02){
//         key = 0x00;
//         menu.prevLine(&menu);
//     }else if(key = 0x05){
//         liner = store.finder(&store, menu.getName(&menu));
//         line = liner->line;

//         int pin = pinComeBack(menu.getName(&menu));

//         if (digitalRead(pin) == HIGH){
//             digitalWrite(pin, LOW);
//             liner->val = false;
//         }else{
//             digitalWrite(pin, HIGH);
//             liner->val = true;
//         }
//         store.allUp(&store);

//     }

// }

// int pinComeBack(String name){
//     if(name == "FAN") return REL1;
//     if(name == "TEN") return REL2;
//     if(name == "COOL")return REL3;
//     return 0;
dallas_loop();
timer_loop();
}

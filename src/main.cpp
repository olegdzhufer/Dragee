#include <Arduino.h>
#include <Menulib.h>


static Menu menu;
Screen* mainS;

#include "dependenci/pins.h"
#include "dependenci/btns.h"
#include "dependenci/dallas_sensor.h"
#include "dependenci/led.h"
#include "dependenci/menu.h"
#include "dependenci/encoder.h"
#include "dependenci/TimerSet.h"

int encderVal = 0x00;


int key;
float temp = readTemperatureSensor(temperatureSensor);


void setup() {
    Serial.begin(9600);
    encoder_setup();
    timer_setup();
    menu = *(initMenu());
    setup_Menu(&menu);

    dallas_setup();

    menu.printScreen(&menu);
    mainS = menu.curr;
    
  
}


void loop() {
    
    int press = read_encoder();
    if(press){
        Screen* curr;
        switch (press)
        {
        case 1:
            menu.prevLine(&menu);
        break;
        case 2:
            menu.nextLine(&menu);
        break;
        case 3:
            menu.curr = mainS;
        break;
        case 4:
            menu.nextScreen(&menu);
        break;

        case 5:            
            Serial.print(mainS->name);



        break;
        
        default:

            break;
        }
    }
}


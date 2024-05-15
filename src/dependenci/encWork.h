#include <Arduino.h>
#include <Menulib.h>
#include "menu.h"
#include "encoder.h"

#include "menu.h"

int encWork_loop(){
    en.tick();
    
    int key = read_encoder();
    
    return key;
    
}
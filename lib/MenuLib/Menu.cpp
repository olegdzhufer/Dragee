
#include "MenuLib.h"

void printScreen (Menu* menu){
    int cursor = 0;
    Line* line = menu->curr->current->prev;

    LiquidCrystal_I2C* lcd = menu->lcd; 
    Screen* screen = menu->curr;
        Serial.print('1');
    lcd->clear();
    lcd->setCursor(0, cursor);
    lcd->printf(">> ");
    lcd->printf(screen->header->textGen(screen->header));
    Serial.print('2');
    cursor ++;
    Serial.print('3');

    Serial.print('4');
    while( cursor < ROWS  || (line != screen->current && cursor < 3) ){
        lcd->setCursor(0, cursor);
        Serial.print('5');
        if(line == screen->current){
            lcd->print('>');
            lcd->printf(line->textGen(line));
        }
        else lcd->printf(line->textGen(line));

        line = line->next;
        cursor ++;
        Serial.print('6');
    }
    if(screen->footer){
        Serial.print('7');
        lcd->setCursor(0, cursor);
        lcd->printf(screen->footer->textGen(screen->footer));
    }
    Serial.print('8');
}


void autoPrEn (Menu* menu){
    menu->printScreen(menu); // Timer
}


void autoPrDe (Menu* menu){
    menu->printScreen(menu); // Timer off
}


void nextLine (Menu* menu){
    if(menu->curr){
        if(menu->curr->current && menu->curr->current->next){
            menu->curr->current = menu->curr->current->next;
        }
    }
    menu->printScreen(menu);
}
void prevLine (Menu* menu){
    if(menu->curr){
        if(menu->curr->current && menu->curr->current->prev){
            menu->curr->current = menu->curr->current->prev;
        }
    }
    menu->printScreen(menu);
}


void nextScreen (Menu* menu){
    if(menu->curr && menu->curr->next){
        menu->curr = menu->curr->next;
    }
    menu->printScreen(menu);
}
void prevScreen (Menu* menu){
    if(menu->curr && menu->curr->prev){
        menu->curr = menu->curr->prev;
    }
    menu->printScreen(menu);
}


Screen* addScreen(Menu* menu, char* name){

    if(!name)return NULL;

    Screen* screen = initScreen(name);
    if(screen){
        if(menu->curr == NULL){
            menu->curr = screen;
            screen->next = screen;
            screen->prev = screen;
        }else{

            screen->next = menu->curr;
            screen->prev = menu->curr->prev;
            menu->curr->prev->next = screen;
            menu->curr->prev = screen;
        }
        return screen;
    }
    return NULL;
}


Screen* getScreen(Menu* menu, char* name){
    if(!menu->curr || !name) return NULL;

    Screen* cur = menu->curr;

    if(cur->name == name) return cur;
    cur = cur->next;
    while(cur != menu->curr){
        if(cur->name == name) return cur;
        cur = cur->next;
    }

    return NULL;

}


Line* addLine (Menu* menu, char* name, char* description, valLine* valuer){
    if(menu && name && description && menu->curr){
        return menu->curr->newLine_ptr(menu->curr, name, description, valuer);
    }
}

void removeLineByNameM (Menu* menu, char* name){
    if(menu && name && menu->curr){
        menu->curr->removeLineByName(menu->curr, name);
    }
}
void removeLineByPtrM (Menu* menu, Line* line){
    if(menu && line && menu->curr){
        menu->curr->removeLineByPtr(menu->curr, line);
    }
}

void removeScreenByName (Menu* menu, char* name){
    if(menu && name){
        Screen* screen = menu->getScreen(menu, name);
        menu->removeScreenByPtr(menu, screen);
    }
}
void removeScreenByPtr (Menu* menu, Screen* screen){
    if(screen && menu){

        if(screen->next = screen){
            menu->curr = NULL;
        }
        else{
            
        screen->prev->next = screen->next;
        screen->next->prev = screen->prev;
        }
            
        destructScreen(screen);
    }

}


char* getName(Menu* menu){
    if(menu && menu->curr && menu->curr->name){
        return menu->curr->name;
    }
    return NULL;
}

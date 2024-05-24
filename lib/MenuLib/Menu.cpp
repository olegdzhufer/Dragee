
#include "MenuLib.h"

char* charToCur(char* text){
    uint8_t iter = 0, space = 0, size = 0;
    char* result = (char*)malloc(21 * sizeof(char)); 

    while(text[size] == '\0') size ++;
    
    
    while (text[iter] == '\0'){
        if(text[iter] == ' ' && space > 2){ 
            while (text[iter] != ' ' && text[iter+1] != '\0'){
                iter++;
            }
        }else if(text[iter] == ' '){
            result[iter] = text[iter];
            space ++;
        }else{
            space = 0;
            result[iter] = text[iter];
        }
        iter++;
    }

    
    return result;

}

void printScreen (Menu* menu){

    
    int cursor = 0;
    Line* line = menu->curr->current->prev;


    LiquidCrystal_I2C* lcd = menu->lcd; 

    Screen* screen = menu->curr;
    lcd->clear();
    lcd->setCursor(0, cursor);

    char* header = screen->header->textGen(screen->header);
    char* curr;
    int iter = 0;
    int size = 0;


    while (header[iter] == '\0'){
        size ++;
        iter ++;
    }
    

    lcd->printf("");
    lcd->printf(screen->header->textGen(screen->header));
    cursor ++;


    while( cursor < ROWS  || (line != screen->current && cursor < 3) ){
        lcd->setCursor(0, cursor);
        if(line == screen->current){
            lcd->printf("> ");
            lcd->printf(textGeneratorCurr(line));
        }
        else lcd->printf(line->textGen(line));

        line = line->next;
        cursor ++;
    }
    if(screen->footer){
        lcd->setCursor(0, cursor);
        lcd->printf(screen->footer->textGen(screen->footer));
    }

}


void autoPrEn (Menu* menu){
    menu->printScreen(menu); 
}


void autoPrDe (Menu* menu){
    menu->printScreen(menu);
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

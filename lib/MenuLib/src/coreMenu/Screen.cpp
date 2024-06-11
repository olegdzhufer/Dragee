#include "MenuLib.h"

Line* newLine(Screen* screen, char* name, char* description, valLine* valuer){

    Line* line = initLine(name, description, valuer);

    if (line){

        if(screen->current == NULL){
            screen->current = line;
            screen->current->next = line;
            screen->current->prev = line;
        } else{
            line->next = screen->current;
            line->prev = screen->current->prev;

            screen->current->prev->next = line;
            screen->current->prev = line;
        }
        return line;

    }
    return NULL;
    
}


Line* getLine(Screen* screen, char* name){
    if(screen->current == NULL) return NULL;
    if(name == NULL) return NULL;
    Line* cur = screen->current;

    if(cur->name == name) return cur;
    cur = cur->next;

    while(cur != screen->current){
        if(cur->name == name){
            return cur;
        }
        cur = cur->next;
    }

    return NULL;

}


void removeLineByName(Screen* screen, char* name){
    Line* line = screen->getLine_ptr(screen, name);

    removeLineByPtr(screen, line);
}


void removeLineByPtr(Screen* screen, Line* Line){
    if(Line){

        if(Line->next = Line){
            screen->current = NULL;
            
        }
        else{
            
        Line->prev->next = Line->next;
        Line->next->prev = Line->prev;
        }
            
        destructLine(Line);
    }
}
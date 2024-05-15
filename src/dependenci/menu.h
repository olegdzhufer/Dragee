#ifndef MENU_H
#define MENU_H

#include <Menulib.h>



typedef struct Liner{
    Line* line;

    String name;
    String text;

    bool val;

    Liner* next;


    void (*updateLine)  (Liner* line);
    void (*changeState) (Liner* line);
    
    

}Liner;

typedef struct Storage{
    Liner* lines;

    Liner*  (*finder)   (Storage* st,String name);
    void    (*inStore)  (Screen* screen, Storage* st);
    void    (*allUp)    (Storage* store);
    void    (*addElem)  (Storage* store, String name, String text, bool val, Line* line);


}Storage;

Storage* initStore();
Liner* initliner    (String name, String text, bool val, Line* line);
void changeState  (Liner* line);

void updateLine     (Liner* line);

Liner* finder       (Storage* st, String name);
void inStore        (Screen* screen, Storage* st);
void allUp          (Storage* store);

void addElem  (Storage* store, String name, String text, bool val, Line* line);

#endif
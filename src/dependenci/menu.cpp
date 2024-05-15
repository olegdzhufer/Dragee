#include "menu.h"

Storage* initStore(){
    Storage* store = new Storage;

    store->lines = initliner("start", "start", 0, NULL);

    store->finder = finder;
    store->inStore= inStore;
    store->allUp = allUp;
    store->addElem = addElem;

    return store;
}
Liner* initliner(String name, String text, int val, Line* line){
    Liner* lin = new Liner;
    lin->name = name;
    lin->text = text;
    lin->val = val;

    lin->line = line;

    lin->next = NULL;

    lin->updateLine = updateLine;

    return lin;

}

void updateLine(Liner* line){
    String rez = line->text;
    rez += String(line->val); 
    line->line->content = rez;
}



Liner* finder(Storage* st, String name){
    Liner* line = st->lines;

    while (line){

        if(line->name == name){
            return line;
        }
        line = line->next;
    }
    
    return NULL;
    
}

void addElem  (Storage* store, String name, String text, int val, Line* line){
    Liner* liner = store->lines;

    while (liner->next)liner = liner->next;
    liner->next = initliner(name, text, val, line);

}

void inStore(Screen* screen, Storage* st){
    Line* scr = screen->currentLine;
    Line* start = scr;

    st->addElem(st, scr->id, scr->content, 0, scr);
    scr = scr->next;

    while (scr->next != start)
    {
        st->addElem(st, scr->id, scr->content, 0, scr);
        scr = scr->next;
    }
        st->addElem(st, scr->id, scr->content, 0, scr);
    

}


void allUp(Storage* store){
    Liner* line = store->lines->next;

    while (line){
        line->updateLine(line);
        line = line->next;
    }
}

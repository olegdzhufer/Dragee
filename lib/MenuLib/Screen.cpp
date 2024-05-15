#include "Menulib.h"

Screen* initScreen(String id, String description,  Screen* next, Screen* prev){
    Screen* scr = new Screen;

    scr->descLine = initLine("description", description, NULL, NULL);

    scr->id = id;
    //func

    scr->getLine = getLine;
    scr->newLine = newLine;
    scr->removeLine = removeLine;


    if(next != NULL)scr->next = next;
    if(prev != NULL)scr->prev = prev;



    return scr;
}

Line* getLine(Screen* scr, String id){
    Line* curr = scr->currentLine;
    if (curr->id == id)return curr;

    if(curr->next != scr->currentLine && curr->next != NULL) curr = curr->next;

    while (curr->next != scr->currentLine && curr->next != NULL){
        if(curr->id == id) return curr;
        curr = curr->next;
    }
    return NULL;
    
}

Line* newLine(Screen* scr, String content, String id){

    Line* line = initLine(id, content, NULL, NULL);

    if (scr->currentLine != NULL) {

        scr->currentLine = line;
        scr->currentLine->next = line;
        scr->currentLine->prev = line;

        return line;

    }else{
        

        line->prev = scr->currentLine->prev;
        line->next = scr->currentLine;

        line->prev->next = line;

        scr->currentLine->prev = line;

        return line;
        
    }
    
}
void  removeLine(Screen* scr, String Id){
    Line* remLine = getLine(scr, Id);

    delete remLine;
}
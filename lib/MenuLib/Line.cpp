#include "Menulib.h"

Line* initLine(String id, String content, Line* next, Line* prev){
    Line* line = new Line;

    line->id = id;
    line->content = content;

    if(next != NULL)line->next = next;
    if(prev != NULL)line->prev = prev;

    return line;
}
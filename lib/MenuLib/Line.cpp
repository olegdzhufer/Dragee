#include "MenuLib.h"

char* textGenerator(Line* line){
    char *val, *text, *result;
    char booler[4];
    int iterationCounter = 0;

    text = charGenerator(line->descript, 14);
    


    switch(line->val->TYPE){
        case valLine::INTEGER:

            val = IntToString(line->val->var.count);
            result = mergeChar(text, val);
            free(text);
            free(val);
        break;

        case valLine::BOOLING:
            if(line->val->var.status == true){
                
                booler[0] = 'O';
                booler[1] = 'N';
                booler[2] = ' '; 
                booler[3] = '\0';
                
            }else{
                booler[0] = 'O';
                booler[1] = 'F';
                booler[2] = 'F'; 
                booler[3] = '\0';
            }
            
            result = mergeChar(text, booler);
            free(text);
        break;


        case valLine::FLOAT:
            val = floatToString(line->val->var.temp, 2);
            result = mergeChar(text, val);
            free(text);
            free(val);
        break;

        case valLine::TEXT:
            val = line->val->var.mode;

            result = mergeChar(text, val);
            free(text);
        break;

        case valLine::NULLTYPE:
            result = text;
            free(text);
        break;
        
    }

    return result;
}

char* textGeneratorCurr(Line* line){
    char *val, *text, *result;
    char booler[4];
    int iterationCounter = 0;

    text = charGenerator(line->descript, 12);
    


    switch(line->val->TYPE){
        case valLine::INTEGER:

            val = IntToString(line->val->var.count);
            result = mergeChar(text, val);
            free(text);
            free(val);
        break;

        case valLine::BOOLING:
            if(line->val->var.status == true){
                
                booler[0] = 'O';
                booler[1] = 'N';
                booler[2] = ' '; 
                booler[3] = '\0';
                
            }else{
                booler[0] = 'O';
                booler[1] = 'F';
                booler[2] = 'F'; 
                booler[3] = '\0';
            }
            
            result = mergeChar(text, booler);
            free(text);
        break;


        case valLine::FLOAT:
            val = floatToString(line->val->var.temp, 2);
            result = mergeChar(text, val);
            free(text);
            free(val);
        break;

        case valLine::TEXT:
            val = line->val->var.mode;

            result = mergeChar(text, val);
            free(text);
        break;

        case valLine::NULLTYPE:
            result = text;
            free(text);
        break;
        
    }

    return result;
}




void setParam (Line* line, valLine* valuer){
    line->val = valuer;
}




char* getType(Line* line){

    char* result = (char*)malloc(4*sizeof(char));

    if(result){
        switch(line->val->TYPE){
            case valLine::INTEGER:
                result[0] = 'I';
                result[1] = 'N';
                result[2] = 'T';
            break;


            case valLine::BOOLING:
                result[0] = 'B';
                result[1] = 'O';
                result[2] = 'L';
            break;


            case valLine::FLOAT:
                result[0] = 'F';
                result[1] = 'L';
                result[2] = 'O';
            break;


            case valLine::TEXT:
                result[0] = 'S';
                result[1] = 'T';
                result[2] = 'R';
            break;


            case valLine::NULLTYPE:
                result[0] = 'N';
                result[1] = 'U';
                result[2] = 'L';
            break;

        }
        return result;
    }
    return NULL;
}
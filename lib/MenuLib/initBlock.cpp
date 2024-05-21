#include "MenuLib.h"

LiquidCrystal_I2C* initLCD(){
    static LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);

    if (lcd.begin(COLUMS, ROWS, LCD_5x8DOTS, SDA_PIN, SCL_PIN, SPEED_I2C, TIME_I2C) != 1){
        
        Serial.printf("ajkshfkjahsjkfhakjshfnkajshfkjhaskjfhashfkjashfkjhassjkfhakjsfhakjsf");
        Serial1.printf("jksahfkjahskjfhakjshfkjashfkjashfkjhaskjfhakjsfhakjhfkjahsfkjahkfjhasf \n");
        return NULL;
    }

    Serial.print("\n");
    Serial.printf("LCDInit: %p", &lcd);
    Serial.print("\n");

    return &lcd;
}

valLine* initData(void* data, int type){
    valLine* dataLine = (valLine*)malloc(sizeof(valLine));

    if(dataLine){

        dataLine->setInt = setInt;
        dataLine->setBool = setBool;
        dataLine->setChar = setText;
        dataLine->setfloat = setFloat;


        switch(type){
            
            case 0:
                setInt(dataLine,(int) data);
            break;


            case 1:
                setBool(dataLine, (bool) data);
            break;


            case 2:
                setFloat(dataLine, *(float*) data);
            break;

            case 3:
                setText(dataLine, (char*) data);
            break;

            case 4:
                setNull(dataLine);
            break;

        }

        return dataLine;
    }

    return NULL;
}


Line* initLine(char* name, char* description, valLine* valuer){
    Line* line = (Line*)malloc(sizeof(Line));
        if(line){
            line->name = name;
            line->descript = description;
            line->next = NULL;
            line->prev = NULL;

            line->textGen = textGenerator;
            line->setParam = setParam;
            line->getTypeParam = getType;

            line->destruct = destructLine;

            if(valuer == NULL){
                line->val = initData(NULL, 4);
            }else{
                line->val = valuer;
            }
            return line;
        }
    return NULL;
}

Screen* initScreen(char* name){
    Screen* screen = (Screen*)malloc(sizeof(Screen));

    if(screen){
        screen->name = name;
        screen->header = initLine(name, name, NULL);
        screen->current = NULL;
        screen->footer = NULL;

        screen->next = NULL;
        screen->next = NULL;

        screen->newLine_ptr = newLine;
        screen->getLine_ptr = getLine;
        screen->removeLineByName = removeLineByName;
        screen->removeLineByPtr = removeLineByPtr;

        screen->destruct = destructScreen;
        return screen;
    }
    return NULL;
}

Menu* initMenu(){
    Menu* menu = (Menu*)malloc(sizeof(Menu));

    LiquidCrystal_I2C* lcd = initLCD();
    if(menu){
        menu->lcd = lcd;


        Serial.printf("\n %p \n" , &(menu->lcd));

        menu->curr = NULL;

        menu->addLine_ptr = addLine;
        menu->addScreen_ptr = addScreen;

        menu->autoPrintDe = autoPrDe;
        menu->autoPrintEn = autoPrEn;
        menu->printScreen = printScreen;

        menu->getScreen = getScreen;
        menu->getName = getName;

        menu->nextLine = nextLine;
        menu->nextScreen = nextScreen;

        menu->prevLine = prevLine;
        menu->prevScreen = prevScreen;
        
        menu->removeLineByName = removeLineByNameM;
        menu->removeLineByPtr = removeLineByPtrM;

        menu->removeScreenByName = removeScreenByName;
        menu->removeScreenByPtr = removeScreenByPtr;

        menu->destruct = destructMenu;

        return menu;
    }
    return NULL;
}

void destructData(valLine* data){
    if(data){
        // free(&data->var);
        free(data);
    }
}

void destructLine(Line* line){
    if(line){
        destructData(line->val);

        free(line);
    }
    
}

void destructScreen(Screen* screen){

    if(screen){

        while(screen->current != NULL){
            screen->removeLineByPtr(screen, screen->current);
        }
        free(screen);
    }
}

void destructMenu(Menu* menu){

    if(menu){

        while(menu->curr != NULL){
            menu->removeScreenByPtr(menu, menu->curr);
        }

        free(menu);

    }
    
}
#include "Menulib.h"

LiquidCrystal_I2C initLCD(){
    LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);
    Serial.print("\n");
    Serial.printf("First: %p", &lcd);
    Serial.print("\n");

    if (lcd.begin(COLUMS, ROWS, LCD_5x8DOTS, SDA_PIN, SCL_PIN, SPEED_I2C, TIME_I2C) != 1){

        Serial.print("\n");
        Serial.print("Result:");
        Serial.print("\n"); 
        Serial.println(F("PCF8574 is not connected or lcd pins declaration is wrong. Only pins numbers: 4,5,6,16,11,12,13,14 are legal."));
        
        delay(5000);

        Serial.print("\n");
        Serial.printf("LCDInit: %p", &lcd);
        Serial.print("\n");

        return LiquidCrystal_I2C();
    }

    Serial.print("\n");
    Serial.printf("LCDInit: %p", &lcd);
    Serial.print("\n");

    return lcd;
}


Menu* initMenu(){
    Menu* menu = new Menu;
    menu->lcd = initLCD();

    //func
    menu->printScreen = printScreen;

    menu->getScreen = getScreen;
    menu->newScreen = newScreen;
    menu->removeScreen = removeScreen;

    menu->nextLine = nextLine;
    menu->prevLine = prevLine;

    menu->addLine = addLine;
    menu->getName = getName;

    return menu;
}

void printScreen (Menu* menu){
    Screen* currScr = menu->currentScreen;

    
    menu->lcd.clear();

    menu->lcd.setCursor(0, 0);
    menu->lcd.print(">>>");
    menu->lcd.print(currScr->descLine->content);

    menu->lcd.setCursor(0, 1);
    menu->lcd.print(currScr->currentLine->prev->content);
    
    menu->lcd.setCursor(0,2);
    menu->lcd.print("> ");
    menu->lcd.print(currScr->currentLine->content);

    menu->lcd.setCursor(0, 3);
    menu->lcd.print(currScr->currentLine->next->content);

}

Screen* getScreen(Menu* menu, String id){
    Screen* curr = menu->currentScreen;
    if (curr->id == id)return curr;

    if(curr->next != menu->currentScreen && curr->next != NULL) curr = curr->next;

    while (curr->next != menu->currentScreen && curr->next != NULL){
        if(curr->id == id) return curr;
        curr = curr->next;
    }
    return NULL;
}

Screen* newScreen(Menu* menu, String descript, String id){
    Screen* scr = initScreen(id, descript, NULL, NULL);
    if(menu->currentScreen == NULL) {
        scr->next = scr;
        scr->prev = scr;

        menu->currentScreen = scr;
        
    }else{
        scr->prev = menu->currentScreen->prev;
        scr->next = menu->currentScreen;
        menu->currentScreen->prev->next = scr;
        menu->currentScreen->prev = scr;
    }

    return scr;
}
void removeScreen(Menu* menu, String id){
    Screen* scr = getScreen(menu, id);

    delete scr;
}
void nextLine(Menu* menu){
    Screen* scr = menu->currentScreen;

    if(scr->currentLine != NULL){
        scr->currentLine = scr->currentLine->next;
    }

    menu->printScreen(menu);
}
void prevLine(Menu* menu){
    Screen* scr = menu->currentScreen;

    if(scr->currentLine != NULL){
        scr->currentLine = scr->currentLine->prev;
    }

    menu->printScreen(menu);
}

Line* addLine(Menu* menu, String context, String id){

    menu->currentScreen->currentLine->id;
    Line* line = initLine(id, context, NULL, NULL);

    Screen* scr = menu->currentScreen;
    
    if(scr->currentLine == NULL){
        line->next = line;
        line->prev = line;

        scr->currentLine = line;
    } 
    else{
        line->next = scr->currentLine;
        line->prev = scr->currentLine->prev;

        scr->currentLine->prev->next = line;
        scr->currentLine->prev = line;
    }
    return line;
}

String getName(Menu* menu){
    String name = menu->currentScreen->currentLine->id;

    return name;
}
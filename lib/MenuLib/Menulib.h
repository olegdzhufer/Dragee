#ifndef MENULIB_H
#define MENULIB_H

#define LIQ_I2C

#define COLUMS              20  
#define ROWS                4    
#define LCD_SPACE_SYMBOL    0x20 
#define SCL_PIN             22
#define SDA_PIN             21
#define SPEED_I2C           400000
#define TIME_I2C            250

#include <LiquidCrystal_I2C.h>


typedef enum TimerSet{
    TIMER1,
    TIMER2,
    TIMER3,
    TIMER4,
}TimerSet;

typedef union variable{
    int count;
    bool status;
    float temp;
    char* mode;
}variable;


typedef struct valLine{

    variable var;

    void (*setInt)(valLine* data , int var);
    void (*setBool)(valLine* data , bool var);
    void (*setfloat)(valLine* data , float var);
    void (*setChar)(valLine* data , char* var);

    

    enum{INTEGER, BOOLING, TEXT, FLOAT, NULLTYPE} TYPE;
}valLine;



/*!
    @brief Line - this struct need to storage line data 
    @param name         this id or name line 
    @param description  this is the description of the line and also the first line of the minutiae displayed on the LCD
    @param val          ___
    @param next         ___
    @param prev         ___
*/
typedef struct Line{

    char* name;
    char* descript;

    char* inlcd;

    valLine* val;

    Line *next;
    Line *prev;

    char* (*textGen) (Line* line);
    void  (*setParam) (Line* line, valLine* valuer);
    char* (*getTypeParam) (Line* line);


    void (*destruct) (Line* line);

}Line;



typedef struct Screen{

    char* name;

    Screen* next;
    Screen* prev;

    Line* header;
    Line* current;
    Line* footer;

// Line operation
    Line* (*newLine_ptr)(Screen* screen, char* name, char* description, valLine* valuer);
    Line* (*getLine_ptr)(Screen* screen, char* name);

    void (*removeLineByName) (Screen* screen, char* name);
    void (*removeLineByPtr)(Screen* screen, Line* line);


    void (*destruct) (Screen* screen);
}Screen;


typedef struct Menu{

    LiquidCrystal_I2C* lcd;

    Screen* curr;

    void (*printScreen) (Menu* menu);
    void (*autoPrintEn) (Menu* menu);
    void (*autoPrintDe) (Menu* menu);

    void (*nextLine) (Menu* menu);
    void (*prevLine) (Menu* menu);
    void (*nextScreen) (Menu* menu);
    void (*prevScreen) (Menu* menu);

    Screen* (*addScreen_ptr) (Menu* menu, char* name);
    Line* (*addLine_ptr) (Menu* menu, char* name, char* description, valLine* valuer);

    void (*removeScreenByName)(Menu* menu, char* name);
    void (*removeScreenByPtr)(Menu* menu, Screen* screen);

    void (*removeLineByName) (Menu* menu, char* name);
    void (*removeLineByPtr)(Menu* menu, Line* line);

    Screen* (*getScreen)(Menu* menu, char* name);

    char* (*getName) (Menu* menu);



    void (*destruct) (Menu* Menu);

}Menu;

//INIT


LiquidCrystal_I2C* initLCD();


char* IntToString(int val);
char* charGenerator(char* rev, int space);
char* floatToString(float num, int precision);
char* mergeChar(const char* first, const char* second);

//


//
valLine* initData(void* data, char* type);
Line* initLine(char* name, char* description, valLine* valuer);
Screen* initScreen(char* name);
Menu* initMenu();


//Other function

//valLine

void setInt(valLine* data,int val);
void setBool(valLine* data,bool val);
void setFloat(valLine* data,float val);
void setText(valLine* data,char* val);
void setNull(valLine* data);


//Line

char* textGenerator(Line* line);
char* textGeneratorCurr(Line* line);
void setParam (Line* line, valLine* valuer);
char* getType(Line* line);


//Screen

Line* newLine(Screen* screen, char* name, char* description, valLine* valuer);
Line* getLine(Screen* screen, char* name);

void removeLineByName(Screen* screen, char* name);
void removeLineByPtr(Screen* screen, Line* Line);


//Menu


void printScreen (Menu* menu);
void autoPrEn (Menu* menu);
void autoPrDe (Menu* menu);

void nextLine (Menu* menu);
void prevLine (Menu* menu);

void nextScreen (Menu* menu);
void prevScreen (Menu* menu);

Screen* addScreen(Menu* menu, char* name);
Line* addLine (Menu* menu, char* name, char* description, valLine* valuer);

void removeLineByNameM (Menu* menu, char* name);
void removeLineByPtrM (Menu* menu, Line* line);

void removeScreenByName (Menu* menu, char* name);
void removeScreenByPtr (Menu* menu, Screen* screen);

Screen* getScreen(Menu* menu, char* name);

char* getName(Menu* menu);


//destructor
void destructData(valLine* data);
void destructLine(Line* line);
void destructScreen(Screen* screen);
void destructMenu(Menu* menu);

#endif
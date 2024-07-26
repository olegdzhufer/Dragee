#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include <Wire.h>

#include "../mDef.h"
#include "VirtLiquidCrystal.h"
#include "charList.h"
#include "../PID/TermoRelay.h"
#include "../IODevices/input/EncButton.h"

#define INIT_DELAY_TEXT 5000

class Menu {
public:
    
    Menu(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows)
    {
        lcd_p = new LiquidCrystal_I2C(lcd_addr, lcd_cols, lcd_rows);
    }

    Menu(LiquidCrystal_I2C *lcd_p, MenuEncButton *encBtn_p)
    {
        attachLcd(lcd_p);
        attachEncBtn(encBtn_p);
    }
    

    void begin()
    {
        lcd_p->begin();
        lcd_p->clear();
        lcd_p->setCursor(0, 0);
        lcd_p->print(initFirstLine);
        lcd_p->setCursor(0, 1);
        lcd_p->print(initSecondLine);
        lcd_p->setCursor(0, 2);
        lcd_p->print(initThirdLine);
        delay(INIT_DELAY_TEXT);
    }

    void attachLcd(LiquidCrystal_I2C *lcd)
    {   
        if(lcd != nullptr) lcd_p = lcd;
    }

    void attachEncBtn(MenuEncButton *encBtn)
    {
        if(encBtn != nullptr)
        {
            encBtn_p = encBtn;
            // encBtn_p->attachMenu(this);
        }
    }

    
    void displayItem()
    {
        lcd_p->clear();
        lcd_p->setCursor(0, 0);
        lcd_p->print(currentItem->relay_p->getName());
        lcd_p->setCursor(0, 1);
        lcd_p->print(currentItem->getTempCur());
        lcd_p->setCursor(0, 2);
        lcd_p->print(currentItem->getTempSet());
        if (currentItem->relay_p->getState() == ON)
        {
            lcd_p->setCursor(0, 3);
            lcd_p->print(currentItem->relay_p->timerSec);
        }
    }

    void changeSelection(int8_t change)
    {
        currentItem->tempSet += change;
    }

    void tick()
    {
        if(encBtn_p != nullptr) 
        {
            encBtn_p->tick();
        }

        TermoRelay *last = TermoRelay::getLastInstance();
        TermoRelay *current = last;
        while (current != nullptr)
        {
            if(current->tick())
            {
                currentItem = current;
                displayItem();
            }
            current = current->getNextInstance();
        }
    }

    void setCurrentItem(TermoRelay *item)
    {
        if(item != nullptr) currentItem = item;
    }
    

private:
    LiquidCrystal_I2C *lcd_p=nullptr;
    MenuEncButton *encBtn_p=nullptr;
    TermoRelay *currentItem=nullptr;
};


#endif // MENU_H
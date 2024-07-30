#ifndef VIRT_LIQUID_CRYSTAL_h
#define VIRT_LIQUID_CRYSTAL_h

#if (ARDUINO < 100)
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#ifdef __AVR__
#include <avr/pgmspace.h>
// #define FAST_MODE
#endif

// #include <inttypes.h>
#include <stdint.h>
#include <stddef.h>
#include <Print.h>

#include "LCD_defs.h"

#define LCD_DEFAULT_COLS 20
#define LCD_DEFAULT_ROWS 4

class VirtLiquidCrystal : public Print
{
public:
    virtual ~VirtLiquidCrystal(){ }

    virtual void init(uint8_t lcd_cols, uint8_t lcd_rows, uint8_t charsize = LCD_5x8DOTS)
    {
        _cols = lcd_cols;
        _rows = lcd_rows;

        _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;

        if (_rows > 1)
        {
            setBitFlag(_displayfunction, LCD_2LINE);
        }

        if ((charsize != LCD_5x8DOTS) && (_rows == 1))
        {
            setBitFlag(_displayfunction, LCD_5x10DOTS);
        }
    }

    virtual void init(uint8_t mode = LCD_4BITMODE)
    {
        uint8_t charsize = LCD_5x8DOTS;

        // if (_displayfunction & LCD_5x10DOTS)
        if (checkBitFlag(_displayfunction, LCD_5x10DOTS))
        {
            charsize = LCD_5x10DOTS;
        }

        _displayfunction = mode | LCD_1LINE | charsize;

        if (_rows > 1)
        {
            setBitFlag(_displayfunction, LCD_2LINE);
        }

        // _displayfunction = mode | ((_rows > 1) ? LCD_2LINE : LCD_1LINE) | charsize;
    }

    virtual void begin()
    {
        // put the LCD into 4 bit or 8 bit mode
        // if (! (_displayfunction & LCD_8BITMODE))
        if (!checkBitFlag(_displayfunction, LCD_8BITMODE))
        {

            // this is according to the Hitachi HD44780 datasheet
            // figure 24, pg 46
            // we start in 8bit mode, try to set 4 bit mode
            send(0x03, INIT_MODE);
            delayMicroseconds(4500); // wait min 4.1ms

            // // second try
            send(0x03, INIT_MODE);
            delayMicroseconds(4500); // wait min 4.1ms

            // third go!
            send(0x03, INIT_MODE);
            delayMicroseconds(150);

            // finally, set to 4-bit interface
            send(0x02, INIT_MODE);
            delayMicroseconds(150);
        }
        else
        {
            // this is according to the Hitachi HD44780 datasheet
            // page 45 figure 23

            // Send function set command sequence
            command(LCD_FUNCTIONSET | _displayfunction);
            delayMicroseconds(4500); // wait more than 4.1 ms

            // second try
            command(LCD_FUNCTIONSET | _displayfunction);
            delayMicroseconds(150);

            // third go
            command(LCD_FUNCTIONSET | _displayfunction);
            delayMicroseconds(150);
        }

        // set # lines, font size, etc.
        command(LCD_FUNCTIONSET | _displayfunction);

        // turn the display on with no cursor or blinking default
        _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
        display();
        clear();

        // Initialize to default text direction (for romance languages)
        _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
        // set the entry mode
        command(LCD_ENTRYMODESET | _displaymode);

        home();
    }

#if (ARDUINO < 100)
    virtual void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS, uint8_t mode = LCD_4BITMODE) {};
#else
    virtual void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS, uint8_t mode = LCD_4BITMODE) = 0;
#endif

    void clear()
    {
        command(LCD_CLEARDISPLAY); // clear display, set cursor position to zero
        delayMicroseconds(2000);   // this command takes a long time!
    }

    void clear(uint8_t rowStart, uint8_t colStart = 0, uint8_t colCnt = 255)
    {
        // Maintain input parameters
        rowStart = constrain(rowStart, 0, _rows - 1);
        colStart = constrain(colStart, 0, _cols - 1);
        colCnt = constrain(colCnt, 0, _cols - colStart);
        // Clear segment
        setCursor(colStart, rowStart);
        for (uint8_t i = 0; i < colCnt; i++)
            write(' ');
        // Go to segment start
        setCursor(colStart, rowStart);
    }

    void home()
    {
        command(LCD_RETURNHOME); // set cursor position to zero
        delayMicroseconds(2000); // this command takes a long time!
    }

    void noDisplay()
    {
        clearBitFlag(_displaycontrol, LCD_DISPLAYON);
        command(LCD_DISPLAYCONTROL | _displaycontrol);
    }

    void display()
    {
        setBitFlag(_displaycontrol, LCD_DISPLAYON);
        command(LCD_DISPLAYCONTROL | _displaycontrol);
    }

    // void display(lcd_mode_t mode);
    void noBlink()
    {
        clearBitFlag(_displaycontrol, LCD_BLINKON);
        command(LCD_DISPLAYCONTROL | _displaycontrol);
    }

    void blink()
    {
        setBitFlag(_displaycontrol, LCD_BLINKON);
        command(LCD_DISPLAYCONTROL | _displaycontrol);
    }

    void noCursor()
    {
        clearBitFlag(_displaycontrol, LCD_CURSORON);
        command(LCD_DISPLAYCONTROL | _displaycontrol);
    }

    void cursor()
    {
        setBitFlag(_displaycontrol, LCD_CURSORON);
        command(LCD_DISPLAYCONTROL | _displaycontrol);
    }

    void scrollDisplayLeft()
    {
        command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
    }

    void scrollDisplayRight()
    {
        command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
    }

    void leftToRight()
    {
        setBitFlag(_displaymode, LCD_ENTRYLEFT);
        command(LCD_ENTRYMODESET | _displaymode);
    }

    void rightToLeft()
    {
        clearBitFlag(_displaymode, LCD_ENTRYLEFT);
        command(LCD_ENTRYMODESET | _displaymode);
    }

    void autoscroll()
    {
        setBitFlag(_displaymode, LCD_ENTRYSHIFTINCREMENT);
        command(LCD_ENTRYMODESET | _displaymode);
    }

    void noAutoscroll()
    {
        clearBitFlag(_displaymode, LCD_ENTRYSHIFTINCREMENT);
        command(LCD_ENTRYMODESET | _displaymode);
    }

    void createChar(uint8_t location, uint8_t charmap[])
    {
        location &= 0x7; // we only have 8 locations 0-7
        command(LCD_SETCGRAMADDR | (location << 3));
        for (int i = 0; i < 8; i++)
        {
            write(charmap[i]);
        }
    }

#ifdef __AVR__
    void createChar(uint8_t location, const char *charmap);
#endif

    void setCursor(uint8_t col, uint8_t row, uint8_t offsets[])
    {
        if (row > _rows)
        {
            row = _rows - 1; // we count rows starting w/0
        }
        command(LCD_SETDDRAMADDR | (col + offsets[row]));
    }


    void printstr(const char c[])
    {
        // This function is not identical to the function used for "real" I2C displays
        // it's here so the user sketch doesn't have to be changed
        print(c);
    }


    virtual void setCursor(uint8_t col, uint8_t row);

    virtual void command(uint8_t value)
    {
        this->send(value, COMMAND);
    }

#if (ARDUINO < 100)
    virtual void write(uint8_t value){
  this->send(value, DATA);
}
#else
    virtual size_t write(uint8_t value){
  this->send(value, DATA);
  return 1; // assume success
}
#endif

#if (ARDUINO < 100)
    virtual void write4bits(uint8_t value) {};
    virtual void send(uint8_t value, uint8_t mode) {};
#else
    virtual void write4bits(uint8_t value) = 0;
    virtual void send(uint8_t value, uint8_t mode) = 0;
#endif

    bool getMode() { return readBitFlag(_displayfunction, LCD_8BITMODE); }
    uint8_t getCols() { return _cols; }
    uint8_t getRows() { return _rows; }

protected:
    uint8_t _cols = LCD_DEFAULT_COLS;
    uint8_t _rows = LCD_DEFAULT_ROWS;

    uint8_t _displayfunction;
    uint8_t _displaycontrol;
    uint8_t _displaymode;

    ////Unsupported API functions (not implemented in this library)
    // void setContrast(uint8_t new_val);
    // void setDelay(int,int); //for asynchroneous, no delay funcrion
    // uint8_t init_bargraph(uint8_t graphtype);
    // void draw_horizontal_graph(uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_col_end);
    // void draw_vertical_graph(uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_col_end);

    inline uint8_t status() { return _displayfunction; }
    inline void on() { display(); }
    inline void off() { noDisplay(); }
    inline void blink_on() { blink(); }
    inline void blink_off() { noBlink(); }
    inline void cursor_on() { cursor(); }
    inline void cursor_off() { noCursor(); }
    inline void printLeft() { rightToLeft(); }
    inline void printRight() { leftToRight(); }
    inline void shiftIncrement() { autoscroll(); }
    inline void shiftDecrement() { noAutoscroll(); }
    // virtual void write8bits(uint8_t value);
    // void writeNbits(uint8_t value, uint8_t numBits);
private:
    inline void setBitFlag(uint8_t &flagsGroup, const uint8_t &bitToSet) __attribute__((always_inline))
    {
        flagsGroup |= bitToSet;
    }

    inline void clearBitFlag(uint8_t &flagsGroup, const uint8_t &bitToClear) __attribute__((always_inline))
    {
        flagsGroup &= ~bitToClear;
    }

    inline bool readBitFlag(uint8_t &flagsGroup, const uint8_t &bitToRead) __attribute__((always_inline))
    {
        return flagsGroup & bitToRead;
    }

    inline void writeBitFlag(uint8_t &flagsGroup, const uint8_t &bitToSet, const bool &flagValue) __attribute__((always_inline))
    {
        if (flagValue)
            setBitFlag(flagsGroup, bitToSet);
        else
            clearBitFlag(flagsGroup, bitToSet);
    }

    inline bool checkBitFlag(uint8_t &flagsGroup, const uint8_t &bitToCheck) __attribute__((always_inline))
    {
        return (flagsGroup & (1 << bitToCheck)) ? true : false;
    }
};

#endif

// #define LCD_BRIGHT100 0x00
// #define LCD_BRIGHT75 0x01
// #define LCD_BRIGHT50 0x02
// #define LCD_BRIGHT25 0x03
// void bright (uint8_t brg) { command (LCD_FUNCTIONSET | _displayfunction | brg); }
//  lcd.print(F("Cursor"));
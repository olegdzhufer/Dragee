#include <stdio.h>
#include <string.h>

#include "LiquidCrystal.h"

LiquidCrystal::LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
                             uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                             uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                             uint8_t cols=LCD_DEFAULT_COLS, uint8_t rows=LCD_DEFAULT_ROWS,
                             uint8_t charsize = LCD_5x8DOTS, uint8_t mode = LCD_8BITMODE)
{
  LiquidCrystal_Base::init(cols, rows, charsize); //1
  init(mode, rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7);
}

LiquidCrystal::LiquidCrystal(uint8_t rs, uint8_t enable,
                             uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                             uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                             uint8_t cols=LCD_DEFAULT_COLS, uint8_t rows=LCD_DEFAULT_ROWS,
                             uint8_t charsize = LCD_5x8DOTS, uint8_t mode = LCD_8BITMODE)
{
  LiquidCrystal_Base::init(cols, rows, charsize);
  init(mode, rs, 255, enable, d0, d1, d2, d3, d4, d5, d6, d7);
}

LiquidCrystal::LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
                             uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                             uint8_t cols=LCD_DEFAULT_COLS, uint8_t rows=LCD_DEFAULT_ROWS,
                             uint8_t charsize = LCD_5x8DOTS, uint8_t mode = LCD_4BITMODE)
{
  LiquidCrystal_Base::init(cols, rows, charsize);
  init(mode, rs, rw, enable, d0, d1, d2, d3, 0, 0, 0, 0);
}

LiquidCrystal::LiquidCrystal(uint8_t rs, uint8_t enable,
                             uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                             uint8_t cols=LCD_DEFAULT_COLS, uint8_t rows=LCD_DEFAULT_ROWS,
                             uint8_t charsize = LCD_5x8DOTS, uint8_t mode = LCD_4BITMODE)
{
  LiquidCrystal_Base::init(cols, rows, charsize);
  init(mode, rs, 255, enable, d0, d1, d2, d3, 0, 0, 0, 0);
}

LiquidCrystal::~LiquidCrystal()
{
}

void LiquidCrystal::init(uint8_t mode, uint8_t rs, uint8_t rw, uint8_t enable,
                         uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                         uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
{
  _rs_pin = rs;
  _rw_pin = rw;
  _enable_pin = enable;

  _data_pins[0] = d0;
  _data_pins[1] = d1;
  _data_pins[2] = d2;
  _data_pins[3] = d3;
  _data_pins[4] = d4;
  _data_pins[5] = d5;
  _data_pins[6] = d6;
  _data_pins[7] = d7;

  LiquidCrystal_Base::init(mode); //2
}

void LiquidCrystal::init(uint8_t lcd_cols = LCD_DEFAULT_COLS, uint8_t lcd_rows=LCD_DEFAULT_ROWS, uint8_t charsize = LCD_5x8DOTS)
{
  LiquidCrystal_Base::init(lcd_cols, lcd_rows, charsize);
  
  LiquidCrystal_Base::init(getMode() ? LCD_8BITMODE : LCD_4BITMODE); 
  
  setRowOffsets(0x00, 0x40, 0x00 + lcd_cols, 0x40 + lcd_cols);

  begin();
}

void LiquidCrystal::begin()
{
  pinMode(_rs_pin, OUTPUT);
  // we can save 1 pin by not using RW. Indicate by passing 255 instead of pin#
  if (_rw_pin != 255)
  {
    pinMode(_rw_pin, OUTPUT);
  }
  pinMode(_enable_pin, OUTPUT);

  // Do these once, instead of every time a character is drawn for speed reasons.
  for (int i = 0; i < (getMode() ? 8 : 4); ++i)
  {
    pinMode(_data_pins[i], OUTPUT);
  }

  // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
  // according to datasheet, we need at least 40 ms after power rises above 2.7 V
  // before sending commands. Arduino can turn on way before 4.5 V so we'll wait 50
  delayMicroseconds(5000);
  // Now we pull both RS and R/W low to begin commands
  digitalWrite(_rs_pin, LOW);
  digitalWrite(_enable_pin, LOW);
  if (_rw_pin != 255)
  {
    digitalWrite(_rw_pin, LOW);
  }

  LiquidCrystal_Base::begin();
}

void LiquidCrystal::begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS, uint8_t mode = LCD_4BITMODE)
{
  LiquidCrystal_Base::init(cols, rows, charsize);
  setRowOffsets(0x00, 0x40, 0x00 + cols, 0x40 + cols);
  begin();
}

void LiquidCrystal::setRowOffsets(int row0, int row1, int row2, int row3)
{
  _row_offsets[0] = row0;
  _row_offsets[1] = row1;
  _row_offsets[2] = row2;
  _row_offsets[3] = row3;
}

/********** high level commands, for the user! */

void LiquidCrystal::setCursor(uint8_t col, uint8_t row)
{
  const size_t max_lines = SIZE_OF_ROW_OFFSETS;
  if (row >= max_lines)
  {
    row = max_lines - 1; // we count rows starting w/ 0
  }

  LiquidCrystal_Base::setCursor(col, row, _row_offsets);
}


/************ low level data pushing commands **********/

// write either command or data, with automatic 4/8-bit selection
void LiquidCrystal::send(uint8_t value, uint8_t mode)
{
  if (mode == INIT_MODE)
  {
     write4bits(value);
  }
  else
  {  
    digitalWrite(_rs_pin, mode);

    // if there is a RW pin indicated, set it low to Write
    if (_rw_pin != 255)
    {
      digitalWrite(_rw_pin, LOW);
    }

    // if (_displayfunction & LCD_8BITMODE)
    if (getMode())
    {
      write8bits(value);
    }
    else
    {
      write4bits(value >> 4);
      write4bits(value);
    }
  }
}

void LiquidCrystal::pulseEnable(void)
{
  digitalWrite(_enable_pin, LOW);
  delayMicroseconds(1);

  digitalWrite(_enable_pin, HIGH);
  delayMicroseconds(1); // enable pulse must be >450 ns

  digitalWrite(_enable_pin, LOW);
  delayMicroseconds(100); // commands need >37 us to settle
}

void LiquidCrystal::write4bits(uint8_t value)
{
  for (uint8_t i = 0; i < 4; i++)
  {
    digitalWrite(_data_pins[i], (value >> i) & 0x01);
  }

  pulseEnable();
}

void LiquidCrystal::write8bits(uint8_t value)
{
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(_data_pins[i], (value >> i) & 0x01);
  }

  pulseEnable();
}

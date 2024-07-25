#ifndef LIQUID_CRYSTAL_I2C_h
#define LIQUID_CRYSTAL_I2C_h

#if (ARDUINO < 10000)
#include <../Wire/Wire.h>
#else
#include <Wire.h>
#endif
#include "LiquidCrystal_Base.h"

// flags for backlight control
#define LCD_BACKLIGHT 0x08 //0b00001000
#define LCD_NOBACKLIGHT 0x00

#define En 0b00000100  // Enable bit B00000100
#define Rw 0b00000010  // Read/Write bit B00000010
#define Rs 0b00000001   // Register select bit #define Rs B00000001 

#define LCD_DEFAULT_ADDR 0x27 // Default I2C address


class LiquidCrystal_I2C : public LiquidCrystal_Base {
public:
	LiquidCrystal_I2C()=default;
	LiquidCrystal_I2C(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows, uint8_t charsize = LCD_5x8DOTS);
	
	~LiquidCrystal_I2C();

	virtual void init(uint8_t mode = LCD_4BITMODE);
	virtual void init(uint8_t lcd_addr, uint8_t lcd_cols,  uint8_t lcd_rows, uint8_t charsize = LCD_5x8DOTS);
	virtual void begin();
	virtual void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS, uint8_t mode = LCD_4BITMODE);

	void setCursor(uint8_t col, uint8_t row);
	void noBacklight();
	void backlight();
	bool getBacklight();

	// Compatibility API function aliases
	void setBacklight(uint8_t new_val);	// alias for backlight() and nobacklight()
	void load_custom_character(uint8_t char_num, uint8_t *rows);	// alias for createChar()
	void printstr(const char[]);

	virtual void write4bits(uint8_t value);

private:
	void send(uint8_t value, uint8_t mode);
	void expanderWrite(uint8_t _data);
	void pulseEnable(uint8_t _data);
	uint8_t _addr = LCD_DEFAULT_ADDR;
	uint8_t _backlightval = LCD_NOBACKLIGHT;
};

#endif 

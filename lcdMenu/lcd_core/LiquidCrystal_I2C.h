#ifndef LIQUID_CRYSTAL_I2C_h
#define LIQUID_CRYSTAL_I2C_h

#if (ARDUINO < 100)
#include <../Wire/Wire.h>
#else
#include <Wire.h>
#endif

#include "VirtLiquidCrystal.h"

// flags for backlight control
#define LCD_BACKLIGHT 0x08 //0b00001000
#define LCD_NOBACKLIGHT 0x00

#define En 0b00000100  // Enable bit B00000100
#define Rw 0b00000010  // Read/Write bit B00000010
#define Rs 0b00000001   // Register select bit #define Rs B00000001 

#define LCD_DEFAULT_ADDR 0x27 // Default I2C address


class LiquidCrystal_I2C : public VirtLiquidCrystal {
public:
	LiquidCrystal_I2C()=default;

	LiquidCrystal_I2C(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows){
		this->init(lcd_addr, lcd_cols, lcd_rows, LCD_5x8DOTS);
	}


	~LiquidCrystal_I2C(){}

	virtual void init(uint8_t mode = LCD_4BITMODE)
	{
		_backlightval = LCD_NOBACKLIGHT;
		VirtLiquidCrystal::init(mode);
		begin();
	}


	virtual void init(uint8_t lcd_addr, uint8_t lcd_cols,  uint8_t lcd_rows, uint8_t charsize = LCD_5x8DOTS)
	{
		_addr = lcd_addr;
		_backlightval = LCD_NOBACKLIGHT;
		VirtLiquidCrystal::init(lcd_cols, lcd_rows, charsize);
	}	


	virtual void begin()
	{
		Wire.begin();
	// SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
	// according to datasheet, we need at least 40ms after power rises above 2.7V
	// before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
	delay(50);
	
	// wire->beginTransmission(_LCDSlaveAddresI2C);
	// I2CReturnCode = wire->endTransmission();
	// if (I2CReturnCode!= 0)

	// Now we pull both RS and R/W low to begin commands
	expanderWrite(_backlightval); // reset expanderand turn backlight off (Bit 8 =1)
	delay(1000);

	VirtLiquidCrystal::begin();
	backlight();
	}

	
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
	uint8_t expanderWrite(uint8_t _data);
	void pulseEnable(uint8_t _data);
	uint8_t _addr = LCD_DEFAULT_ADDR;
	uint8_t _backlightval = LCD_NOBACKLIGHT;
};


#endif 

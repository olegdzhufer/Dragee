
// //~ ******************************************************************** */

// LiquidCrystal_I2C::LiquidCrystal_I2C(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows)
// {

// 	this->init(lcd_addr, lcd_cols, lcd_rows, LCD_5x8DOTS);
// }

// LiquidCrystal_I2C::~LiquidCrystal_I2C()
// {
// }

// //calls firts
// void LiquidCrystal_I2C::init(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows, uint8_t charsize)
// {

	
// }

// //calls second
// void LiquidCrystal_I2C::init(uint8_t mode )
// {
	
// }

// //last
// void LiquidCrystal_I2C::begin()
// {
	
// }

// //calls 1 and 2 inits
// void LiquidCrystal_I2C::begin(uint8_t cols, uint8_t rows, uint8_t charsize, uint8_t mode)
// {
// 	init(_addr, cols, rows, charsize);
// 	init(mode);
// }


// /********** high level commands, for the user! */

// void LiquidCrystal_I2C::setCursor(uint8_t col, uint8_t row)
// {
// 	uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};
// 	VirtLiquidCrystal::setCursor(col, row, row_offsets);
// }

// // Turn the (optional) backlight off/on
// void LiquidCrystal_I2C::noBacklight(void)
// {
// 	_backlightval = LCD_NOBACKLIGHT;
// 	expanderWrite(0);
// }

// void LiquidCrystal_I2C::backlight(void)
// {
// 	_backlightval = LCD_BACKLIGHT;
// 	expanderWrite(0);
// }
// bool LiquidCrystal_I2C::getBacklight()
// {
// 	return _backlightval == LCD_BACKLIGHT;
// }


// /************ low level data pushing commands **********/

// // write either command or data
// void LiquidCrystal_I2C::send(uint8_t value, uint8_t mode)
// {
	
// 	uint8_t lownib = (value << 4) & 0xf0; // performs a bitwise AND with 0xf0 (which is 11110000 in binary)

// 	if (mode == INIT_MODE)
// 	{
// 		mode = COMMAND;
// 	}
// 	else
// 	{
// 		if (mode == DATA)
// 		{
// 			mode = Rs;
// 		}
		
// 		uint8_t highnib = value & 0xf0; // & 1111 0000
// 		write4bits((highnib) | mode);
// 	}

// 	write4bits((lownib) | mode);
// }

// void LiquidCrystal_I2C::write4bits(uint8_t value)
// {
// 	expanderWrite(value);
// 	pulseEnable(value);
// }

// uint8_t LiquidCrystal_I2C::expanderWrite(uint8_t _data)
// {
// 	 uint8_t status = 0;

// 	Wire.beginTransmission(_addr);
// #if (ARDUINO < 100)
//       Wire.send(_data | _backlightval);
// #else
//       Wire.write(_data | _backlightval); //	Wire.write((int)(_data) | _backlightval);
// #endif
// 	status = Wire.endTransmission();
// 	// return ((status == 0));
// 	// return (ret == 0) ? true : false; //false if error
// 	return status;
// }

// void LiquidCrystal_I2C::pulseEnable(uint8_t _data)
// {
// 	expanderWrite(_data | En); // En high
// 	delayMicroseconds(1);	   // enable pulse must be >450ns

// 	expanderWrite(_data & ~En); // En low
// 	delayMicroseconds(50);		// commands need > 37us to settle
// }

// void LiquidCrystal_I2C::load_custom_character(uint8_t char_num, uint8_t *rows)
// {
// 	createChar(char_num, rows);
// }

// void LiquidCrystal_I2C::setBacklight(uint8_t new_val)
// {
// 	if (new_val)
// 	{
// 		backlight(); // turn backlight on
// 	}
// 	else
// 	{
// 		noBacklight(); // turn backlight off
// 	}
// }

// void LiquidCrystal_I2C::printstr(const char c[])
// {
// 	// This function is not identical to the function used for "real" I2C displays
// 	// it's here so the user sketch doesn't have to be changed
// 	print(c);
// }
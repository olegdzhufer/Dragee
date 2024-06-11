#ifndef EncMenu_h
#define encMenu_h

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "MenuTypes.h"

#ifndef LCD_ROW_COUNT
#define LCD_ROW_COUNT 4
#endif

#ifndef LCD_COL_COUNT
#define LCD_COL_COUNT 20
#endif

#ifndef MAX_SCREENS
#define MAX_SCREENS 9 //was 6
#endif

#ifndef MAX_LINES
#define MAX_LINES 10 //was 6
#endif

#define DEFAULT_LINE 0

#define START_BAR_POSITION 8 // to do

#ifndef BAR_END_POSITION
#define BAR_END_POSITION LCD_COL_COUNT - 2 // 18
#endif

#define IND_POSITION LCD_COL_COUNT - 3 // 17 //to do
#define SCREEN_NUMBER_POS LCD_COL_COUNT - 2

#define DEFAULT_BACKLIGHT_TIMEOUT 30000 // 30 sec


/**
 * @class Menu
 */
class Menu
{
private:
   LiquidCrystal_I2C *_lcd;

   uint8_t const static Screens = (MAX_SCREENS+1);
   uint8_t const static Lines = (MAX_LINES+1);

   uint8_t focuce = 1;
   int8_t active_focuce = focuce;
   uint8_t scr_num = 0; // Focus variables(active line), screen numbers,
   uint16_t *printed_lines_indicator[3] = {NULL, NULL, NULL}; // Array of pointers to current printed values
   uint8_t rows_to_update = LCD_ROW_COUNT - 1;
   
  // String screen[Screens][Lines];                             // Array of menu titles
   MenuLine_t lines[Screens][Lines];    // Array of line_value pointers (changing value at the end of the line)

   char cursor_icon = 0x7E; //->
   char edit_cursor_icon = '>';
   char screen_ind_icon = '#';
   uint32_t backlight_timeout = DEFAULT_BACKLIGHT_TIMEOUT; // 30 sec default

public:
   Menu(LiquidCrystal_I2C *lcd);

   MenuFlags mFlags = {};

   pointf_t pointf1[Screens][Lines]; // = {{NULL}}; // Array of pointers to the first attached function
   pointf_t pointf2[Screens][Lines]; // = {{NULL}}; // Array of pointers to the second attached function
   pointf_t pointf3[Screens][Lines]; // = {{NULL}}; // Array of pointers to the third attached function for encoder press button

   void *obj_indicator[Screens][Lines];// = {{NULL}};
   obj_pointf_t obj_pointf1[Screens][Lines]; // = {{NULL}};
   obj_pointf_t obj_pointf2[Screens][Lines]; // = {{NULL}};
   obj_pointf_t obj_pointf3[Screens][Lines]; // = {{NULL}};

   uint32_t backlight_timer = 0;
   
   void ResetMenu();

   /**
    * @fn SetLineValues
    * @brief Set the screen number, line, menu item name and variable to display at the end of the line
    * @param scr  screen number
    * @param line screen line
    * @param item_name menu item name
    * @param ind  variable to display
    */
   // void SetLineValues(uint8_t scr, uint8_t line, String item_name, uint16_t* ind, line_t line_type = NORMAL);
   void SetLineValues(uint8_t scr, uint8_t line, String item_name, void* ind_val, line_value_t val_type = U16_t, line_t line_type = NORMAL);

   //void SetLineValuesFromStruct(uint8_t scr, uint8_t line, String item_name, void* ind, line_t line_type = NORMAL);

   /**
    * @fn SetLineValues
    * @brief Set the screen number, line, menu item name
    * @param scr  screen number
    * @param line screen line
    * @param item_name menu item name
    */
   void SetLineValues(uint8_t scr, uint8_t line, String item_name, line_t line_type = NO_VALUE);

   /**
    * @fn SetFunc1
    * @brief Installing the first attached function
    * @param scr  screen number
    * @param line screen line
    * @param p function to attach
    */
   void SetFunc1(uint8_t scr, uint8_t line, void *p);
   void SetFunc1(uint8_t scr, uint8_t line, void (*listener)(void *object), void *object);

   /**
    * @fn SetFunc2
    * @brief Installing the second attached function
    * @param scr  screen number
    * @param line screen line
    * @param p function to attach
    */
   void SetFunc2(uint8_t scr, uint8_t line, void *p);
   void SetFunc2(uint8_t scr, uint8_t line, void (*listener)(void *object), void *object);

   /**
    * @fn SetFunc3
    * @brief Installing the third attached function
    * @param scr  screen number
    * @param line screen line
    * @param p function to attach
    */
   void SetFunc3(uint8_t scr, uint8_t line, void *p);
   void SetFunc3(uint8_t scr, uint8_t line, void (*listener)(void *object), void *object);

   /**
    * @fn ActivateBacklightTimer
    * @brief Activate lcd backlight timer for menu
    */
   void ActivateBacklightTimer();

   /**
    * @fn SetBacklightTimeout
    * @brief Activate lcd backlight timer for menu and set its timeout.
    * Default timeout is:
    *          DEFAULT_BACKLIGHT_TIMEOUT 30000
    */
   void SetBacklightTimeout(uint32_t timeout);

   /**
    * @fn SetLineType
    * @brief Set line type to change its display settings
    * @param scr  screen number
    * @param line screen line to change type
    * @param line_type new line type
    *
    * Possible types:
    *      NORMAL = 0; - by default
    *      BOOL = 1;   - showing only "ON" or "OFF"
    *      BARGRAPH = 2; - percentage progress bar
    *      NO_VALUE = 3; - for lines without line_value value
    */
   // void SetLineType(uint8_t scr, uint8_t line, line_t line_type);
   //void SetLineType(MenuLine_t *line, line_t line_type);

   bool CheckFunction1();
   
   /**
    * @fn RunFunction1
    * @brief Run the first attached function (if it exist)
    */
   void RunFunction1();

   bool CheckFunction2();

   /**
    * @fn RunFunction2
    * @brief Run the second attached function (if it exist)
    */
   void RunFunction2();

   /**
    * @fn CheckFunction3
    * @brief Return true if the third attached function exist
    */
   bool CheckFunction3();

   /**
    * @fn RunFunction3
    * @brief Run the third attached function (if it exist)
    */
   bool RunFunction3();


   /**
    * @fn SetMenuActive
    * @brief Activate update menu flag
    */
   void SetMenuActive();
   void SetMenuUpdate();

   /**
    * @fn GetScreen
    * @brief Return screen number
    * @return Current scr_num
    */
   uint8_t GetScreen();

   /**
    * @fn GetLine
    * @brief Return current menu line
    * @return focuce
    */
   uint8_t GetLine();

   /**
    * @fn MakeMenuLine
    * @brief Drawing the menu line on the screen, processing the internal logic of the menu.
    * @param scr   screen number index
    * @param line_index  screen line index
    */
   void MakeMenuLine(uint8_t scr, uint8_t line_index);
   void MakeMenuCurrentLine();

   void MenuNextLine();
   void MenuPrevLine();
   void MenuNextScreen();
   void MenuPrevScreen();
   void MenuUpdate();
   void MenuSwitchToScreen(uint8_t scr);
   void MenuHandler();


private:
   /**
    * @fn EncMenu
    * @brief Drawing the menu on the screen, processing the internal logic of the menu.
    *
    * @param line_target  responsible for switching the focus row (active line)
    * @param screen_target  for switching the current screen
    *
    * @example Example:
    * @(1-switching to the next screen/line, 0-previous screen/line, 2-updating the current screen without changes)
    * EncMenu (1, 2); - move to next line, EncMenu (0, 2); - move to previous line,
    * EncMenu (2, 1); - move to the next screen, EncMenu (2, 0); - move to the previous screen.
    */
   void EncMenu(LINE_TARGET_TYPE line_target, MENU_TARGET_TYPE screen_target);


   /**
    * @fn GetLinesCount
    * @brief Return number of current menu lines
    * @param scr current menu
    * @return focuce
    */
   uint8_t GetLinesCount(uint8_t scr);
   uint8_t GetScreensCount();

   /**
    * @fn MenuClearLine
    * @brief Clearing only one lcd line
    * @param row lcd line to be cleared
    */
   void MenuClearLine(uint8_t row);

   /**
    * @fn PrintOneLine
    * @brief Printing only one lcd line
    * @param scr   screen number index
    * @param line_index  screen line index
    * @param line_to_print lcd line number to print
    */
   void PrintOneLine(uint8_t scr, uint8_t line_index, uint8_t line_to_print);

   void ScreensNavigation(LINE_TARGET_TYPE line_target, MENU_TARGET_TYPE screen_target);

   void DisplayFocuceLines(int8_t *focuce_pos);

   void DisplayCurrentCursor(int8_t focuce_pos);

   void setup_progressbar();

   /**
    * @fn draw_progressbar progression.
    *
    * @param percent percentage value to be shown as bar
    * @param start_row which element of menu
    * @param start_col start point of bar
    */
   void draw_progressbar(uint16_t percent, byte start_row, byte start_col);
   void GetLineValueType(uint8_t scr, uint8_t line);
   //void GetLineValueType(MenuLine_t *line_ptr);
};

#endif // MakeMenu_h

#pragma once

#include <Arduino.h>

typedef union valuetype
{
    char *string;
    bool Bool;
    uint8_t u8;
    int8_t s8;
    uint16_t u16;
    int16_t s16;
    uint32_t u32;
    int32_t s32;
    uint64_t u64;
    int64_t s64;
    float f32;
    const char *stringconstant;
} value_t;

typedef enum
{
    PREVIOS_LINE,
    NEXT_LINE,
    UPDATE_LINE
} LINE_TARGET_TYPE;

typedef enum
{
    PREVIOS_SCREEN,
    NEXT_SCREEN,
    UPDATE_SCREEN
} MENU_TARGET_TYPE;

typedef enum
{
    NO_VALUE,
    NORMAL,
    SWITCH,
    BARGRAPH,
    NAVIGATION
} line_t;

typedef enum
{
    NO_TYPE,
    BOOL_t,
    U8_t,
    U16_t,
    U32_t
} line_value_t; 

struct MenuFlags
{
    bool menuActive_f : 1;
    bool menuUpdate_f : 1;
    bool lineSelected : 1;
    bool bar_chars_inited : 1;
    bool num_chars_inited : 1;
    bool backlight_enabled : 1;
};

/**
 *  @brief Struct (Array) of line_value pointers (changing value at the end of the line)
 */
struct MenuLine
{
    String line_text;  // const char     *DisplayText;
    value_t *line_value; // uint8_t  Linetype;
    line_value_t val_type;
    line_t line_type;
    // struct MenuLine *nextline; //line_struct
};
typedef struct MenuLine MenuLine_t;

typedef void (*pointf_t)();
typedef void (*obj_pointf_t)(void *);

/*

struct
{
   void  (*callfunc)(void *Socket);          // Function to call and arguments
   U8 FunctionWorks;                         // 0 = Not tested, 1 = failed, 2 = Works
} Dynamic;

struct
{
   void  (*callfunc)(void *Socket, U32 Par); // Function to call and arguments
   U32 Parameter;                            // Parameter to menu function
   U8 FunctionWorks;                         // 0 = Not tested, 1 = failed, 2 = Works
} DynamicParameter;

struct menu_group_struct
{
   U32 MagicNumber;                    // A magic number to detect validity of data
   char  *Name;                        // Menu group name
   struct menu_struct *first_menu;     // Pointer to first menu in this group, zero if none
   struct menu_struct *last_menu;      // Pointer to last menu in this group, zero if none
   struct menu_group_struct *prev;     // Pointer to previus group, zero if first
   struct menu_group_struct *next;     // Pointer to next group, zero if last.
   struct button_struct *first_button; // Pointer to first button in group
   struct button_struct *last_button;  // Pointer to last button in group
};


*/

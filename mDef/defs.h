#ifndef defs_h
#define defs_h

#include <Arduino.h>

#ifndef Refresh
#define noRefresh       false          // Set auto refresh OFF
#define Refresh         true           // Set auto refresh ON
#endif

#ifndef ON
#define ON              true           // Set the Relay ON
#define OFF             false          // Set the Relay OFF
#endif

#if defined(ESP8266) || defined(ESP32)
#define GET_FREE_HEAP() ESP.getFreeHeap()
#else
#define GET_FREE_HEAP()
#endif


#define LCD_ADDR_DEFAULT 0x27
#define LCD_COLS 20
#define LCD_ROWS 4


// #define PGM_VAL(T, name, val) const T name PROGMEM = val;

// #define PGM_STRUCT(T, name, ...) const T name PROGMEM = {__VA_ARGS__};


// #define PGM_STR(name, str) const char name[] PROGMEM = str;

// #define _MAKE_STR(N, i, name, val) const char name##_##i[] PROGMEM = val;
// #define _MAKE_LIST(N, i, name, val) name##_##i,

/* #define PGM_STR_LIST(name, ...)          \ */
/*     PU_FOR(_MAKE_STR, name, __VA_ARGS__) \ */
/*     const char* const name[] PROGMEM = {PU_FOR(_MAKE_LIST, name, __VA_ARGS__)}; */

/* #define PGM_STR_LIST_OBJ(name, ...)        \ */
/*     PGM_STR_LIST(name##_list, __VA_ARGS__) \ */
//     pgm::StringList name(name##_list, sizeof(name##_list) / sizeof(const char*));

// #define MAKE_STR_LIST(name) pgm::StringList(name, sizeof(name) / sizeof(const char*));


// #define PGM_ARRAY(T, name, ...) const T name[] PROGMEM = {__VA_ARGS__};

// #define PGM_ARRAY_LIST(T, name, ...) const T* const name[] PROGMEM = {__VA_ARGS__};

// #define MAKE_ARRAY(T, name) pgm::Array<T>(name, sizeof(name) / sizeof(T));

/*     PGM_ARRAY(T, name##_arr, __VA_ARGS__) \ */
//     pgm::Array<T> name(name##_arr, sizeof(name##_arr) / sizeof(T));


// #ifndef FSTR
// #define FSTR const __FlashStringHelper*
// #endif

// #ifndef FPSTR
// #define FPSTR(x) (reinterpret_cast<FSTR>(x))
// #endif


#endif
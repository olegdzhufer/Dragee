#ifndef types_h
#define types_h

#include <Arduino.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;

// typedef bool b8;
typedef char c8;

typedef u8 flag_t;

typedef struct FLAG_PACK
{
    bool flag1:1;
    bool flag2:1;
    bool flag3:1;
    bool flag4:1;
    bool flag5:1;
    bool flag6:1;
    bool flag7:1;
    bool flag8:1;
} flag_pack_t;

typedef void (*func_p)();
typedef void (*funcVoid_p)(void);
typedef void (*funcInt_p)(u16);
typedef void (*funcStr_p)(c8);

typedef void (*obj_func_p)(void *);

#endif
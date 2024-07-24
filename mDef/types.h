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
typedef c8* c8_p;

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

#ifdef __AVR__
typedef void (*func_t)();//why
typedef void (*funcVoid_t)(void);//why esp compiler....why...vva

typedef void (*func_p)();
typedef void (*funcVoid_p)(void);
typedef void (*funcUInt_p)(u16);
typedef void (*funcInt_p)(i16);
typedef void (*funcStr_p)(c8_p);
typedef void (*obj_func_p)(void *);
#else

typedef void (*func_t)();
typedef void (*funcVoid_t)(void);

typedef std::function<void()> func_p;
typedef std::function<void(void)> funcVoid_p;
typedef std::function<void(u16)> funcUInt_p;
typedef std::function<void(i16)> funcInt_p;
typedef std::function<void(c8_p)> funcStr_p;
typedef std::function<void(void*)> obj_func_p;
#endif

#endif
#ifndef defs_h
#define defs_h

#ifndef Refresh
#define noRefresh       false          // Set auto refresh OFF
#define Refresh         true           // Set auto refresh ON
#endif

#ifndef ON
#define ON              true           // Set the Relay ON
#define OFF             false          // Set the Relay OFF
#endif

#define DEBUG 1

#if defined(DEBUG) && DEBUG > 0
 #define DEBUG_PRINT(fmt, args...) fprintf(stderr, "DEBUG: %s:%d:%s(): " fmt, \
    __FILE__, __LINE__, __func__, ##args)
#else
 #define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif

#endif
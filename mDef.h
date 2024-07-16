#ifndef MDEF_h
#define MDEF_h

#if defined(ARDUINO) && (ARDUINO >= 100)
	#include <Arduino.h>
#else
	#include <WProgram.h>
#endif

#include <pgmspace.h>

#include "pins.h"
#include "defs.h"
#include "types.h"
#include "debugPrint.h"
#include "sts.h"

#endif

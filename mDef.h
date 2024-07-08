#ifndef MDEF_h
#define MDEF_h

#if defined(ARDUINO) && (ARDUINO >= 100)
	#include <Arduino.h>
#else
	#include <WProgram.h>
#endif

#include <pgmspace.h>

#include "mDef/pins.h"
#include "mDef/defs.h"
#include "mDef/types.h"
#include "mDef/debugPrint.h"
#include "mDef/sts.h"

#endif

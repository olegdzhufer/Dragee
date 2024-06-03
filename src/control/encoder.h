#ifndef ENC_DEF_H
#define ENC_DEF_H

#include <EncButton.h>
#include "mDef.h"

void encSetup();
void encLoop();
void encSetCallback(void (*callback)(int));



#endif
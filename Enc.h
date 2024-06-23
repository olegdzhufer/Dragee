#ifndef ENC_H
#define ENC_H

#include <Arduino.h>
#include <EncButton.h>

#include "settings.h"


class EncoderWork {

  EncoderWork() {}

private:
  EncButton* enc;
  void (*callBackFuncClick)() = NULL;
  void (*callBackFuncRight)() = NULL;
  void (*callBackFuncLeft)() = NULL;

  //  public:
  //    set
};

#endif
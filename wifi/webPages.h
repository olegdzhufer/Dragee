#ifndef webPages_h
#define webPages_h

#include <Arduino.h>
#include "settings.h"



String calculateWIFIsignal() {
  float Signal = WiFi.RSSI();
  Signal = 90 / 40.0 * Signal + 212.5;
  if (Signal > 100)
    Signal = 100;
  return " " + String(Signal, 0) + "%";
}

#endif
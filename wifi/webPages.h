#ifndef webPages_h
#define webPages_h

#include <Arduino.h>
#include "settings.h"


const char* serverName = "dragee"; //  http://dragee.local/ 

const char* serverLinkApi = "api.thingspeak.com";
const char* serverIPApi = "184.106.153.149";

// NTP server to request epoch time
const char* ntpServer = "pool.ntp.org";
const char* timezone   = "EET-2EEST,M3.5.0/3,M10.5.0/4";

String sitetitle            = "Dragee Machine IoT";



String calculateWIFIsignal() {
  float Signal = WiFi.RSSI();
  Signal = 90 / 40.0 * Signal + 212.5;
  if (Signal > 100)
    Signal = 100;
  return " " + String(Signal, 0) + "%";
}

#endif
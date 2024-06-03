#include <Arduino.h>
#include <pgmspace.h>

#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#include <esp_task_wdt.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include "src/ESPAsyncTCP/ESPAsyncTCP.h"
#endif
#include <ESPAsyncWebServer.h>
#include <ThingSpeak.h>
#include <OpenTherm.h>

void siteLoop();
void siteSetup();
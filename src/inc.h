#ifndef INC_LOCAL_H
#define INC_LOCAL_H

#include <Arduino.h>

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#else
#include <WiFi.h>
#include <HTTPClient.h>
#endif

#include <esp_task_wdt.h>
#include <WiFiClient.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MenuLib.h>
#include <BigNumbers_I2C.h>

#include <OneWire.h>
#include <DallasTemperature.h>
#include <ThingSpeak.h>
#include <OpenTherm.h>

#include <EncButton.h>

#include "mDef.h"
#include "pins.h"
#include "menuLCD/menu.h"
#include "wifi/wifi.h"

#endif
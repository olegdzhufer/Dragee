#ifndef WIFI_CONF_H
#define WIFI_CONF_H

#include <Arduino.h>


#include <WiFi.h>
#include <AsyncTCP.h>
#include <esp_task_wdt.h>
#include <ESPAsyncWebServer.h>
#include <ThingSpeak.h>
#include <OpenTherm.h>

#include <HTTPClient.h>

#include <WiFiClient.h>

#include "mDef.h"

#define SSDI_C "realme 11"
#define PASSWORD_C "a4na8x5u"


extern const char index_html[];
extern const char css[];
extern const char js[];
extern const int favico_ico_length;
extern const byte favico_ico[];

void siteSetup();
void siteLoop();


void setupWifi()
{
    WiFi.mode(WIFI_AP);
    WiFi.begin(SSDI_C, PASSWORD_C);
    Serial.print("Connecting.");

    // int retry_count = 0
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
        // if (++retry_count > 1000) ESP.restart();
        // spinner();
    }
    Serial.println();
    Serial.println("\n\nWiFi connected\n\n");
    Serial.print("ESP IP Address: http://");
    Serial.println(WiFi.localIP());
}

#endif
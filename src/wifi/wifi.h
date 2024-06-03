#ifndef WIFI_CONF_H
#define WIFI_CONF_H

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#else
#include <WiFi.h>
#include <HTTPClient.h>
#endif

#include <WiFiClient.h>

#include "mDef.h"

const char *ssid = "AsusLyra";
const char *password = "123456qwerty";


void setupWifi()
{
    WiFi.mode(WIFI_AP);
    WiFi.begin(ssid, password);
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
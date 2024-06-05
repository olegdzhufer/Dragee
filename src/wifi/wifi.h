#ifndef WIFI_CONF_H
#define WIFI_CONF_H


#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>

#include <esp_task_wdt.h> //?

#include <ESPAsyncWebServer.h>
// #include <ThingSpeak.h>
// #include <OpenTherm.h>
#include <HTTPClient.h>
#include <WiFiClient.h>

#include <SPIFFS.h>
#include <LittleFS.h>

#include "mDef.h"
// #include "relayTemp/tempSensors.h"

#define SSDI_C "Susid"
#define PASSWORD_C "lvbnhbr2016"

AsyncWebServer server(80); 

void handleRoot(AsyncWebServerRequest *request) {
  request->send(SPIFFS, "/index.html", "text/html");
}

void setupWifi_AP() {
  WiFi.mode(WIFI_AP);
  WiFi.begin(SSDI_C, PASSWORD_C);
  
  DEBUG_PRINT("Connecting.");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("\n\nWiFi connected\n\n");
  Serial.print("ESP IP Address: http://");
  Serial.println(WiFi.localIP());

  if (!SPIFFS.begin(true)) {
    Serial.println("An error occurred while mounting SPIFFS");
    return;
  }

  server.on("/", HTTP_GET, handleRoot);

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });

  server.begin();
  Serial.println("HTTP server started");
}




#endif

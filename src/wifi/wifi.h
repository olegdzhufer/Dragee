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
#include <SPIFFS.h>
#include "mDef.h"
#include <LittleFS.h>

#define SSDI_C "Susid"
#define PASSWORD_C "lvbnhbr2016"

AsyncWebServer server(80); // Використовуємо AsyncWebServer замість WebServer

void handleRoot(AsyncWebServerRequest *request) {
  // Відправлення вмісту файлу index.html як відповідь на запит
  request->send(SPIFFS, "/index.html", "text/html");
}

void setupWifi() {
  WiFi.mode(WIFI_AP);
  WiFi.begin(SSDI_C, PASSWORD_C);
  Serial.print("Connecting.");

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

  // Призначення обробника запиту на кореневий шлях
  server.on("/", HTTP_GET, handleRoot);

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });

  // Запуск веб-сервера
  server.begin();
  Serial.println("HTTP server started");
}


void wifiLoop() {
  
}

#endif

#ifndef FILE_SYS_H
#define FILE_SYS_H


#include <Arduino.h>
#include <LittleFS.h>
#include "settings.h"
using namespace fs;


void startLITLLFS() {
  if (!LittleFS.begin()) {
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }
  server.on("/change_mode", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/change_mode.html", String(), false);
  });

  server.on("/graphs", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/graph.html", String(), false);
  });

  server.on("/schedule", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/schedule.html", String(), false);
  });

  server.on("/setup", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/setup.html", String(), false);
  });

  server.on("/help", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/help.html", String(), false);
  });
}

#endif
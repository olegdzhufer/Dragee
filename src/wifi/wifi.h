#ifndef WIFI_CONF_H
#define WIFI_CONF_H

#include <SPIFFS.h>
#include <LittleFS.h>

#include "mDef.h"
#include "secrets.h"

#define STATION_PORT 80

#define DEBUG_WIFI DEBUG_PRINT
#define DEBUGLN_WIFI DEBUG_PRINTLN

char ssid[] = SECRET_SSID;  
char pass[] = SECRET_PASS;  

AsyncWebServer local_server(STATION_PORT); 

void handleRoot(AsyncWebServerRequest *request) {
  request->send(SPIFFS, "/index.html", "text/html");
}

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

STATUS_t setupFS() {

  // Initialise SPIFFS, if this fails try .begin(true)
    // NOTE: I believe this formats it though it will erase everything on
    // spiffs already! In this example that is not a problem.
    // I have found once I used the true flag once, I could use it
    // without the true flag after that.
    bool spiffsInitSuccess = SPIFFS.begin(false) || SPIFFS.begin(true);
    if (!spiffsInitSuccess)
    {
        Serial.println("SPIFFS initialisation failed!");
        while (1)
            yield(); // Stay here twiddling thumbs waiting
        return FS_NOT_INITED;
    }
    Serial.println("\r\nInitialisation done.");
  return STATUS_OK;
}


void setupServer() {
  local_server.on("/", HTTP_GET, handleRoot);

  local_server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });


   // Receive an HTTP GET request
  // local_server.on("/on", HTTP_GET, [] (AsyncWebServerRequest *request) {
    // btnChangedFlag = true;
    // btnPressed = true;
    // request->send(200, "text/plain", "ok");
  // });
// 
  // Receive an HTTP GET request
  // local_server.on("/off", HTTP_GET, [] (AsyncWebServerRequest *request) {
    // btnChangedFlag = true;
    // btnReleased = true;
    // request->send(200, "text/plain", "ok");
  // });

//////////////////////////////////////

  // Send web page to client
  // local_server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            // { request->send_P(200, "text/html", index_html); });
// 
  // Receive an HTTP GET request
  // local_server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request)
            // {
    // btnChangedFlag = true;
    // btnPressed = true;
    // webChange = true;
    // request->send(200, "text/plain", "ok"); });


  local_server.onNotFound(notFound);
  local_server.begin();
  DEBUGLN_WIFI"HTTP local_server started");
}

STATUS_t setupWifi_AP() {
  WiFi.mode(WIFI_AP);
  WiFi.begin(SECRET_AP_SSID, SECRET_AP_PASS); //todo logic for deciding which ssid to use
  
  DEBUGLN_WIFI("Connecting ");

  // while (WiFi.status() != WL_CONNECTED) 
  // {
  //   delay(500);
  //   DEBUG_WIFI(".");
  // }

  DEBUGLN_WIFI("\n\nWiFi connected\n\n");
  DEBUGLN_WIFI("ESP IP Address: http://");
  DEBUGLN_WIFI(WiFi.localIP());

  STATUS_t sts = setupFS(); //todo another function  with wifi fs and local_server
  if (sts) {
    DEBUGLN_WIFI("FS setup failed");
    DEBUGLN_WIFI(__FILE__);
    return sts;
  }

  setupServer();

  return STATUS_OK;
}


#endif

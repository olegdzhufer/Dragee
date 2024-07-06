#include "ESPAsyncWebServer.h"
#ifndef serverHost_h
#define serverHost_h

#include <Arduino.h>
#include "settings.h"
#include "timerThermo.h"
#include "webPages.h"
#include "file_sys.h"
#include "btns.h"
#include <LittleFS.h>

using namespace fs;

#ifdef WEB_S

/**
  * @brief The name that will identify your device on the network
  * @todo move to wifi configuration file
  * @param DeviceName New device name
  */
void setupDeviceName(const char *DeviceName) {
#ifdef DEBUG_FUNC
  Serial.println(__func__);
#endif
  if (MDNS.begin(DeviceName)) {
    Serial.println("mDNS responder started");
    Serial.print("Device name: ");
    Serial.println(DeviceName);
    MDNS.addService("n8i-mlp", "tcp", 23);  // Add service
  } else {
    Serial.println("Error setting up MDNS responder");
  }
}


void serverHandlersSetup() {
#ifdef DEBUG_FUNC
  Serial.println(__func__);
#endif

  server.on("/heat_set", HTTP_GET, heatControl);
  server.on("/cold_set", HTTP_GET, coldControl);
  server.on("/fan_set", HTTP_GET, fanControl);
  server.on("/relayHeatState", HTTP_GET, relayHeatState);
  server.on("/relayCoolState", HTTP_GET, relayCoolState);
  server.on("/relayFanState", HTTP_GET, relayFanState);
}

void startServerHost() {
#ifdef DEBUG_FUNC
  Serial.println(__func__);
#endif
  setupDeviceName(serverName);
  serverHandlersSetup();
  server.begin();
}

#endif

#endif

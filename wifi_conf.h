#include "esp32-hal.h"
#include <sys/_stdint.h>
#ifndef WIFI_CONF_H
#define WIFI_CONF_H

#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>

#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <HTTPClient.h>

#include "settings.h"

#ifdef WIFI_S

void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info) {
#ifdef DEBUG_FUNC
  Serial.println(__func__);
#endif
  connections += 1;
  Serial.println("Connected to AP successfully!");
}

void WiFiGotIP(WiFiEvent_t event, WiFiEventInfo_t info) {
#ifdef DEBUG_FUNC
  Serial.println(__func__);
#endif
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info) {
#ifdef DEBUG_FUNC
  Serial.println(__func__);
#endif
  Serial.println("Disconnected from WiFi access point");
  Serial.print("WiFi lost connection. Reason: ");
  Serial.println(info.wifi_sta_disconnected.reason);
  Serial.println("Trying to Reconnect");
  WiFi.begin(ssid, password);
}

void setupAPMode() {
  WiFi.mode(WIFI_MODE_AP);
  WiFi.softAP(apssid, appassword);
  Serial.println("AP Mode Enabled.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
}

void initWiFi() {
#ifdef DEBUG_FUNC
  Serial.println(__func__);
#endif
  Serial.print("\r\nConnecting to: ");
  Serial.println(String(ssid));

  IPAddress primaryDNS(8, 8, 8, 8);  // Use Google as DNS


  WiFi.mode(WIFI_MODE_STA);

  WiFi.onEvent(WiFiStationConnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_CONNECTED);
  WiFi.onEvent(WiFiGotIP, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_GOT_IP);
  WiFi.onEvent(WiFiStationDisconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

  WiFi.begin(ssid, password);

  unsigned long startTime = millis();
  unsigned long timeout = 5000;

  while (WiFi.status() != WL_CONNECTED) {
    if (millis() - startTime > timeout) {
      setupAPMode();
      return;
    }
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nWiFi connected at: " + WiFi.localIP().toString());
  Serial.print("RRSI: ");
  Serial.println(WiFi.RSSI());
}

#endif

#endif

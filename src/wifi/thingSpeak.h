#ifndef WIFI_CONF_H
#define WIFI_CONF_H

#include "relayTemp/tempSensors.h"

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

#include <LittleFS.h>


#define SSDI_C "Shoko-cli_A"
#define PASSWORD_C "Shock2009"

unsigned long myChannelNumber = 2570068;
const char * myWriteAPIKey = "2KWEPCTBOYPEDPMW";

unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

extern const char index_html[];
extern const char css[];
extern const char js[];
extern const int favico_ico_length;
extern const byte favico_ico[];

void siteSetup();
void siteLoop();

AsyncWebServer server(80);

WiFiClient  client;

void setupWifi()
{   
 Serial.begin(115200);  
 WiFi.mode(WIFI_STA);   
 ThingSpeak.begin(client);
 IPAddress IP = WiFi.softAPIP();
 Serial.print("AP IP address: ");
 Serial.println(IP);

 temperatureSensor.begin();
 temperatureSensor.setResolution(12);
 temperatureSensor.requestTemperatures();
}

void loopWifi(){
    if ((millis() - lastTime) > timerDelay) {
    
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(SSDI_C, PASSWORD_C); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }
    temperature = readTemperatureSensor(temperatureSensor);
    Serial.println(temperature);

    int x = ThingSpeak.writeField(myChannelNumber, 1, temperature, myWriteAPIKey);

    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    lastTime = millis();
  }
}

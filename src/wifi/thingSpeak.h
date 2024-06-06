#ifndef WIFI_CONF_H
#define WIFI_CONF_H


// #include <Arduino.h>
// #include <WiFi.h>
// #include <AsyncTCP.h>
// #include <esp_task_wdt.h>
// #include <ESPAsyncWebServer.h>
// #include <ThingSpeak.h>
// #include <OpenTherm.h>
// #include <HTTPClient.h>
// #include <WiFiClient.h>

// #include <LittleFS.h>

#include "mDef.h"
#include "wifi.h"
#include "relayTemp/tempSensors.h"

#define THINGSPEAK_PORT 80

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

unsigned long thingSpeak_timer = 0;
unsigned long thingSpeak_delay = 30000;

// extern const char index_html[];
// extern const char css[];
// extern const char js[];
// extern const int favico_ico_length;
// extern const byte favico_ico[];

#define DEBUG_THINGSPEAK DEBUG_PRINT
#define DEBUGLN_THINGSPEAK DEBUG_PRINTLN

    // #define TS_OK_SUCCESS              200     // OK / Success
    // #define TS_ERR_BADAPIKEY           400     // Incorrect API key (or invalid ThingSpeak server address)
    // #define TS_ERR_BADURL              404     // Incorrect API key (or invalid ThingSpeak server address)
    // #define TS_ERR_OUT_OF_RANGE        -101    // Value is out of range or string is too long (> 255 bytes)
    // #define TS_ERR_INVALID_FIELD_NUM   -201    // Invalid field number specified
    // #define TS_ERR_SETFIELD_NOT_CALLED -210    // setField() was not called before writeFields()
    // #define TS_ERR_CONNECT_FAILED      -301    // Failed to connect to ThingSpeak
    // #define TS_ERR_UNEXPECTED_FAIL     -302    // Unexpected failure during write to ThingSpeak
    // #define TS_ERR_BAD_RESPONSE        -303    // Unable to parse response
    // #define TS_ERR_TIMEOUT             -304    // Timeout waiting for server to respond
    // #define TS_ERR_NOT_INSERTED        -401    // Point was not inserted (most probable cause is the rate limit of once every 15 seconds)


AsyncWebServer server(THINGSPEAK_PORT);
WiFiClient  speak_thing_client;

void setupWifi_STA()
{   
 WiFi.mode(WIFI_STA);   
 
 ThingSpeak.begin(speak_thing_client);

 IPAddress IP = WiFi.softAPIP();
 
 DEBUG_THINGSPEAK("AP IP address: ");
 DEBUGLN_THINGSPEAK(IP);
}


bool reconnect_STA()
{
      Serial.print("Attempting to connect");
      if(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, pass);
        while(WiFi.status() != WL_CONNECTED)
        {
          delay(500);
          DEBUG_THINGSPEAK(".");
        }
      } 
      DEBUGLN_THINGSPEAK("\nConnected.");
     DEBUGLN_THINGSPEAK();
      DEBUGLN_THINGSPEAK("ESP IP Address: http://");
      DEBUGLN_THINGSPEAK(WiFi.localIP());
      DEBUG_THINGSPEAK("RRSI: ");
      DEBUGLN_THINGSPEAK(WiFi.RSSI());
    return true;
}

bool check_connection_STA()
{
    if(WiFi.status() != WL_CONNECTED){
        return false;
    }else{
        return true;
    }
}

void loopThingSpeak(){
    if ((millis() - thingSpeak_timer) > thingSpeak_delay) {
    
    if (!check_connection_STA()) {
      reconnect_STA();
    }

    float temperature = readTemperatureSensor(temperatureSensor);
    //int writeFields(unsigned long channelNumber, const char * writeAPIKey)
     // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  // pieces of information in a channel.  Here, we write to field 1.
    int sts = ThingSpeak.writeField(myChannelNumber, 1, temperature, myWriteAPIKey);
    if(sts == TS_OK_SUCCESS){
      DEBUGLN_THINGSPEAK("Channel update successful.");
    }
    else{
      DEBUGLN_THINGSPEAK("Problem updating channel. HTTP error code " + String(sts));
    }
    thingSpeak_timer = millis();
  }
}

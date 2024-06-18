#include <Arduino.h>
#include <WiFi.h>              
#include <ESPmDNS.h>           
#include <SPIFFS.h>           
#include <ESPAsyncWebServer.h> // https://github.com/me-no-dev/ESPAsyncWebServer/tree/63b5303880023f17e1bca517ac593d8a33955e94
#include <AsyncTCP.h>          // https://github.com/me-no-dev/AsyncTCP
#include <DS18B20Events.h>          //#include <OneWire.h> is already included in DS18B20Events.h
// #include <ThingSpeak.h>               
#include <HTTPClient.h>

#include "mDef.h"
#include "settings.h"
#include "file_sys.h"
#include "wifi_conf.h"
#include "serverHost.h"
#include "timerThermo.h"
#include "webPages.h"

// #include "menu.h"
#include "btns.h"
#include "relay.h" 


void thingSpeakSend(float temperature)
{
  if(WiFi.status() == WL_CONNECTED) {
      WiFiClient client; 
      HTTPClient http;

      // String url = "http://" + String(serverLinkApi) + "/update?api_key=" + apiKey + "&field1=" + String(temperature);
      // http.begin(url);
      String url = "http://" + String(serverLinkApi) + "/update";
      http.begin(client, url);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      String httpRequestData = "api_key=" + apiKey + "&field1=" + String(temperature);           
      // int httpCode = http.GET();
      // if(httpCode > 0) {
        // String payload = http.getString();
        // Serial.println(payload);
      // }

      int httpResponseCode = http.POST(httpRequestData);
       /*
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      // JSON data to send with HTTP POST
      String httpRequestData = "{\"api_key\":\"" + apiKey + "\",\"field1\":\"" + String(random(40)) + "\"}";           
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);*/
     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();
    }else {
      Serial.println("WiFi Disconnected");
    }
}

void setup()
{

  setupSystem();
  initWiFi();
  setupTime();
  startSPIFFS();   
  initSection();
  relaySetup();      

  initDaysArray(); // Initialise the array for storage and set some values
  recoverSettings();  // Recover settings from LittleFS
  startServerHost();
  startSensor();
  actuateHeating(OFF);
  lastTimerSwitchCheck = millis() + timerCheckDuration; 

  btnsSetup();


}

void loop()
{ 
  btnsLoop(); 
  relayTick();

  if ((millis() - lastTimerSwitchCheck) > timerCheckDuration)
  {
    lastTimerSwitchCheck = millis(); // Reset time
    Temperature = readSensorComplete();                   

    //httpRequest(Temperature);
    
    UpdateLocalTime();               // Updates Time UnixTime to 'now'
    CheckTimerEvent();               // Check for schedules actuated
  }

  if ((millis() - LastReadingCheck) > (lastReadingDuration * 60 * 100))//1000
  {
    LastReadingCheck = millis(); // Update reading record every ~n-mins e.g. 60,000uS = 1-min
    AssignSensorReadingsToArray();
  }

  if (millis() - lastConnectionTime > 10000) {
    lastConnectionTime = millis();
    Temperature = readSensor();
    // thingSpeakSend(Temperature);
  }

  //lcdLoop();
}



void AssignSensorReadingsToArray()
{
  SensorReading[1][0] = 1;
  SensorReading[1][1] = Temperature;
  SensorReading[1][2] = RelayState;
  AddReadingToSensorData(1, Temperature); 
}

void AddReadingToSensorData(byte RxdFromID, float Temperature)
{ 
  byte ptr, p;
  ptr = SensorReadingPointer[RxdFromID];
  sensordata[RxdFromID][ptr].Temp = Temperature;
  ptr++;
  if (ptr >= SensorReadings)
  {
    p = 0;
    do
    {
      sensordata[RxdFromID][p].Temp = sensordata[RxdFromID][p + 1].Temp;
      p++;
    } while (p < SensorReadings);
    ptr = SensorReadings - 1;
    sensordata[RxdFromID][SensorReadings - 1].Temp = Temperature;
  }
  SensorReadingPointer[RxdFromID] = ptr;
}


void setupSystem()
{
  Serial.begin(115200); // Initialise serial communications
  Serial.setDebugOutput(true);
  delay(200);
  Serial.println(__FILE__);
  Serial.println("Starting...");
}





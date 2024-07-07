#ifndef FILE_SYS_H
#define FILE_SYS_H


#include <Arduino.h>
#include <LittleFS.h>
#include "settings.h"

// void startSPIFFS()
// {
//     #ifdef DEBUG_FUNC
//       Serial.println(__func__);
//     #endif

//   #ifdef DEBUG
//     Serial.println("Starting SPIFFS");
//   #endif
  
//   bool SPIFFS_Status;
//   SPIFFS_Status = SPIFFS.begin();
//   if (SPIFFS_Status == false)
//   { // Most likely SPIFFS has not yet been formated, so do so

//     #ifdef DEBUG
//       Serial.println("Formatting SPIFFS (it may take some time)...");
//     #endif
    
//     SPIFFS.begin(true); // Now format SPIFFS
//     File datafile = SPIFFS.open("/" + DataFile, "r");
//     if (!datafile || !datafile.isDirectory())
//     {

//       #ifdef DEBUG
//         Serial.println("SPIFFS failed to start...");
//       #endif
//        // Nothing more can be done, so delete and then create another file
//       SPIFFS.remove("/" + DataFile);               // The file is corrupted!!
//       datafile.close();
//     }
//   }
//   else
//   {
//     #ifdef DEBUG
//       Serial.println("SPIFFS Started successfully...");
//     #endif
    
//   }
// }


void recoverSettings()
{
    #ifdef DEBUG_FUNC
      Serial.println(__func__);
    #endif
  String Entry;
  #ifdef DEBUG
    Serial.println("Reading settings...");
  #endif
  
  File dataFile = SPIFFS.open("/" + DataFile, "r");
  if (dataFile)
  { // if the file is available, read it

    #ifdef DEBUG
      Serial.println("Recovering settings...");
    #endif
    
    while (dataFile.available())
    {
      for (byte dow = 0; dow < 7; dow++)
      {
        #ifdef DEBUG
          Serial.println("Day of week = " + String(dow));
        #endif
        
        for (byte p = 0; p < NumOfEvents; p++)
        {
          Timer[dow].Temp[p] = dataFile.readStringUntil('\n');
          Timer[dow].Temp[p].trim();
          Timer[dow].Start[p] = dataFile.readStringUntil('\n');
          Timer[dow].Start[p].trim();
          Timer[dow].Stop[p] = dataFile.readStringUntil('\n');
          Timer[dow].Stop[p].trim();
          #ifdef DEBUG
            Serial.println("Period: " + String(p) + " " + Timer[dow].Temp[p] + " from: " + Timer[dow].Start[p] + " to: " + Timer[dow].Stop[p]);
          #endif
          
        }
      }
      
      Entry = dataFile.readStringUntil('\n');
      Entry.trim();
      Hysteresis = Entry.toFloat();
      Entry = dataFile.readStringUntil('\n');
      Entry.trim();
      FrostTemp = Entry.toInt();
      Entry = dataFile.readStringUntil('\n');
      Entry.trim();
      EarlyStart = Entry.toInt();

      #ifdef DEBUG
        Serial.println("Recovered Hysteresis : " + String(Hysteresis));
        Serial.println("Recovered Frost Temp : " + String(FrostTemp));
        Serial.println("Recovered EarlyStart : " + String(EarlyStart));
      #endif
      
      dataFile.close();

      #ifdef DEBUG
        Serial.println("Settings recovered...");
      #endif
      
    }
  }
}


#endif
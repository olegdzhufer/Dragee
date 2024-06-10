#ifndef FILE_SYS_H
#define FILE_SYS_H


#include <Arduino.h>
#include <SPIFFS.h>           
#include "settings.h"

void startSPIFFS()
{
  Serial.println("Starting SPIFFS");
  bool SPIFFS_Status;
  SPIFFS_Status = SPIFFS.begin();
  if (SPIFFS_Status == false)
  { // Most likely SPIFFS has not yet been formated, so do so
    Serial.println("Formatting SPIFFS (it may take some time)...");
    SPIFFS.begin(true); // Now format SPIFFS
    File datafile = SPIFFS.open("/" + DataFile, "r");
    if (!datafile || !datafile.isDirectory())
    {
      Serial.println("SPIFFS failed to start..."); // Nothing more can be done, so delete and then create another file
      SPIFFS.remove("/" + DataFile);               // The file is corrupted!!
      datafile.close();
    }
  }
  else
  {
    Serial.println("SPIFFS Started successfully...");
  }
}


void recoverSettings()
{
  String Entry;
  Serial.println("Reading settings...");
  File dataFile = SPIFFS.open("/" + DataFile, "r");
  if (dataFile)
  { // if the file is available, read it
    Serial.println("Recovering settings...");
    while (dataFile.available())
    {
      for (byte dow = 0; dow < 7; dow++)
      {
        Serial.println("Day of week = " + String(dow));
        for (byte p = 0; p < NumOfEvents; p++)
        {
          Timer[dow].Temp[p] = dataFile.readStringUntil('\n');
          Timer[dow].Temp[p].trim();
          Timer[dow].Start[p] = dataFile.readStringUntil('\n');
          Timer[dow].Start[p].trim();
          Timer[dow].Stop[p] = dataFile.readStringUntil('\n');
          Timer[dow].Stop[p].trim();
          Serial.println("Period: " + String(p) + " " + Timer[dow].Temp[p] + " from: " + Timer[dow].Start[p] + " to: " + Timer[dow].Stop[p]);
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
      Serial.println("Recovered Hysteresis : " + String(Hysteresis));
      Serial.println("Recovered Frost Temp : " + String(FrostTemp));
      Serial.println("Recovered EarlyStart : " + String(EarlyStart));
      dataFile.close();
      Serial.println("Settings recovered...");
    }
  }
}


#endif
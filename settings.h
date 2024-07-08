#ifndef settings_h
#define settings_h


//######################################################

#include <Arduino.h>
#include <DS18B20Events.h>
#include <MenuLib.h>

#include "mDef.h"
#include "wifi/secrets.h"


const char* serverName = "dragee"; //  http://dragee.local/ 

const char* serverLinkApi = "api.thingspeak.com";
const char* serverIPApi = "184.106.153.149";

// NTP server to request epoch time
const char* ntpServer = "pool.ntp.org";
const char* timezone   = "EET-2EEST,M3.5.0/3,M10.5.0/4";

// "CET-1CEST,M3.5.0,M10.5.0/3";

//#define THINGSPEAK_PORT 81
#define WENPAGE_PORT 80 

#define LCD_ADDR 0x3F
#define LCD_ROWS 4
#define LCD_COLS 20

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire);

String       Time_str, DoW_str;                  // For Date and Time
settings     Timer[7];                           // Timer settings, 7-days of the week
int          SensorReadingPointer[NumOfSensors]; // Used for sensor data storage
float        Hysteresis     = 0.2;               // Heating Hysteresis default value


bool CHECK_UPDATE_MENU = false;

bool FLAG_LCD = false;

//################ VARIABLES ################
char* ssid       = SECRET_SSID;             // WiFi SSID     replace with details for your local network
char* password   = SECRET_PASS;         // WiFi Password replace with details for your local network

//unsigned long myChannelNumber = SECRET_CH_ID;             
//const char *  myWriteAPIKey   = SECRET_WRITE_APIKEY;  
String apiKey = SECRET_WRITE_APIKEY;

int connections = 0;

// System values
String sitetitle            = "Dragee Machine IoT";
String Year                 = "2024";     // For the footer line
float  Temperature          = 0.0;          // Variable for the current temperature
u8  TargetTemp           = 31;         // Default thermostat value for set temperature
u8  FrostTemp            = 0;          // Default thermostat value for frost protection temperature
u8  ManOverrideTemp      = 21;         // Manual override temperature
u8  MaxTemperature       = 28;         // Maximum temperature detection, switches off thermostat when reached

#define MIN_TEMP_HEAT  30
#define MIN_TEMP_COOL  0

#define MAX_TEMP_HEAT  60
#define MAX_TEMP_COOL  30


int    UnixTime             = 0;          // Time now (when updated) of the current time
char* timeNow; 

AsyncWebServer server(WENPAGE_PORT);

uint32_t lastConnectionTime =0;

float* temp = NULL;

#endif
#ifndef settings_h
#define settings_h


//#########################_WORK_PARAM_#################
// Debug mod

// #define DEBUG
// #define DEBUG_FUNC

//Section

#define ENC_S
#define BTN_S
#define RELAY_S
#define TIMER_S
#define WIFI_S
#define MENU_S
#define TEMP_S

#define FILE_S

#ifdef WIFI_S
  #define WEB_S
#endif


//######################################################

#include <Arduino.h>
#include <DS18B20Events.h>
#include <MenuLib.h>
#include "pins.h"
#include "secrets.h"
#include "sts.h"


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

bool   ManualOverride       = true;      // Manual override
int    EarlyStart           = 0;          // Default thermostat value for early start of heating
String RelayState           = "OFF";      // Current setting of the control/thermostat relay
String TimerState           = "OFF";      // Current setting of the timer
String Units                = "M";        // or Units = "I" for °F and 12:12pm time format

uint32_t    timerCheckDuration   = 5000;       // Check for timer event every 5-seconds
uint32_t    lastReadingDuration  = 1;          // Add sensor reading every n-mins
uint32_t    lastTimerSwitchCheck = 0;          // Counter for last timer check
uint32_t    LastReadingCheck     = 0;          // Counter for last reading saved check
float  LastTemperature      = 0;          // Last temperature used for rogue reading detection
int    UnixTime             = 0;          // Time now (when updated) of the current time

char* timeNow; 

AsyncWebServer server(WENPAGE_PORT);

uint32_t lastConnectionTime =0;

float* temp = NULL;

#endif
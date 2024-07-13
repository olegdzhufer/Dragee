#ifndef settings_h
#define settings_h


//#########################_WORK_PARAM_#################



//######################################################

#include <Arduino.h>
#include <DS18B20Events.h>
#include <MenuLib.h>
#include "pins.h"
#include "mDef.h"
// #include "flags.h"

String version = "2.0";      // Programme version, see change log at end

const char* serverName = "dragee"; //  http://dragee.local/ 

const char* serverLinkApi = "api.thingspeak.com";
const char* serverIPApi = "184.106.153.149";

// NTP server to request epoch time
const char* ntpServer = "pool.ntp.org";
const char* timezone   = "EET-2EEST,M3.5.0/3,M10.5.0/4";

// "CET-1CEST,M3.5.0,M10.5.0/3";

//#define THINGSPEAK_PORT 80 // Thingspeak port
#define WENPAGE_PORT 80 

#define SensorReadings  144            // maximum number of sensor readings, typically 144/day at 6-per-hour
#define NumOfSensors    2              // number of sensors (+1), set by the graphing section
#define NumOfEvents     4              // Number of events per-day, 4 is a practical limit
#define noRefresh       false          // Set auto refresh OFF
#define Refresh         true           // Set auto refresh ON
#define ON              true           // Set the Relay ON
#define OFF             false          // Set the Relay OFF



#define LCD_ADDR 0x3F
#define LCD_ROWS 4
#define LCD_COLS 20

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire);


typedef struct {
  float Temp = 0;
} sensordatatype;

sensordatatype sensordata[NumOfSensors][SensorReadings];

struct settings {
  String DoW;                // Day of Week for the programmed event
  String Start[NumOfEvents]; // Start time
  String Stop[NumOfEvents];  // End time
  String Temp[NumOfEvents];  // Required temperature during the Start-End times
};

String       Received_Data[9];                  // TxId, RxId, MsgCnt, Temperature, RelayState, Incoming Msg, Msg Rssi, Msg SNR (10-fields are sent to this Rx)
String       SensorReading[NumOfSensors][6];     // 254 Sensors max. and 6 Parameters per sensor T, H, Relay-state. Maximum LoRa adress range is 255 - 1 for Server so 0 - 253
String       DataFile = "params.txt";            // Storage file name on flash
String       Time_str, DoW_str;                  // For Date and Time
settings     Timer[7];                           // Timer settings, 7-days of the week
int          SensorReadingPointer[NumOfSensors]; // Used for sensor data storage
float        Hysteresis     = 0.2;               // Heating Hysteresis default value


bool CHECK_UPDATE_MENU = false;

bool FLAG_LCD = false;

//################ VARIABLES ################


int connections = 0;

// System values
String sitetitle            = "Dragee Machine IoT";
String Year                 = "2024";     // For the footer line
float  Temperature          = 0.0;        // Variable for the current temperature
float  TargetTemp           = 31;         // Default thermostat value for set temperature
float  FrostTemp            = 0;          // Default thermostat value for frost protection temperature
float  ManOverrideTemp      = 21;         // Manual override temperature
float  MaxTemperature       = 28;         // Maximum temperature detection, switches off thermostat when reached

#define MIN_TEMP_HEAT  30
#define MIN_TEMP_COOL  0

#define MAX_TEMP_HEAT  60
#define MAX_TEMP_COOL  30

bool   ManualOverride       = true;      // Manual override
int    EarlyStart           = 0;          // Default thermostat value for early start of heating
String RelayState           = "OFF";      // Current setting of the control/thermostat relay
String TimerState           = "OFF";      // Current setting of the timer
String Units                = "M";        // or Units = "I" for °F and 12:12pm time format

String webpage              = "";         // General purpose variable to hold HTML code for display
uint32_t    timerCheckDuration   = 5000;       // Check for timer event every 5-seconds
uint32_t    lastReadingDuration  = 1;          // Add sensor reading every n-mins
uint32_t    lastTimerSwitchCheck = 0;          // Counter for last timer check
uint32_t    LastReadingCheck     = 0;          // Counter for last reading saved check
float  LastTemperature      = 0;          // Last temperature used for rogue reading detection
int    UnixTime             = 0;          // Time now (when updated) of the current time

char* timeNow; 


uint32_t lastConnectionTime =0;

float* temp = NULL;
Line* currLine;

#endif

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

bool isFlagTemp = false;

int count = 0;

void dallas_setup(void)
{
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");

  sensors.begin();

}

void dallas_loop(void)
{
  if(isFlagTemp == true){
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); 
  Serial.println("DONE");

  Serial.print("Temperature for the device 1 (index 0) is: ");
  Serial.println(sensors.getTempCByIndex(0));

  count++;
  sensors.setUserDataByIndex(0, count);
  int x = sensors.getUserDataByIndex(0);
  Serial.println(count);
  }
}



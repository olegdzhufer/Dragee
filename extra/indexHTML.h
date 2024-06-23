/**
 * @file indexHTML.h
 * @brief This file describes the index page of the webserver.
 * As there is no template engine (à la Jinja), the HTML is split up in a number of pieces
 * to allow for dynamic content generation based on the state of the Thermostat.
 */
#include <Thermostat.h>
#include <ESP8266WebServer.h>

String index_page_html_untill_thermostat_state_button = R""""(
<!DOCTYPE html>
<html>
<head>
<style>
.button {
  border: none;
  color: white;
  padding: 2vw 8vw;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 4vw;
  margin: 4px 2px;
  cursor: pointer;
}

.button1 {background-color: #085c4e;} /* Green */
.button2 {background-color: #65819b;} /* Blue */

p{
    font-size: 4vw;
}
b {
    font-size: 4vw;
}

h1{
    font-size: 6vw;
}

h3 {
    font-size: 5vw;
}

</style>
</head>
<body>
    <center>
        <h1> Thermostat WebServer </h1>
        <h3> current temperature = {{temp}} </h3>
        <br>
        <a href="/switch_thermostat_state">
            <button class="button button1">
                Thermostat {{state}}
            </button>
        </a>

)""""; // requires temp, thermostat_state

String index_page_html_thermostat_state = R""""(
<h3> heater is {{heater_state}}</h3>
<a href="/decrease_target_temperature">
    <button class="button button1">
        -
    </button>
</a>
<b> {{target_temperature}} </b>
<a href="/increase_target_temperature">
    <button class="button button1">
        +
    </button>
</a>        
<p>lower threshold = {{lower_temp_threshold}}<br>
upper threshold = {{upper_temp_threshold}}</p>

)""""; // requires heater_state, target_temperature, lower_temp_threshold , upper_temp_threshold

String index_page_html_closing = R""""(
</center>
</body>
</html>
)"""";

String float2str(float value)
{
    char str_value[6] = "";
    sprintf(str_value, "%.1f", value);
    return String(str_value);
}

String renderIndex(float current_temperature, bool heater_on, Thermostat *thermostat)
/**
 * @brief Renders the index page by 'processing' the HTML template and replacing {{<param>}} fields.
 * 
 */
{
    String content = "";
    content += index_page_html_untill_thermostat_state_button;
    content.replace("{{temp}}", float2str(current_temperature));

    if (thermostat->isActive())
    {
        content.replace("{{state}}", "on");
        content += index_page_html_thermostat_state;
        if (heater_on)
        {
            content.replace("{{heater_state}}", "on");
        }
        else
        {
            content.replace("{{heater_state}}", "off");
        }
        content.replace("{{target_temperature}}", float2str(thermostat->getDesiredTemperature()));
        content.replace("{{lower_temp_threshold}}", float2str(thermostat->getDesiredTemperature() - thermostat->getLowerTemperatureMargin()));
        content.replace("{{upper_temp_threshold}}", float2str(thermostat->getDesiredTemperature() + thermostat->getUpperTemperatureMargin()));
    }
    else
    {
        content.replace("{{state}}", "off");
    }
    content += index_page_html_closing;
    return content;
}


/*
main



// initialize routes (these should match the routes in the webServer.h HTML) and other UI variables.
float webserverIncrementValue = 0.5;
char switchThermostatStateRoute[] = "/switch_thermostat_state";
char increaseDesiredTemperatureRoute[] = "/increase_target_temperature";
char descreaseDesiredTemperatureRoute[] = "/decrease_target_temperature";

// create NTP client
WiFiUDP ntpUDP;
NTPClient ntpClient(ntpUDP, "pool.ntp.org");

// state variables and flags
bool should_read_temperature = false;
bool should_heater_be_turned_on = false;
float most_recent_temperature_measurement;

void temperatureTimerISR()
{
  should_read_temperature = 1;
}

void setupServerRouting()
{
  server.on("/", []()
            { server.send(200, "text/html", renderIndex(most_recent_temperature_measurement, should_heater_be_turned_on, thermostat)); });
  server.on(switchThermostatStateRoute, []()
            { 
    if (thermostat->isActive()){
      thermostat->deactivate();
    }
    else{
       thermostat->activate();
    }
    // redirect to index page
    // to avoid retriggering the request
    server.sendHeader("Location","/",true);
    // 303 is for redirect after POST, but for sake of simplicity all requests are GET
    server.send(303,"text/plain",""); });
  server.on(increaseDesiredTemperatureRoute, []()
            {
              thermostat->setDesiredTemperature(thermostat->getDesiredTemperature() + webserverIncrementValue);
              server.sendHeader("Location", "/", true);
              server.send(303, "text/plain", ""); });
  server.on(descreaseDesiredTemperatureRoute, []()
            {
    thermostat->setDesiredTemperature(thermostat->getDesiredTemperature() - webserverIncrementValue);
    server.sendHeader("Location","/",true);
    server.send(303,"text/plain",""); });
}

void setup()
{

  Serial.begin(115200);

  // IO pin setup
  pinMode(LED_PIN, OUTPUT);
  pinMode(RELAIS_PIN, OUTPUT);

  // setup timer interrupts
  timer1_attachInterrupt(temperatureTimerISR);
  timer1_enable(TIM_DIV16, TIM_EDGE, TIM_LOOP);
  timer1_write(5000000 * 5); // every 5 seconds;

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(CONFIG_SSID);
  WiFi.begin(CONFIG_SSID, CONFIG_WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  IPAddress localIP = WiFi.localIP();
  Serial.println(localIP);

  // start NTP client
  ntpClient.begin();
  ntpClient.setTimeOffset(3600); // TODO: deal with zomeruur/winteruur
  ntpClient.setUpdateInterval(10000);

  // start temperature sensor
  // wait until address found
  if (temperatureSensor.begin() == false)
  {
    Serial.println("ERROR: No device found");
    while (!temperatureSensor.begin())
      ; // wait until device comes available.
  }

  temperatureSensor.setResolution(12);
  temperatureSensor.setConfig(DS18B20_CRC); // or 1
  temperatureSensor.requestTemperatures();

  // setup server
  server.begin();
  setupServerRouting();
}

float readTemperatureSensor(DS18B20 sensor)
{
  sensor.requestTemperatures();

  // wait for data AND detect disconnect
  uint32_t timeout = millis();
  while (!sensor.isConversionComplete())
  {
    if (millis() - timeout >= 800) // check for timeout
    {
      Serial.println("ERROR: timeout or disconnect");
      break;
    }
  }

  float temperature = sensor.getTempC();

  if (temperature == DEVICE_CRC_ERROR)
  {
    Serial.println("ERROR: CRC error");
    return -22.22;
  }
  return temperature;
}
void loop()
{

  ntpClient.update();

  digitalWrite(LED_PIN, 1 - thermostat->isActive());

  // read the current temperature and
  // decide if heater should be turned on

  if (should_read_temperature)
  {

    should_read_temperature = 0;

    // read temperature
    most_recent_temperature_measurement = readTemperatureSensor(temperatureSensor);
    // decide if heater should be turned on
    should_heater_be_turned_on = thermostat->shouldHeatBeOn(most_recent_temperature_measurement, should_heater_be_turned_on);

    // actuate relais
    Serial.printf("should heater be on = %d \n", should_heater_be_turned_on);
    digitalWrite(RELAIS_PIN, should_heater_be_turned_on);
  }

  server.handleClient();
}

*/
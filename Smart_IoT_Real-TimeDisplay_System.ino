//====================================================
// ESP32 + WiFi Web Server + MAX7219 + RTC + DHT22
//====================================================
//  Smart IoT Real-Time Information Display System
//====================================================
//           Author: RoshanWithEmbedded
//===================================================
#include <WiFi.h>
#include <WebServer.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <Wire.h>
#include <RTClib.h>
#include <DHT.h>
#include <Preferences.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

// MAX7219 Pins
#define DATA_PIN 23
#define CLK_PIN 18
#define CS_PIN 5

// DHT22
#define DHTPIN 4
#define DHTTYPE DHT22

// WiFi
// ESP32 AP Mode (Hotspot)
const char* ssid = "Embedded_With_Roshan";
const char* password = "12345678";

WebServer server(80);
Preferences preferences;
RTC_DS3231 rtc;
DHT dht(DHTPIN, DHTTYPE);

MD_Parola display = MD_Parola(
  HARDWARE_TYPE,
  DATA_PIN,
  CLK_PIN,
  CS_PIN,
  MAX_DEVICES
);

String customText = "EMBEDDED WITH ROSHAN";
int intensity = 3;
bool is24HourFormat = true;

void handleRoot()
{
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Smart IoT Real-Time Information Display System</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">

  <style>
    body {
      font-family: Arial;
      background: #f4f4f4;
      padding: 20px;
    }

    .container {
      max-width: 500px;
      margin: auto;
      background: white;
      padding: 25px;
      border-radius: 12px;
      box-shadow: 0px 0px 10px rgba(0,0,0,0.1);
    }

    h1 {
      margin-bottom: 10px;
    }

    h3 {
      margin-bottom: 8px;
    }

    input {
      width: 100%;
      padding: 10px;
      margin-bottom: 20px;
      border: 1px solid #ccc;
      border-radius: 8px;
      box-sizing: border-box;
    }

    input[type=range] {
      padding: 0;
    }

    button {
      width: 100%;
      background: black;
      color: white;
      padding: 12px;
      border: none;
      border-radius: 10px;
      font-size: 16px;
      cursor: pointer;
    }
  </style>
</head>

<body>

<div class="container">
  <h1>Smart IoT Real-Time Information Display System</h1>
  <p style="font-size: 14px; color: gray;">
  Developed by Roshan With Embedded
  </p>
  <p>ESP32 + MAX7219 + DS3231 + DHT22 Dashboard</p>

  <form action="/save">

    <h3>Custom Display Text</h3>
    <input name="text" type="text">

    <h3>Set Date</h3>
    <input name="date" type="date">

    <h3>Set Time</h3>
    <input name="time" type="time">
    <h3>Time Format</h3>

<select name="timeformat" style="
  width: 100%;
  padding: 10px;
  margin-bottom: 20px;
  border: 1px solid #ccc;
  border-radius: 8px;
">
  <option value="24">24 Hour Format</option>
  <option value="12">12 Hour Format</option>
</select>

    <h3>Display Intensity (0 to 15)</h3>
    <input
      name="intensity"
      type="range"
      min="0"
      max="15"
      value="3"
    >

    <button type="submit">
      Save Settings
    </button>

  </form>
</div>

</body>
</html>
)rawliteral";

  server.send(200, "text/html", html);
}

void handleSave()
{
  if (server.hasArg("text"))
    customText = server.arg("text");

   if (server.hasArg("timeformat"))
{
  String tf = server.arg("timeformat");

  if (tf == "12")
    is24HourFormat = false;
  else
    is24HourFormat = true;
} 
  if (server.hasArg("intensity"))
  {
    intensity = server.arg("intensity").toInt();
    display.setIntensity(intensity);
  }

  if (server.hasArg("date") && server.hasArg("time"))
  {
    String date = server.arg("date");
    String time = server.arg("time");

    int year  = date.substring(0, 4).toInt();
    int month = date.substring(5, 7).toInt();
    int day   = date.substring(8, 10).toInt();

    int hour   = time.substring(0, 2).toInt();
    int minute = time.substring(3, 5).toInt();

    rtc.adjust(DateTime(year, month, day, hour, minute, 0));
  }

  // Return same page with success message below button
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Smart IoT Real-Time Information Display System</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body {
      font-family: Arial;
      background: #f4f4f4;
      padding: 20px;
    }

    .container {
      max-width: 500px;
      margin: auto;
      background: white;
      padding: 25px;
      border-radius: 12px;
      box-shadow: 0px 0px 10px rgba(0,0,0,0.1);
    }

    input {
      width: 100%;
      padding: 10px;
      margin-bottom: 20px;
      border: 1px solid #ccc;
      border-radius: 8px;
      box-sizing: border-box;
    }

    input[type=range] {
      padding: 0;
    }

    button {
      width: 100%;
      background: black;
      color: white;
      padding: 12px;
      border: none;
      border-radius: 10px;
      font-size: 16px;
      cursor: pointer;
    }

    .success {
      margin-top: 12px;
      font-size: 14px;
      color: green;
      text-align: center;
    }
  </style>
</head>

<body>

<div class="container">
  <h1>Smart IoT Real-Time Information Display System</h1>
  <p style="font-size: 14px; color: gray;">
  Developed by Roshan With Embedded
  </p>
  <p>ESP32 + MAX7219 + RTC + DHT22</p>

  <form action="/save">

    <h3>Custom Display Text</h3>
    <input name="text" type="text">

    <h3>Set Date</h3>
    <input name="date" type="date">

    <h3>Set Time</h3>
    <input name="time" type="time">

    <h3>Time Format</h3>

<select name="timeformat" style="
  width: 100%;
  padding: 10px;
  margin-bottom: 20px;
  border: 1px solid #ccc;
  border-radius: 8px;
">
  <option value="24">24 Hour Format</option>
  <option value="12">12 Hour Format</option>
</select>

    <h3>Display Intensity (0 to 15)</h3>
    <input
      name="intensity"
      type="range"
      min="0"
      max="15"
      value="3"
    >

    <button type="submit">
      Save Settings
    </button>

    <div class="success">
      Settings Saved Successfully
    </div>

  </form>
</div>

</body>
</html>
)rawliteral";
preferences.begin("display", false);

preferences.putString("text", customText);
preferences.putInt("intensity", intensity);
preferences.putBool("time24", is24HourFormat);

preferences.end();

  server.send(200, "text/html", html);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Web Server Started");

  // RTC
  Wire.begin(21, 22);
 if (!rtc.begin())
{
  Serial.println("RTC not found");
  while (1);
}

  // DHT
  dht.begin();
  delay(2000);

    // Load saved settings first
  preferences.begin("display", true);

  customText = preferences.getString("text", "EMBEDDED WITH ROSHAN");
  intensity = preferences.getInt("intensity", 3);
  is24HourFormat = preferences.getBool("time24", true);
  preferences.end();

  // Display
  display.begin();
  display.setIntensity(intensity);
  display.displayClear();

  // ESP32 AP Mode (creates its own WiFi hotspot)
  WiFi.softAP(ssid, password);

  Serial.println("ESP32 Access Point Started");
  Serial.print("AP IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Web Server Routes
  server.on("/", handleRoot);
  server.on("/save", handleSave);
  server.begin();
}

void loop()
{
  server.handleClient();

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  DateTime now = rtc.now();

  char text[40];

  // Custom Text
  display.displayClear();
  display.displayScroll(customText.c_str(), PA_LEFT, PA_SCROLL_LEFT, 70);
  while (!display.displayAnimate())
{
  server.handleClient();
}

  // Time
  char timeText[15];

if (is24HourFormat)
{
  sprintf(timeText, "%02d:%02d", now.hour(), now.minute());
}
else
{
  int hour12 = now.hour() % 12;
  if (hour12 == 0) hour12 = 12;

  sprintf(timeText, "%02d:%02d", hour12, now.minute());
}
  display.displayClear();
  display.setTextAlignment(PA_CENTER);
  display.print(timeText);
  for (int i = 0; i < 50; i++)
{
  server.handleClient();
  delay(100);
}

// ===== DATE =====
char dateText[30];
sprintf(
  dateText,
  "%02d/%02d/%04d",
  now.day(),
  now.month(),
  now.year()
);

display.displayClear();

display.displayScroll(
  dateText,
  PA_LEFT,
  PA_SCROLL_LEFT,
  70
);

while (!display.displayAnimate())
{
  server.handleClient();
}

delay(500);
  // Temperature
  if (isnan(temp))
    sprintf(text, "TEMP ERROR");
  else
    sprintf(text, "TEMP %d C", (int)temp);

  display.displayClear();
  display.displayScroll(text, PA_LEFT, PA_SCROLL_LEFT, 70);
  while (!display.displayAnimate())
{
  server.handleClient();
}

  // Humidity
  if (isnan(hum))
    sprintf(text, "HUM ERROR");
  else
    sprintf(text, "HUM %d %%", (int)hum);

  display.displayClear();
  display.displayScroll(text, PA_LEFT, PA_SCROLL_LEFT, 70);
  while (!display.displayAnimate())
{
  server.handleClient();
}
}


/*## Usage

1. Replace WiFi name and password
2. Upload code to ESP32
3. Open Serial Monitor
4. Copy ESP32 IP Address
5. Open that IP in browser
6. Change text + intensity from webpage
7. MAX7219 updates live*/

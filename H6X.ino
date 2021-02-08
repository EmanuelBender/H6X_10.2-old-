
/*=============================================================================================================================================================
                                                         H6X Station (Health Environment Device)
                                                         by Emanuel Bender
  "
  within me there are
  forests without trees,
  cities without people and
  oceans without water.
  what am i?
  "

  Credits:
  TFT_eSPI Bodmer
  CJMCU-8128 - 0x5B -  Marshall Taylor, Nathan Seidle  https://github.com/sparkfun/CCS811_Air_Quality_Breakout
  |- HDC1080 - 0x40
  |- BME280  - 0x76
  VEML6075   - 0x10 -  Jonathan Dempsey  https://github.com/WifWaf/VEML6075
  MAX30102   - 0x57 - Sparkfun MAX3010X library https://github.com/sparkfun/SparkFun_MAX3010x_Sensor_Library
  MLX90614   - 0x5A - Written by Limor Fried/Ladyada for Adafruit Industries.
  INA219     - 0x41 - Battery Monitor by Flavius Bindea
  RTC DS3231 - 0x68 - The functions are inspired by work of G6EJD ( https://www.youtube.com/channel/UCgtlqH_lkMdIa4jZLItcsTg )

  known Bugs:
  Beeper/CCS811 Alarm/MAX30102 trigger PWM LED Output
  MLX90614 not working with other sensors active
  =============================================================================================================================================================*/

#define Revision "  v9"

#include <Arduino.h>
#include <WiFi.h>
#include <time.h>
#include <RTClib.h>
#include <Preferences.h>
#include <SPI.h>
#include <Wire.h>
#include <Credentials.h>
#include <ESP32Servo.h>                 // Beeps
#include <SparkFunCCS811.h>             // CJMCU-8128 - CCS811 [from Banggood with all 3 sensors]
#include <SparkFunBME280.h>             // BME280
#include <ClosedCube_HDC1080.h>         // HDC1080
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();  // Invoke custom library
//#include "hex.h"       //tft.pushImage(0, 0, 240, 240, Hex_Blur_240x240);    // put where image should be loaded

//#include <esp32-hal-log.h> // Logging

#include "MAX30105.h"       // sparkfun MAX3010X library
#include "heartRate.h"
#include <Adafruit_INA219.h>
#include <Adafruit_MLX90614.h>
#include "Adafruit_VEML6075.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 5

MAX30105 particleSensor;
RTC_DS3231 rtc;
Adafruit_INA219 ina219;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Adafruit_VEML6075 uv = Adafruit_VEML6075();

OneWire oneWire(ONE_WIRE_BUS); // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature.

DeviceAddress tempProbe1 = { 0x28, 0x12, 0xEF, 0x75, 0xD0, 0x01, 0x3C, 0x77 };
DeviceAddress tempProbe3 = { 0x28, 0x56, 0xC6, 0x75, 0xD0, 0x01, 0x3C, 0xD5 };
DeviceAddress tempProbe2 = { 0x28, 0xB9, 0xAA, 0x75, 0xD0, 0x01, 0x3C, 0xE8 };
DeviceAddress tempProbe4 = { 0x28, 0xC6, 0x99, 0x75, 0xD0, 0x01, 0x3C, 0x9E };
DeviceAddress tempProbe5 = { 0x28, 0xBD, 0x6B, 0x75, 0xD0, 0x01, 0x3C, 0xDB };
DeviceAddress tempProbe6 = { 0x28, 0xFB, 0x83, 0x75, 0xD0, 0x01, 0x3C, 0xF8 };
//DeviceAddress tempProbe7 = { 0x28, 0x30, 0x14, 0x75, 0xD0, 0x01, 0x3C, 0x79 };
//                                     // INA219 current and voltage readings
#define R_SHUNT 0.00375
#define V_SHUNT_MAX 0.075
#define V_BUS_MAX 16
#define I_MAX_EXPECTED 20

/*
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_A = 0;
  float batvoltage = 0;
  float power = 0;
  float Ah = 0;
  unsigned long lastread = 0; // used to calculate Ah
  unsigned long tick;         // current read time - last read
  int intervalReadData = 50; // different intervals for each Task
  int intervalDisplay = 1000;
  unsigned long previousMillisReadData = 0;
  unsigned long previousMillisDisplay = 0;
*/

const int tPAD1 = 4;
const int tPAD2 = 2;
const int beep = 13;
const int fan = 26;

const int pwmLED = 27;
const int freq = 20000;
const int ledChannel = 0;
const int resolution = 8;

int buttonState1 = 0;       // current state of the button
int buttonState2 = 0;
int lastButtonState = 0;
int lastButtonState2 = 0;

CCS811 myCCS811(CCS811_ADDR);  //      CCS811 Settings
ClosedCube_HDC1080 myHDC1080;
BME280 myBME280;

WiFiServer server(80);
Preferences preferences;

const char* ssid       = mySSID;        //  WIFI
const char* password   = myPassword;

const char* issid       = myiSSID;        //  iPhone WIFI
const char* ipassword   = myiPassword;

//unsigned long previousTime = 0; // timeout wifi
//const long timeoutTime = 15000; // 20000

const char* NTP_SERVER = "pool.ntp.org";            // NTP Time
const char* TZ_INFO    = "CET-1CEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00";
tm timeinfo;
time_t now;

String header;

const int CO2TH = 2000;                 // Sensor Thresholds
const int VOCTH = 250;
char pressure_value[4];

const int low = (2000, 250);            // Beeper (freq, duration)
const int high = (4000, 350);

void sensorXY()                          // ====== Voids ======
{
  tft.setCursor(6, 24);
  tft.setTextSize(2);
}
void errXY()
{
  tft.setCursor(90, 24);
  tft.setTextSize(2);
  tft.setTextColor(TFT_RED, TFT_BLACK);
}

void printTemperature(DeviceAddress deviceAddress)         // Dallas Temperature Sensor Void
{
  float tempC = sensors.getTempC(deviceAddress);
  if (tempC == DEVICE_DISCONNECTED_C)
  {
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.print(" --- ");
    return;
  } if (sensors.hasAlarm(deviceAddress)) {
    tft.setTextColor(TFT_RED, TFT_BLACK);
  }
  tft.print(tempC, 0);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
}


bool checkAlarm(DeviceAddress deviceAddress)
{
  if (sensors.hasAlarm(deviceAddress))
  {
    return true;
  }
  return false;
}

/*
  bool getNTPtime(int sec) {
  {
  //uint32_t start = millis();
  //do {
  time(&now);
  localtime_r(&now, &timeinfo);
  DateTime now = rtc.now();
  //Serial.println("NTP");
  //} while (((millis() - start) <= (1000 * sec)) && (timeinfo.tm_year < (2016 - 1900)));
  //if (timeinfo.tm_year <= (2016 - 1900)) return false;  // the NTP call was not successful
  }
  //return true;
  }
*/

void staticGFX() {
  tft.drawRoundRect(0, 19, 240, 24, 4, TFT_MIDDLEGREY);                // GFX Static Elements Main Page
  tft.drawRoundRect(0, 198, 240, 24, 4, TFT_MIDDLEGREY);
  tft.drawLine(60, 220, 60, 198, TFT_MIDDLEGREY);
  tft.drawLine(120, 220, 120, 198, TFT_MIDDLEGREY);
  tft.drawLine(180, 220, 180, 198, TFT_MIDDLEGREY);

  tft.fillRoundRect(0, 48, 75, 30, 3, TFT_DARKGREY);  // Box #1
  tft.drawRoundRect(0, 48, 75, 70, 3, TFT_MIDDLEGREY);
  tft.drawRoundRect(1, 49, 73, 68, 3, TFT_BLACK);

  tft.fillRoundRect(80, 48, 80, 30, 3, TFT_DARKGREY);  // Box #2
  tft.drawRoundRect(80, 48, 80, 70, 3, TFT_MIDDLEGREY);
  tft.drawRoundRect(81, 49, 78, 68, 3, TFT_BLACK);

  tft.fillRoundRect(165, 48, 75, 30, 3, TFT_DARKGREY);  // Box #3
  tft.drawRoundRect(165, 48, 75, 70, 3, TFT_MIDDLEGREY);
  tft.drawRoundRect(166, 49, 73, 68, 3, TFT_BLACK);

  // lower UI Boxes
  /*
    tft.fillRoundRect(0, 161, 75, 30, 3, TFT_DARKGREY);  // Box #1
    tft.drawRoundRect(0, 123, 75, 70, 3, TFT_MIDDLEGREY);
    tft.drawRoundRect(1, 124, 73, 68, 3, TFT_BLACK);
  */
  tft.fillRoundRect(80, 161, 80, 30, 3, TFT_DARKGREY);  // Box #2
  tft.drawRoundRect(80, 123, 80, 70, 3, TFT_MIDDLEGREY);
  tft.drawRoundRect(81, 124, 78, 68, 3, TFT_BLACK);
  /*
    tft.fillRoundRect(165, 161, 75, 30, 3, TFT_DARKGREY);  // Box #3
    tft.drawRoundRect(165, 123, 75, 70, 3, TFT_MIDDLEGREY);
    tft.drawRoundRect(166, 124, 73, 68, 3, TFT_BLACK);
  */
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(191, 225);
  tft.print(Revision);
}

void setup()//=========================================== SETUP ===========================================
{
  //Serial.begin(115200);
  //delay(500);

  tft.begin();                          // TFT Initialize
  tft.fillScreen(TFT_BLACK);
  tft.setSwapBytes(true);
  tft.setRotation(0);
  delay(300);
  //Wire.setClock(50000);

  pinMode(tPAD1, INPUT);
  pinMode(tPAD2, INPUT);
  pinMode(fan, OUTPUT);
  digitalWrite(fan, LOW);

  ledcAttachPin(pwmLED, ledChannel);
  ledcSetup(ledChannel, freq, resolution);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);             // Connect WiFi
  tft.setCursor(0, 0);
  tft.setTextSize(2);
  tft.println();

  if ((digitalRead(tPAD2)) == HIGH) {
    WiFi.begin(issid, ipassword);
    tft.printf("Connecting % s ", issid);
  } else {
    WiFi.begin(ssid, password);
    tft.printf("Connecting % s ", ssid);
  }
  tft.println();

  while (WiFi.status() != WL_CONNECTED) {
    tft.print("-");
    delay(200);
    if ((millis() / 1000) > 5)
      break;
  }
  tft.println();

  if (WiFi.status() == WL_CONNECTED)
  {
    //server.begin();
    tft.setTextColor(TFT_WHITE);
    tft.println(WiFi.localIP());
    configTime(0, 0, NTP_SERVER);   // See https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv for Timezone codes for your region
    setenv("TZ", TZ_INFO, 1);
    delay(1000);


    if (rtc.lostPower() == true) {
      // Serial.println("RTC lost power, let's set the time!");
      rtc.adjust(DateTime(uint32_t(now + 7203)));
      tft.setTextColor(TFT_WHITE);
      tft.print("RTC");
      tft.setTextColor(TFT_GREEN);
      tft.println("       PWR RST");
      //delay(300);
    } else {
      tft.setTextColor(TFT_WHITE);
      tft.print("RTC");
      tft.setTextColor(TFT_GREEN);
      tft.println("       OK");
      //delay(300);
    }
  } else {
    tft.setTextColor(TFT_RED);
    tft.println("WiFi      ERROR");
    tft.println("RTC       ERROR");
    //delay(300);
  }

  if (! rtc.begin()) {                                     // RTC setup
    // Serial.println("Couldn't find RTC");
    tft.setTextColor(TFT_WHITE);
    tft.print("RTC");
    tft.setTextColor(TFT_RED);
    tft.println("       NO FIND");
    //abort();
    //Serial.flush();
    //delay(300);
  }



  myBME280.settings.commInterface = I2C_MODE;              // Initialize CCS811
  myBME280.settings.I2CAddress = 0x76;
  myBME280.settings.runMode = 3;
  myBME280.settings.tStandby = 0;
  myBME280.settings.filter = 3; // 3
  myBME280.settings.tempOverSample = 5; // 5
  myBME280.settings.pressOverSample = 8;
  myBME280.settings.humidOverSample = 8;
  myBME280.begin();
  myHDC1080.begin(0x40);
  CCS811Core::status returnCode = myCCS811.begin();

  if (myCCS811.checkForStatusError() > 0) {
    tft.setTextColor(TFT_WHITE);
    tft.print("CCS811");
    tft.setTextColor(TFT_RED);
    tft.println("    ERROR");
    //delay(300);
  } else {
    tft.setTextColor(TFT_WHITE);
    tft.print("CCS811");
    tft.setTextColor(TFT_GREEN);
    tft.println("    OK");
    //delay(300);
  }

  if (!particleSensor.begin(Wire, I2C_SPEED_FAST))         // Initialize MAX30102
  {
    tft.setTextColor(TFT_WHITE);
    tft.print("MAX30102");
    tft.setTextColor(TFT_RED);
    tft.println("  ERROR");
    particleSensor.enableDIETEMPRDY(); //Enable the temp ready interrupt. This is required.
  } else {
    tft.setTextColor(TFT_WHITE);
    tft.print("MAX30102");
    tft.setTextColor(TFT_GREEN);
    tft.println("  OK");
    // HRO2 Setup to sense a nice looking saw tooth on the plotter
    byte ledBrightness = 230; //Options: 0=Off to 255=50mA
    byte sampleAverage = 8; //Options: 1, 2, 4, 8, 16, 32
    byte ledMode = 2; //Options: 1 = IR only, 2 = Red + IR on MH-ET LIVE MAX30102 board
    int sampleRate = 400; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
    int pulseWidth = 118; //Options: 69, 118, 215, 411
    int adcRange = 16384; //Options: 2048, 4096, 8192, 16384

    particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings
    particleSensor.shutDown();
  }

  if (! uv.begin()) {
    tft.setTextColor(TFT_WHITE);
    tft.print("VEML6075");
    tft.setTextColor(TFT_RED);
    tft.println("  ERROR ");
  } else {
    tft.setTextColor(TFT_WHITE);
    tft.print("VEML6075");
    tft.setTextColor(TFT_GREEN);
    tft.print("  OK ");
    uv.setIntegrationTime(VEML6075_50MS);
    tft.setTextColor(TFT_WHITE);
    switch (uv.getIntegrationTime()) {
      case VEML6075_50MS: tft.print("50"); break;
      case VEML6075_100MS: tft.print("100"); break;
      case VEML6075_200MS: tft.print("200"); break;
      case VEML6075_400MS: tft.print("400"); break;
      case VEML6075_800MS: tft.print("800"); break;
    } tft.println("ms");
    uv.setHighDynamic(true);
    uv.setForcedMode(false);
    uv.setCoefficients(2.22, 1.33,  // UVA_A and UVA_B coefficients
                       2.95, 1.74,  // UVB_C and UVB_D coefficients
                       0.001461, 0.002591); // UVA and UVB responses
  }

  sensors.begin();     // OneWire Dallas Temp begin
  tft.setTextColor(TFT_WHITE);
  tft.print("OneWire   ");
  if (sensors.getDeviceCount() < 6) {
    tft.setTextColor(TFT_RED);
  } else {
    tft.setTextColor(TFT_GREEN);
  }
  tft.print(sensors.getDeviceCount());
  tft.setTextColor(TFT_WHITE);
  tft.println("  Sensors");

  //delay(300);
  sensors.setResolution(tempProbe1, 12);
  sensors.setResolution(tempProbe2, 12);
  sensors.setResolution(tempProbe3, 12);
  sensors.setResolution(tempProbe4, 12);
  sensors.setResolution(tempProbe5, 12);
  sensors.setResolution(tempProbe6, 12);
  //sensors.setResolution(tempProbe7, 12);

  sensors.setHighAlarmTemp(tempProbe1, 27); // tempProbe, Threshold
  sensors.setHighAlarmTemp(tempProbe2, 27);
  sensors.setHighAlarmTemp(tempProbe3, 27);
  sensors.setHighAlarmTemp(tempProbe4, 27);
  sensors.setHighAlarmTemp(tempProbe5, 27);
  sensors.setHighAlarmTemp(tempProbe6, 27);
  //sensors.setHighAlarmTemp(tempProbe7, 27);

  //delay(300);

  ina219.begin();      // INA219 Setup

  mlx.begin();

  WiFi.disconnect();                                       // disconnect WiFi
  WiFi.mode(WIFI_OFF);

  tft.setTextColor(TFT_LIGHTGREY);
  tft.print("WiFi ");
  if ((WiFi.status()) == 255) {
    tft.setTextColor(TFT_INDIA);
    tft.print("DISCONNECTED");
  } else {
    tft.println(WiFi.status());
  }
  while (digitalRead(tPAD2) == LOW) {
    delay(50);
    if (digitalRead(tPAD2) == HIGH) break;
  }

  preferences.begin("my - app", false);                       // Bootup Counter
  //preferences.clear(); // Remove all preferences under the opened namespace
  //preferences.remove("counter"); // Or remove the counter key only
  unsigned int counter = preferences.getUInt("counter", 0);
  counter++;  // Increase counter by 1
  tft.setTextColor(TFT_DARKGREY);
  tft.setCursor(94, 225);
  tft.setTextSize(2);
  tft.fillScreen(TFT_BLACK);
  tft.printf(" % u\n", counter);
  preferences.putUInt("counter", counter);// Store the counter to the Preferences
  preferences.end();   // Close the Preferences
  staticGFX(); // Print Static GFX Elements
}
// Setup Done.


void loop()//=========================================== VOID LOOP ===========================================
{
  const int minElapsed = millis() / 1000 / 60;  // time elapsed since boot in min

  const int temp = myHDC1080.readTemperature() / 1.225;
  const int tempBME = myBME280.readTempC() / 1.225;
  const int RH = myHDC1080.readHumidity();
  const int CO2 = myCCS811.getCO2();
  const int TVOC = myCCS811.getTVOC();
  const int alt = myBME280.readFloatAltitudeMeters();
  String pressure = String(myBME280.readFloatPressure() * 0.000145038 / 714); // in ATM
  pressure.toCharArray(pressure_value, 4);


  printTime(timeinfo);
  readCCS811();                                //// CCS811 Function /w error detection
  readHRO2();                                  //// HeartRate SpO2 Function /w touch button detection
  readPOWER();
  readUV();                                    //// VEML6075 Combined UV-A, UV-B Readings
  readTEMP();
  readBodyTEMP();

  bool buttonState2 = (digitalRead(tPAD2));
  if (buttonState2 != lastButtonState2) {
    int ledB = 0;
    while (digitalRead(tPAD2) == 1) {
      ledB++;
      ledcWrite(ledChannel, ledB);
      delay(5);
      if (digitalRead(tPAD2) == 0)
        break;
    }
  }
  /*
    int current_mA = ina219.getCurrent_mA();
    Serial.print(CO2 / 10); // divided by 10 to make easier to see         // Serial Plotter Logging
    Serial.print(" ");
    Serial.print(TVOC);
    Serial.print(" ");
    Serial.print(current_mA);
  */


  tft.setTextSize(2);
  //tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
  //tft.setCursor(188, 203);
  //tft.print(digitalRead(tPAD2));
  tft.setCursor(0, 225);                                 // Time elapsed & Code Revision
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.print(minElapsed);
  tft.setTextColor(TFT_DARKCYAN, TFT_BLACK);
  tft.print("min");

  /*
    WiFiClient client = server.available();                           ////  WiFi Print to Local IP  ////
    if (client)
    {
      int ccs811 = myCCS811.checkForStatusError();
      pressure.toCharArray(pressure_value, 4);
      sensorXY();
      tft.setTextColor(TFT_GREEN);
      tft.print("Status HTTP");
      String currentLine = ""; //Storing the incoming data in the string
      while (client.connected() && minElapsed - previousTime <= timeoutTime) {  // loop while the client's connected
        if (client.available())  //if there is some client data available
        {
          char c = client.read(); // read a byte
          if (c == '\n') // check for newline character,
          {
            if (currentLine.length() == 0) //if line is blank it means its the end of the client HTTP request
            {
              client.println("HTTP / 1.1 200 OK");
              client.println("Content - type: text / html");
              client.println("<font style = 'font-family:electric toaster'>");
              client.println();
              client.println(" < meta name = 'apple-mobile-web-app-capable' content = 'yes' / > ");
              client.println(" < meta name = 'apple-mobile-web-app-status-bar-style' content = 'white-translucent' / > ");
              client.println("<HTML>");              // Header
              client.println("<HEAD>");
              client.println("<head><title>HEX 6 < / title > < / head > ");
              client.println("<BODY>");               //Body
              client.println("<body><div style = 'text-align: middle'>");
              client.println("<body><body bgcolor = '#383838'>");
              client.println(" < br / > ");
              client.println(" < a href = \"/?button1on\"\"><button1 style='font-size:300%; background-color:#383838; color:green;border-radius:5px; position:absolute; top:20px; left:30px;'>Sensors</a>");
              client.println("<br />");
              client.println("<br />");
              client.print("<p style=\"text-align: middle; font-size:300%; color: white\"> Altitude: ");
              client.print(alt);
              client.print("m    ");
              client.print("<br/> Pressure: ");
              client.print(pressure);
              client.print("ATM");
              client.print("<br/> Temp:     ");
              client.print(tempBME);
              client.print("C");
              client.print("<br/> RH: ");
              client.print(RH);
              client.print("%");
              client.print("<br/> CO2:   ");
              client.print(CO2);
              client.print("ppm");
              client.print("<br/> TVOC: ");
              client.print(TVOC);
              client.print("ppm");
              client.print("<br/> UV: ");
              client.print(VML.getUVIndex());
              client.print("<br/>");
              client.print("<br/> Time: ");
              client.print(minElapsed);
              client.print("m <br/>");
              client.print("<br/>");
              if (ccs811 > 0) {                     // ccs811 Error check - if yes, set text TFT_RED
                CCS811Core::status returnCode = myCCS811.begin();
                client.println("<a href=\"/?button1off\"\"><button2 style='font-size:100%; background-color:#383838; color:red;border-radius:5px; position:absolute; top:20px; left:30px;'>Sensors</a>");
                switch ( returnCode )
                {
                  case CCS811Core::SENSOR_ID_ERROR:
                    client.print("<br/>CCS811 ID Error");
                    break;
                  case CCS811Core::SENSOR_I2C_ERROR:
                    client.print("<br/>CCS811 I2C Error");
                    break;
                  case CCS811Core::SENSOR_INTERNAL_ERROR:
                    client.print("<br/>CCS811 Internal Error");
                    break;
                  case CCS811Core::SENSOR_GENERIC_ERROR:
                    client.print("<br/>CCS811 Generic Error");
                    break;
                }
              }
              client.print("<br/>");
              client.println("</BODY>");
              client.println("</HTML>");
              break;
            }
            else
            { // if you got a newline, then clear currentLine:
              currentLine = "";
            }
          }
          else if (c != '\r')
          { // if you got anything else but a carriage return character,
            currentLine += c;       // add it to the end of the currentLine
          }
        }
      }
    } */
  delay(10);
}


/////////////// END MAIN ///////////////

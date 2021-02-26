
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
  // MLX90614   - 0x5A - Written by Limor Fried/Ladyada for Adafruit Industries.
  INA219     - 0x41 - Battery Monitor by Flavius Bindea
  RTC DS3231 - 0x68 - The functions are inspired by work of G6EJD ( https://www.youtube.com/channel/UCgtlqH_lkMdIa4jZLItcsTg )
  MPU9250    - 0x69 - asukiaaa Asuki Kono, kevinlhoste, josephlarralde joseph

  known Bugs/Issues:
  Temp probes trigger alarm below ca. 5 degrees??
  MLX90614 not working while other sensors activated
  CCS811 shows spikes on SDlog when loop is running too fast
  =============================================================================================================================================================*/

#define Revision "9.3"

#include <Arduino.h>
#include <WiFi.h>
#include <time.h>
#include <RTClib.h>
#include <Preferences.h>
#include <Wire.h>
#include <Credentials.h>
#include <ESP32Servo.h>                 // Beeps
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();  // Invoke custom library
//#include "hex.h"       //tft.pushImage(0, 0, 240, 240, Hex_Blur_240x240);    // put where image should be loaded
#include "FS.h"
#include "SD.h"
#include "SPI.h"

#include "TProbes.h"
#include "FAN18.h"
#include "Lowbat.h"
#include "LowbatY.h"
#include "LowbatR.h"
#include "BuddhaRed240.h"
#include "HR18.h"
#include "HRgreen18.h"

#include "MAX30105.h"       // sparkfun MAX3010X library
#include "heartRate.h"
#include <Adafruit_INA219.h>
#include <Adafruit_MLX90614.h>
#include "VEML6075.h"
#include <SparkFunCCS811.h>             // CJMCU-8128 - CCS811 [from Banggood with all 3 sensors]
#include <SparkFunBME280.h>             // BME280
#include <ClosedCube_HDC1080.h>         // HDC1080
#include <OneWire.h>                    // Temp Probes 
#include <DallasTemperature.h>
#include <MPU9250_asukiaaa.h>
#define ONE_WIRE_BUS 5

#define SDA_PIN 21
#define SCL_PIN 22

MAX30105 particleSensor;


Adafruit_INA219 ina219;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
VEML6075 VML(0x10, Wire);
MPU9250_asukiaaa IMU;
float aX, aY, aZ, aSqrt, gX, gY, gZ, mDirection, mX, mY, mZ;

SPIClass spiSD = SPIClass(HSPI);

RTC_DS3231 rtc;
bool LoggingActive = true;    // Logging State
bool ButtonsActive = true;    // Physical Touch buttons State
bool Setup2 = true;
char LogFile[16];
char RTCtimeLOG[10];
char RTClog[12];
int ledBlog;
int yr, mo, da, hr, mi, se;

OneWire oneWire(ONE_WIRE_BUS); // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature.

DeviceAddress tempProbe1 = { 0x28, 0x12, 0xEF, 0x75, 0xD0, 0x01, 0x3C, 0x77 };
DeviceAddress tempProbe3 = { 0x28, 0x56, 0xC6, 0x75, 0xD0, 0x01, 0x3C, 0xD5 };
DeviceAddress tempProbe2 = { 0x28, 0xB9, 0xAA, 0x75, 0xD0, 0x01, 0x3C, 0xE8 };
DeviceAddress tempProbe4 = { 0x28, 0xC6, 0x99, 0x75, 0xD0, 0x01, 0x3C, 0x9E };
DeviceAddress tempProbe5 = { 0x28, 0xBD, 0x6B, 0x75, 0xD0, 0x01, 0x3C, 0xDB };
DeviceAddress tempProbe6 = { 0x28, 0xFB, 0x83, 0x75, 0xD0, 0x01, 0x3C, 0xF8 };
DeviceAddress tempProbe7 = { 0x28, 0x30, 0x14, 0x75, 0xD0, 0x01, 0x3C, 0x79 };

int t1, t2, t3, t4, t5, t6, t7;
bool ta1, ta2, ta3, ta4, ta5, ta6, ta7;
byte tempCycle = 0;

//                                     // INA219 current and voltage readings
#define R_SHUNT 0.00375
#define V_SHUNT_MAX 0.075
#define V_BUS_MAX 16
#define I_MAX_EXPECTED 20

float shuntvoltage = 0;
float busvoltage = 0;
float current_A = 0;
float loadvoltage = 0;
float power_mW = 0;
const int current_TH = 1; // current threshold in A

#define tPAD1 4      // I/O PINS
#define tPAD2 2
#define tPAD3 35 //35
#define beep 33
#define fan 26
#define tftBLK 17
#define pwmLED 27

#define TimeoutT 80          // Sleep Timer in number of Program Loops
unsigned int sleepTimer = 0;

const int pwmfreq = 20000;
const int ledChannel1 = 1;
const int pwmresolution = 12;
byte ledB = 0;

bool buttonState1 = 0;       // Button Bools
bool buttonState2 = 0;
bool buttonState3 = 0;
bool lastButtonState1 = 0;
bool lastButtonState2 = 0;
bool lastButtonState3 = 0;

CCS811 myCCS811(0x5B);  //      CCS811 Settings
ClosedCube_HDC1080 myHDC1080;
BME280 myBME280;

const int CO2TH = 2000;                 // Sensor Thresholds
const int VOCTH = 250;
char pressure_value[4];

float tempHDC;
float tempBME;
float tempCCS811;
float RH;
int alt;
int CO2;
int TVOC;
int CCS811err;

WiFiServer server(80);
Preferences preferences;
int WiFiTimeout = 5; // WiFi tries to connect for x seconds

String header;
const char* ssid       = mySSID;        //  WIFI
const char* password   = myPassword;

const char* issid       = myiSSID;        //  iPhone WIFI
const char* ipassword   = myiPassword;

const char* NTP_SERVER = "pool.ntp.org";            // NTP Time
const char* TZ_INFO    = "CET-1CEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00";
tm timeinfo;
time_t now;

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
    tft.print("--");
    tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
    return;

  } if (sensors.hasAlarm(deviceAddress)) {
    tft.setTextColor(TFT_RED, TFT_BLACK);
  } else {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
  }
  tft.print(tempC, 0);
  tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
}


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

    tft.fillRoundRect(80, 161, 80, 30, 3, TFT_DARKGREY);  // Box #2
    tft.drawRoundRect(80, 123, 80, 70, 3, TFT_MIDDLEGREY);
    tft.drawRoundRect(81, 124, 78, 68, 3, TFT_BLACK);

    tft.fillRoundRect(165, 161, 75, 30, 3, TFT_DARKGREY);  // Box #3
    tft.drawRoundRect(165, 123, 75, 70, 3, TFT_MIDDLEGREY);
    tft.drawRoundRect(166, 124, 73, 68, 3, TFT_BLACK);
  */
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(188, 225);
  tft.print("v");
  tft.print(Revision);

  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.setCursor(0, 123);
  tft.setTextSize(2);
  tft.print("SD size: ");
  if (SD.cardSize() == 0) {
    tft.print("--");
  } else {
    tft.print(SD.cardSize() / 1000000000);
  }
  tft.println(" Gb ");
  tft.print("SD used: ");
  if (SD.usedBytes() == 0) {
    tft.print("--");
  } else {
    tft.print(SD.usedBytes() / 1000000);
  }
  tft.print(" Mb ");
}

void setup()//=========================================== SETUP ===========================================
{
  //Serial.begin(115200);
  delay(100);

  tft.begin();                          // TFT Initialize
  tft.fillScreen(TFT_BLACK);
  tft.setSwapBytes(true);
  tft.setRotation(0);
  tft.pushImage(0, 0, 240, 240, BuddhaRed240);

  Wire.begin(SDA_PIN, SCL_PIN);

  tft.setTextColor(TFT_LIGHTGREY);
  tft.setTextDatum(MC_DATUM);
  tft.setTextPadding(240);
  tft.setTextSize(1);
  tft.drawString("DON'T PANIC", 120, 190, 4);

  pinMode(tPAD1, INPUT);
  pinMode(tPAD2, INPUT);
  pinMode(tPAD3, INPUT);
  pinMode(fan, OUTPUT);
  digitalWrite(fan, LOW);
  pinMode(tftBLK, OUTPUT);
  digitalWrite(tftBLK, HIGH);

  ledcAttachPin(pwmLED, ledChannel1);
  ledcSetup(ledChannel1, pwmfreq, pwmresolution);

  tft.setTextColor(TFT_BLACK, TFT_INDIA);             // Connect WiFi
  tft.setCursor(0, 225);
  tft.setTextSize(2);

  if ((digitalRead(tPAD2)) == HIGH) {
    WiFi.begin(issid, ipassword);
    //tft.printf("Connecting % s ", issid);
    tft.print("i ");
  } else {
    WiFi.begin(ssid, password);
    //tft.printf("Connecting % s ", ssid);
    tft.print("h ");
  }

  while (WiFi.status() != WL_CONNECTED) {
    //tft.print("-");
    delay(200);
    if ((millis() / 1000) > WiFiTimeout)
      break;
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    //server.begin();
    //tft.setTextColor(TFT_WHITE);
    //tft.println(WiFi.localIP());
    configTime(0, 0, NTP_SERVER);   // See https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv for Timezone codes for your region
    setenv("TZ", TZ_INFO, 1);
    delay(700);


    if (! rtc.begin()) {
      tft.print("R");
    } else {
      time(&now);
      localtime_r(&now, &timeinfo);
      DateTime now = rtc.now();
      tft.print(" ");
      delay(10);
    }


    if (rtc.lostPower() == true) {                           // RTC setup
      rtc.adjust(DateTime(uint32_t(now + 7203)));
      tft.print("rR");
    } else {
      tft.print("  ");
    }
  } else {
    tft.println("W "); // WiFi Failed
  }



  spiSD.begin(14 /* SCK */, 25 /* MISO */, 13 /* MOSI */, 15 /* CS */);
  if (!SD.begin(15, spiSD)) {
    tft.print("SD");
  } else {
    tft.print("  ");
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


  if (returnCode != CCS811Core::SENSOR_SUCCESS) {
    tft.print("C ");
  } else {
    tft.print("  ");
  }

  if (!particleSensor.begin(Wire, I2C_SPEED_FAST))              // Initialize MAX30102
  {
    tft.print("M ");
    //particleSensor.enableDIETEMPRDY(); //Enable the temp ready interrupt. This is required.
  } else {
    // HRO2 Setup to sense a nice looking saw tooth on the plotter
    byte ledBrightness = 230; //Options: 0=Off to 255=50mA
    byte sampleAverage = 8; //Options: 1, 2, 4, 8, 16, 32
    byte ledMode = 2; //Options: 1 = IR only, 2 = Red + IR on MH-ET LIVE MAX30102 board
    int sampleRate = 400; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
    int pulseWidth = 118; //Options: 69, 118, 215, 411
    int adcRange = 16384; //Options: 2048, 4096, 8192, 16384

    particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings
    particleSensor.shutDown();
    tft.print("  ");
  }

  VML.begin();                          // VEML6075 UV begin
  if (VML.getID() > 0) {
    tft.print("V ");
  } else {
    tft.print("  ");
  }

  sensors.begin();                      // OneWire Dallas Temp begin
  if (sensors.getDeviceCount() <= 6) {
    tft.setTextColor(TFT_WHITE, TFT_INDIA);
    tft.print(sensors.getDeviceCount());
    tft.setTextColor(TFT_BLACK, TFT_INDIA);
  } else {
    tft.print(" ");
  }

  sensors.setResolution(tempProbe1, 10); // 12 Bit max
  sensors.setResolution(tempProbe2, 10);
  sensors.setResolution(tempProbe3, 10);
  sensors.setResolution(tempProbe4, 10);
  sensors.setResolution(tempProbe5, 10);
  sensors.setResolution(tempProbe6, 10);
  sensors.setResolution(tempProbe7, 10);

  sensors.setHighAlarmTemp(tempProbe1, 28); // tempProbe, Threshold
  sensors.setHighAlarmTemp(tempProbe2, 28);
  sensors.setHighAlarmTemp(tempProbe3, 28);
  sensors.setHighAlarmTemp(tempProbe4, 28);
  sensors.setHighAlarmTemp(tempProbe5, 28);
  sensors.setHighAlarmTemp(tempProbe6, 28);
  sensors.setHighAlarmTemp(tempProbe7, 28);

  ina219.begin();
  //  ina219.setCalibration_32V_1A();     // To use a slightly lower 32V, 1A range (higher precision on amps):
  ina219.setCalibration_32V_2A();
  //  ina219.setCalibration_16V_400mA();  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  tft.print(" ");

  //mlx.begin();

  IMU.setWire(&Wire);
  uint8_t sensorId;

  if (IMU.readId(&sensorId) == 0) {
    tft.print(" ");
    IMU.beginAccel();
    IMU.beginGyro();
    IMU.beginMag();
    //  IMU.magXOffset = 20;    // You can set your own offset for mag values
    //  IMU.magYOffset = 10;
    //  IMU.magZOffset = 76;
  } else {
    tft.print("I");
  }

  WiFi.disconnect();                                       // disconnect WiFi
  WiFi.mode(WIFI_OFF);
  tft.print("v");
  tft.print(Revision);
  delay(200);

  preferences.begin("my - app", false);                       // Bootup Counter
  //preferences.clear(); // Remove all preferences under the opened namespace
  //preferences.remove("counter"); // Or remove the counter key only
  unsigned long int counter = preferences.getUInt("counter", 0);
  counter++;  // Increase counter by 1
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_DARKGREY);
  tft.setCursor(88, 225);
  tft.setTextSize(2);
  tft.printf(" % u\n", counter);
  preferences.putUInt("counter", counter);// Store the counter to the Preferences
  preferences.end();   // Close the Preferences

  tone(beep, 2400, 3);
  delay(400);
  staticGFX(); // Print Static GFX Elements
}

// Setup Done.



void loop()//=========================================== VOID LOOP ===========================================
{
  //Serial.begin(115200);
  //delay(20);
  unsigned long minElapsed = millis() / 1000 / 60;  // time elapsed since boot in min


  printTime(timeinfo);

  if (tempCycle > 30 || tempCycle == 0)
  {
    sensors.requestTemperatures();

    t1 = sensors.getTempC(tempProbe1);
    t2 = sensors.getTempC(tempProbe2);
    t3 = sensors.getTempC(tempProbe3);
    t4 = sensors.getTempC(tempProbe4);
    t5 = sensors.getTempC(tempProbe5);
    t6 = sensors.getTempC(tempProbe6);
    t7 = sensors.getTempC(tempProbe7);
    ta1 = sensors.hasAlarm(tempProbe1);
    ta2 = sensors.hasAlarm(tempProbe2);
    ta3 = sensors.hasAlarm(tempProbe3);
    ta4 = sensors.hasAlarm(tempProbe4);
    ta5 = sensors.hasAlarm(tempProbe5);
    ta6 = sensors.hasAlarm(tempProbe6);
    ta7 = sensors.hasAlarm(tempProbe7);
    tempCycle = 1;
  }
  tempCycle++;


  readPOWER();                     //// INA219 Readings Logging (temp Logging)
  //readIMU();                     //// MPU9250 IMU Readings
  readCCS811();                    //// CCS811 Function /w error detection Logging
  readUV();                        //// VEML6075 Combined UV-A, UV-B Readings Logging

  if (sleepTimer < TimeoutT) {
    sleepTimer++;
    readTEMP();                      //// Settings page Dallas Temperature Probes
    readHRO2();                      //// HeartRate SpO2 Function /w touch button activation
    //readBodyTEMP();

    appendFile(SD, LogFile, "2, ");

  } else {
    appendFile(SD, LogFile, "0, ");
    digitalWrite(tftBLK, LOW);

    if (digitalRead(tPAD1) == 1 || digitalRead(tPAD2) == 1) {
      sleepTimer = 0;
      digitalWrite(tftBLK, HIGH);
    }
  }

  if (ta1 == true ||                 // Temp Fan Activation
      ta2 == true ||
      ta3 == true ||
      ta4 == true ||
      ta6 == true ||
      ta6 == true ||
      ta7 == true ||
      current_A > current_TH)
  {
    digitalWrite(fan, HIGH);
    appendFile(SD, LogFile, "1, ");
  } else {
    digitalWrite(fan, LOW);
    appendFile(SD, LogFile, "0, ");
  }


  tft.setTextSize(2);
  tft.setTextColor(TFT_GOLD, TFT_BLACK);
  while (digitalRead(tPAD3) == 1) {

    if (digitalRead(tPAD1) == 1 && digitalRead(tPAD2) == 0) {
      ledB++;
      delay(25);
    }

    if (digitalRead(tPAD1) == 0 && digitalRead(tPAD2) == 1) {
      ledB = 0;
    }
    tft.setCursor(192, 24);
    tft.print("LED");

    ledcWrite(ledChannel1, ledB);

    if (digitalRead(tPAD3) == 0) {
      tft.setCursor(192, 24);
      tft.print("   ");
      break;
      //ledcWrite(ledChannel1, 0);

    }
  }


  if ( ledB > 0) {
    String ledBlog = "";
    ledBlog += ledB;
    appendFile(SD, LogFile, ledBlog.c_str());
  } else {
    appendFile(SD, LogFile, "0");
  }

  tft.setTextSize(2);
  tft.setCursor(0, 224);                                 // Time elapsed & Code Revision
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
}


/////////////// END MAIN ///////////////

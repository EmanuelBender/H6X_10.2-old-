
/*========================================================================================
                      H6X Station (Health Environment Device) by Emanuel Bender
  "
  within me there are
  forests without trees,
  cities without people and
  oceans without water.
  what am i?
  "
  - unknown

  Credits:
  Bodmer for TFT_eSPI Library, JPEGDecoder
  CJMCU-8128 - 0x5B - Marshall Taylor, Nathan Seidle https://github.com/sparkfun/CCS811_Air_Quality_Breakout
  |- HDC1080 - 0x40 - AA for ClosedCube
  |- BME280  - 0x76 - Marshall Taylor @ Sparkfun Electronics
  VEML6075   - 0x10 - Jim Lindblom @ SparkFun Electronics
  MAX30102   - 0x57 - Sparkfun MAX3010X library https://github.com/sparkfun/SparkFun_MAX3010x_Sensor_Library
  AMG8833    - 0x69 - Adafruit Industries
  SCD30      - 0x61 - Nathan Seidle @ Sparkfun Electronics
  INA260     - 0x41 - Adafruit Industries
  DS3231     - 0x68 - Adafruit Industries - fork of JeeLabs RTC Library
  MPU9250    - 0x69 - (I2C Bus 2) - asukiaaa Asuki Kono, kevinlhoste, josephlarralde joseph

  Bugs/Issues:
    VEML6075 broken?
  ========================================================================================*/

#define Revision "10.0" // Alpha Stage

#include <Arduino.h>
#include <Credentials.h>
#include <Preferences.h>
#include <WiFi.h>
#include <Wire.h>
#include <time.h>
#include <ESP32Servo.h>     // Beeps
#include <RTClib.h>
#include <rom/rtc.h>
#include "driver/rtc_io.h"
#include "soc/rtc.h"
#include "soc/rtc_cntl_reg.h"
#include "FS.h"
#include "SPIFFS.h"
#include "SD.h"
#include "SPI.h"
#include "system.h" // in Libraries/png
#include "Wifi12.h"
#include "bTemp42.h"
#include "HEX240R_8bit.h"
// #include "TProbesB240.h"
// #include "hex.h"       //tft.pushImage(0, 0, 240, 240, Hex_Blur_240x240); // put where image should be loaded

#include <MAX30105.h>             // Sensor Libraries
#include "heartRate.h"
#include <Adafruit_INA260.h>
// #include <SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library.h>
#include <Adafruit_AMG88xx.h>
#include "SparkFun_SCD30_Arduino_Library.h"
#include <DallasTemperature.h>
#include <OneWire.h>        // Temp Probes
// #include <MPU9250_asukiaaa.h>
#include <SparkFun_VEML6075_Arduino_Library.h>
#include <SparkFunCCS811.h> // CJMCU-8128 - CCS811 [from Banggood with all 3 sensors]
#include <SparkFunBME280.h> // BME280
#include <ClosedCube_HDC1080.h> // HDC1080

#include <EasyButton.h>

#include <U8g2lib.h>
//U8G2_SSD1306_64X32_1F_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
U8G2_SH1106_128X32_VISIONOX_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

#include <TFT_eSPI.h>
TFT_eSPI    tft      =  TFT_eSPI(); // Invoke custom library - #include <User_Setups/Setup24_ST7789.h> in User_Setup_Select
TFT_eSprite spr      =  TFT_eSprite(&tft); // Sprite object
TFT_eSprite dial     = TFT_eSprite(&tft); // Sprite object for dial
TFT_eSprite needle   = TFT_eSprite(&tft); // Sprite object for needle
TFT_eSprite dial2    = TFT_eSprite(&tft); // Sprite object for dial
TFT_eSprite needle2  = TFT_eSprite(&tft); // Sprite object for needle
TFT_eSprite dial3    = TFT_eSprite(&tft); // Sprite object for dial
TFT_eSprite needle3  = TFT_eSprite(&tft); // Sprite object for needle
int16_t     angle;

uint16_t    scrollTFT = 0;     // UI Coordinates
const byte  wifiX     = 205;   // status bar icon position
const byte  batX      = 222;

byte       edgeL      = 5;    // static visual elements for graph page
const byte box1Top    = 5;
const byte box1Bottom = 105;
const byte box2Top    = 120;
const byte box2Bottom = 220;
const byte boxHeight  = 100;
const byte boxWidth   = 230;
const byte l          = 228; // boxWidth - 2

const byte menuPages  = 9;
byte       pageCount  = 0;
byte       menuCar    = 3;
uint8_t    mX         = 95, mY;
const byte menuSpeed  = 15; // 1, 5, 15

const char *icon1     = "/car/settingsR.bmp";    // Menu Icons
const char *icon2     = "/car/systemR.bmp";
const char *icon3     = "/car/homecubeR.bmp";
const char *icon4     = "/car/tempcamR.bmp";
const char *icon5     = "/car/heartrateR.bmp";
const byte  carX1     = 10;                      // Menu Icons X
const byte  carX2     = 55;
const byte  carX3     = 100;
const byte  carX4     = 145;
const byte  carX5     = 190;

OneWire oneWire(5); // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature.
DeviceAddress tempProbe1 = {0x28, 0x12, 0xEF, 0x75, 0xD0, 0x01, 0x3C, 0x77};
DeviceAddress tempProbe2 = {0x28, 0x56, 0xC6, 0x75, 0xD0, 0x01, 0x3C, 0xD5};
DeviceAddress tempProbe3 = {0x28, 0xB9, 0xAA, 0x75, 0xD0, 0x01, 0x3C, 0xE8};
DeviceAddress tempProbe4 = {0x28, 0xC6, 0x99, 0x75, 0xD0, 0x01, 0x3C, 0x9E};
DeviceAddress tempProbe5 = {0x28, 0xBD, 0x6B, 0x75, 0xD0, 0x01, 0x3C, 0xDB};
DeviceAddress tempProbe6 = {0x28, 0xFB, 0x83, 0x75, 0xD0, 0x01, 0x3C, 0xF8};
DeviceAddress tempProbe7 = {0x28, 0x30, 0x14, 0x75, 0xD0, 0x01, 0x3C, 0x79};
DeviceAddress tempProbe8 = {0x28, 0x87, 0xB1, 0x75, 0xD0, 0x01, 0x3C, 0x1A};
int  t1, t2, t3, t4, t5, t6, t7, t8, max_probe_temp;
bool ta1, ta2, ta3, ta4, ta5, ta6, ta7, ta8;         // critical temp flag
int        mySensVals[8];
const byte tA1 = 27;  // AMB    temp probes soft Alarm - Fan Activation Thresholds
const byte tA2 = 27;  // BAT1
const byte tA3 = 27;  // ESP
const byte tA4 = 27;  // LED
const byte tA5 = 27;  // PWR
const byte tA6 = 27;  // BAT2
const byte tA7 = 27;  // BUS
const byte tA8 = 27;  // X
String     high_temp_message, max_probe_idx;
byte       DTdevicecount;

#define tPAD1    4         // I/O PINS
#define tPAD2    19 // 19
#define tPAD3    2
#define beepPin  33
#define fan      26
//#define powerOFF 25
#define pwmLED   17  // PWM controlled LED output
#define tftPIN   27   // TFT backlight
byte    tftBKL = 0;  // TFT brightness
byte    tftBKLmax = 255;

#define pwmfreq 20000
#define pwmresolution 12
byte ledB = 0;
bool ledBon;
byte ledBmax = 255;

#define SDA1 21
#define SCL1 22
//#define SPI_FREQUENCY 78000000      // 80Mhz max   --- VSPI, TFT
//#define SPI_READ_FREQUENCY 75000000 // 27Mhz max   --- VSPI, TFT
//#define I2C_SPEED_FAST 400000       // 400000 - 400Kb/s max , 3.4Mhz
SPIClass spiSD = SPIClass(HSPI);

bool        screenState     =  true;     // tft On/Off state
long int    sleepTimer      =  0;        // tft On/Off timer
long int    lastWake;                    // timestamp of last screen wakeup
byte        bklTimeout      =  15;       // Screen turns off after x sec
byte        deepSleepStart  =  30;       // Deep Sleep Start timer in sec
int         sleepWakeupTime =  60;       // DeepSleep Wakeup timer in sec
const int   WiFiTimeout     =  5000;     // WiFi tries to connect for x ms
int         everyXms        =  1000;     // Stuff that runs everx x ms
bool        everyXsecFlag;
int         everyX;

Adafruit_INA260 ina260 = Adafruit_INA260();      // INA219 current and voltage readings
//SFE_MAX1704X soc(MAX1704X_MAX17043);
#define BatteryCapacity 6900 // in mAh
float   Amps, Volts, Watts;
char    bat_char[4];
char    charArr[14];
int     Svolt, Bvolt, Lvolt, currA, powMW, lastpowMW;
int     TFT_BATCOLOR;
byte    INAmode;
float   batDayLeft, batHourLeft;
byte    batMinuteLeft;
int     capacityLeft;
int     ampsAvg  = 10;
int     voltsAvg = 6400;
byte    batIDX;
int     batT, volT;
int     b1, b2;
String  BatteryTime;
int     SOC;
double  socVolts;

const double lowVoltAlarm   = 6;
const double highVoltAlarm  = 8.6;
const double ampsFanTH      = 1.5;    // current threshold for Fan activation in Amps

bool   activeRTC, activeBME, activeCCS, activeSCD, activeMAX, activeINA, activeAMG, activeVML, activeSOC;
bool   powerAlarm, tempAlarm, chargingActive, wetAlarm, lowPowerMode;  //  Voltage & Current Alarms
bool   airWarning, uvWarning;
bool   loggingActive;                 // SYSTEM
bool   deepSleepActive = false;
bool   alarmEnable     = true;        // enables critical Alarm Warnings. should stay on!
bool   fanActive       = false;
bool   silentMode      = true;
bool   htmlRestart;
bool   deleteLog;
bool   notiOn;
int    notiY = -60, notiTimer;
int    notiTimestampF = -60000, notiTimestampA = -60000, notiTimestampT = -15000, notiTimestampL = -60000, notiTimestampW = -10000;
bool   SDpresent, nFanFlag, nAirFlag, nTempFlag, nLedFlag, nWetFlag;
String SDdata;
String SDloghead = "";
String filename;
String panic;
File   bmpFS;
File   file;
String buffer;
uint32_t seekOffset;
uint16_t w, h, row, col;
uint8_t  r, g, b;
uint16_t padding;

MAX30105 MAX30105;    // HR + SpO2 Settings
uint32_t ir, red;
double   fred, fir;
double   SpO2 = 0;  // raw SpO2 before low pass filtered
long     delta, irValue;
byte     irOffset      = 5;    // 0 - 90 , offset distance from sensor
byte     constHRtop    = 93 - irOffset;     // HR graph constraints
byte     constHRbottom = 90 - irOffset;
byte     ledBrightness = 200;  // 130 - Options: 0=Off to 255=50mA
const byte ledMode     = 2;    // Options: 1 = IR only, 2 = Red + IR on MH-ET LIVE MAX30102 board
const int  sampleRate  = 3200; // Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
const byte sampleAverage = 32;   // Options: 1, 2, 4, 8, 16, 32 --- 16
const int  pulseWidth  = 215;  // Options: 69, 118, 215, 411       --- 118
const int  adcRange    = 16384;// Options: 2048, 4096, 8192, 16384

const byte RATE_SIZE = 5;    //  Increase this for more HR averaging. 4 is good.
byte       rates[RATE_SIZE];
byte       rateSpot  = 0;
long       lastBeat  = 0;
float      beatsPerMinute;
uint8_t    beatAvg;

int     lastIR    = 0;
int     lastO2    = 0;
int     i         = 0;
int     m         = 0;
byte    Num       = 10;   //  50 calculate SpO2 by this sampling interval
double  ESpO2     = 90.0; // initial value of estimated SpO2
double  FSpO2     = 0.7;  // filter factor for estimated SpO2
double  frate     = 0.95; // 0.95 low pass filter for IR/red LED value to eliminate AC component
double  avered    = 0;
double  aveir     = 0;
double  sumirrms  = 0;
double  sumredrms = 0;

Adafruit_AMG88xx amg;         //   AMG8833
byte     redAMG, greenAMG, blueAMG;
//float   aa, bb, cc, dd;

#define  AMG_COLS 8
#define  AMG_ROWS 8
float    pixels[AMG_COLS * AMG_ROWS];
float    maxTempAMG, minTempAMG, tempAMG;
bool     amgSetHiRes = false, measurePoint = false; // AMG8833 Image Resolution & burst reading measurement area
float    dest_2d[13320], arr[4], adj_2d[16];
float    val, x, y, frac_x, frac_y, out;
byte     idx, COLS, ROWS;
byte     MINTEMP = 22, MAXTEMP = 33;
byte     colorIndex2, colorIndex;
uint16_t color, boxsize;
int      colorTemp;
float    get_point(float *p, uint8_t rows, uint8_t cols, int8_t x, int8_t y);
void     set_point(float *p, uint8_t rows, uint8_t cols, int8_t x, int8_t y, float f);
void     get_adjacents_1d(float *src, float *dest, uint8_t rows, uint8_t cols, int8_t x, int8_t y);
void     get_adjacents_2d(float *src, float *dest, uint8_t rows, uint8_t cols, int8_t x, int8_t y);
float    cubicInterpolate(float p[], float x);
float    bicubicInterpolate(float p[], float x, float y);
void     interpolate_image(float *src, uint8_t src_rows, uint8_t src_cols, float *dest, uint8_t dest_rows, uint8_t dest_cols);

const byte amgNumReadings = 50;         // Samples of Thermal Cam burst Reading
float      amgReadings[amgNumReadings];
byte       amgreadIndex   = 0;
float      amgtotal       = 0;
double     amgaverage     = 0;
bool       burstReading;

RTC_DS3231 rtc;              //  RTC
bool       rtcLostPower;
char       LogFile[16];        // char & Strings
char       RTClog[13];
uint8_t    yr, mo, da, hr, mi, se, dow;
char       daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
String     RTCt       = ""; // RTC time
String     RTCd       = ""; // RTC date
String     RTCprint   = "";
String     RTClogfile = "";

String    ledBprint, currentLine, envData, PowerLog, tempProbes, dateString;

long int  previousTime, previousTime1, millisElapsed, minElapsed, secElapsed, previousMs;
long int  cycleCount;
long int  counter;
byte      count = 0;
uint16_t  FPS;
const long uS_TO_S_FACTOR = 1000000;

#define SDLOGHEAD "\nTime, Date, Bat %, Bat V, Amps, Watts, t1, t2, t3, t4, t5, t6, t7, t8, CO2, CO2(CCS), tVOC, Temp, RH, Alt, Press, UV, Backlight, Fan, LED, Low Power, Deep Sleep\n"

//  MPU9250_asukiaaa IMU;
//  float    aX, aY, aZ, aSqrt, gX, gY, gZ, mDirection, mX, mY, mZ;
//  uint8_t  sensorId;
uint32_t steps;
//  double   stepTH = 1.8; // counts a step at 1.8G
bool     flag; // stepcounter flag

VEML6075 VML;
int      UVI, UVA, UVB;
String   UVIsd = "--, ";

SCD30    scd30;
CCS811   myCCS811(0x5B);
ClosedCube_HDC1080 myHDC1080;
BME280   myBME280;

float     pressureBME, tempSCD, humidSCD;
double    tempHDC, humidHDC, tHDC, hHDC, hdcT, hdcT2;
double    dewPoint, tempBME, temp, dewpoint;
int       tempRTC, co2SCD, co2CCS, tvocCCS, tempC, altBME, tvocIDX = 1, hdcIDX = 0;
long int  tvocT, ccsT;
const float Da = 17.271, Db = 237.7;
byte      pCO2, pTVOC, AirQI;
int       prevCO2, prevTVOC, tvocSMPL, co2SMPL;
byte      fanGraph, TempGraph, RHgraph, CCS811err;
#define   SEALEVELPRESSURE_HPA (1028.25) // sealevel Pressure Berlin
byte      dialX = 150, dialY = 124;      // Homescreen Dials XY Coordinates
byte      dial2X = 19, dial2Y = 125;
byte      dial3X = 84, dial3Y = 7;

WiFiServer  server(80);
Preferences preferences;
uint32_t    chipId;

byte   WiFistatus, WiFiRSSI, wifiNetworks;
String wiFiName;
String header;

const char *NTP_SERVER = "pool.ntp.org"; // NTP Time   pool.ntp.org
const char *TZ_INFO = "CET-1CEST,M3.5.0,M10.5.0/3"; //  CET-1CEST,M3.5.0,M10.5.0/3  ,  CET-1CEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00  ,  WEST-1DWEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00
tm timeinfo;
time_t now;

void IRAM_ATTR buttonInterrupt1();
void IRAM_ATTR buttonInterrupt2();
EasyButton button(tPAD3);
void buttonPressed();
void sequenceEllapsed();
void buttonISR();


void setup() //==================================== SETUP =========================================
{
  //  Serial.begin(115200);
  //  delay(800);
  tft.fillScreen(TFT_BLACK);
  tft.begin();

  //  spr.setColorDepth(16);
  createDialScale(0, 180, 1);   // create scale (start angle, end angle, increment angle)
  createNeedle();
  createDialScale2(0, 180, 1);   // create scale (start angle, end angle, increment angle)
  createNeedle2();
  createDialScale3(0, 180, 1);   // create scale (start angle, end angle, increment angle)
  createNeedle3();
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFontDirection(1);
  u8g2.setFontMode(0);
  u8g2.setFont(u8g2_font_u8glib_4_tf);

  pinMode(fan, OUTPUT);
  digitalWrite(fan, LOW);
  pinMode(tftPIN, OUTPUT);
  digitalWrite(tftPIN, HIGH);
  ledcAttachPin(pwmLED, 1); // ledPin, ledChannel
  ledcSetup(1, pwmfreq, pwmresolution); // ledChannel, Frequency, Resolution

  attachInterrupt(tPAD1, buttonInterrupt1, RISING);
  attachInterrupt(tPAD2, buttonInterrupt2, RISING);
  //  attachInterrupt(digitalPinToInterrupt(tPAD3), buttonInterrupt3, RISING);

  button.begin();
  button.onSequence(2, 600, doubleClick);
  button.onPressed(sinlgeClick);
  //  button.onPressedFor(2000, onPressedForDuration);
  button.enableInterrupt(buttonISR);

  //  pinMode(powerOFF, OUTPUT);
  //  digitalWrite(powerOFF, HIGH);

  //  gpio_deep_sleep_hold_dis();
  rtc_gpio_hold_dis(GPIO_NUM_17);
  rtc_gpio_hold_dis(GPIO_NUM_26);
  rtc_gpio_hold_dis(GPIO_NUM_27);

  Wire.begin(SDA1, SCL1, I2C_SPEED_FAST);
  //  Wire1.begin(SDA2, SCL2, I2C_SPEED_FAST);

  preferences.begin("my - app", false);
  counter = preferences.getUInt("counter", 0);    // persistent Preferences
  counter++;
  preferences.putUInt("counter", counter);
  htmlRestart   = preferences.getBool("htmlRestart", 0);
  loggingActive = preferences.getBool("loggingActive", 0);
  steps         = preferences.getUInt("steps", 0);
  preferences.end();

  millisElapsed = millis();
  while (!SPIFFS.begin()) {
    delay(10);
    if (millis() - millisElapsed > 2000) {
      u8g2.drawStr(120, 0, "SPIFFS FAILED");
      u8g2.sendBuffer();
      break;
    }
  }

  spiSD.begin(14, 39, 13, 15); // SCK, MISO, MOSI, CS
  spiSD.setFrequency(SPI_FREQUENCY);
  delay(10);
  if (SD.begin(15, spiSD, SPI_FREQUENCY)) {
    SDpresent = true;
    //    loggingActive = true;
  } else {
    SDpresent = false;
    loggingActive = false;
    u8g2.drawStr(110, 0, "SD FAILED");
    u8g2.sendBuffer();
  }

  tft.setTextColor(TFT_WHITE);
  tft.setTextDatum(MC_DATUM);
  tft.setTextSize(1);

  if (!SDpresent) {
    drawBmp(SPIFFS, "/BuddhaRed240.bmp", 0, 0);
    tft.drawString("DON'T PANIC", TFT_WIDTH / 2, 198, 4);
  } else {
    i = random(1, 14);
    if (i == 1) drawBmp(SD, "/UI/nasa240.bmp", 0, 0);
    if (i == 2) drawBmp(SD, "/UI/nasab240.bmp", 0, 0);
    if (i == 3) drawBmp(SD, "/UI/NasaWorm240.bmp", 0, 0);
    if (i == 4) drawBmp(SD, "/UI/Curiosity240.bmp", 0, 0);
    if (i == 5) drawBmp(SD, "/UI/deathstar240.bmp", 0, 0);
    if (i == 6) drawBmp(SD, "/UI/MoonEarth240.bmp", 0, 0);
    if (i == 7) drawBmp(SD, "/UI/Saturn240.bmp", 0, 0);
    if (i == 8) drawBmp(SD, "/UI/Bahamas240.bmp", 0, 0);
    if (i == 9) drawBmp(SD, "/UI/ISS240.bmp", 0, 0);
    if (i == 10) drawBmp(SD, "/UI/River240.bmp", 0, 0);
    if (i == 11) drawBmp(SD, "/UI/EarthNight240.bmp", 0, 0);
    if (i == 12) drawBmp(SD, "/UI/github240.bmp", 0, 0);
    if (i == 13) drawBmp(SD, "/UI/NASAretro.bmp", 0, 0);
    if (i == 14) drawBmp(SD, "/UI/NASAretro.bmp", 0, 0);
    if (i == 1 || i == 2 || i == 4 || i == 5 || i == 6 || i == 12 || i == 13 || i == 14) {
      tft.drawString("DON'T PANIC", TFT_WIDTH / 2, 198, 4);
    }
    i = 0;
  }

  tft.setTextColor(TFT_BLACK, TFT_INDIA); // Connect WiFi
  tft.setTextSize(2);
  tft.setCursor(0, 225);

  if (digitalRead(tPAD1) || digitalRead(tPAD2)) {
    WiFi.begin(myiSSID, myiPassword);
    tft.print("i ");
  } else {
    WiFi.begin(mySSID, myPassword);
    tft.print("h ");
  }
  millisElapsed = millis();
  while (WiFi.status() != WL_CONNECTED) {
    yield();
    delay(50);
    if (millis() - millisElapsed > WiFiTimeout) break;
  }

  if (WiFi.status() == WL_CONNECTED) {
    configTime(0, 0, NTP_SERVER); // gmtOffset, daylightOffset, ntpServer  -  See https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv for Timezone codes for your region
    //    setenv("TZ", TZ_INFO, 1);
    yield();
    delay(50);
    tft.print("  ");
    server.begin();
    delay(5);
  } else {
    tft.print("W "); // WiFi Failed
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    u8g2.drawStr(100, 0, "WIFI FAILED");
    u8g2.sendBuffer();
  }


  if (rtc.begin()) {
    time(&now);                      // RTC time
    localtime_r(&now, &timeinfo);    // ESP32 Time format
    DateTime now = rtc.now();
    rtc.disable32K();
    tft.print(" ");
    activeRTC = true;
  } else {
    tft.print("R");
  }
  if (rtc.lostPower() && WiFi.status() == WL_CONNECTED) {
    rtc.adjust(DateTime(uint32_t(now) + 7200)); // 3600
    tft.print("rR");
    rtcLostPower = true;
  } else {
    tft.print("  ");
    rtcLostPower = false;
  }

  if (SDpresent) {
    tft.print("  ");
  } else {
    tft.print("SD");
  }

  Time(timeinfo);
  print_wakeup_reason();
  tft.setTextSize(2);
  tft.setTextColor(TFT_BLACK, TFT_INDIA);

  myBME280.settings.commInterface   = I2C_MODE;
  myBME280.settings.I2CAddress      = 0x76;
  myBME280.settings.runMode         = 3;       // 0 = sleep, 1 = forced, 3 = normal
  myBME280.settings.tStandby        = 5;       // 0 to 7 valid. Time between readings. 4 = 500ms, 5 = 1000ms, 0 = 0.5ms
  myBME280.settings.filter          = 4;       // 0 to 4 is valid. Filter coefficient. See 3.4.4
  myBME280.settings.tempOverSample  = 12;      // 0 to 16 are valid. 0 disables temp sensing
  myBME280.settings.pressOverSample = 12;      // 0 to 16 are valid. 0 disables pressure sensing
  myBME280.settings.humidOverSample = 12;      // 0 to 16 are valid. 0 disables humidity sensing

  if (myBME280.begin()) {
    /*
      myBME280.setFilter(4);
      myBME280.setStandbyTime(5);
      myBME280.setTempOverSample(5);
      myBME280.setPressureOverSample(8);
      myBME280.setHumidityOverSample(8);
      myBME280.setMode(MODE_NORMAL);
    */
    activeBME = true;
  }

  myHDC1080.begin(0x40);

  CCS811Core::status returnCode = myCCS811.begin();

  if (returnCode != CCS811Core::SENSOR_SUCCESS) {
    tft.print("C ");
    u8g2.drawStr(90, 0, "CCS811 FAILED");
    u8g2.sendBuffer();
  } else {
    myCCS811.setDriveMode(1);
    tft.print("  ");
    activeCCS = true;
  }

  if (scd30.begin()) {
    tft.print("  ");
    scd30.setMeasurementInterval(5);
    scd30.setAutoSelfCalibration(true);
    scd30.beginMeasuring();
    activeSCD = true;
  } else {
    tft.print("S3");
    u8g2.drawStr(80, 0, "SCD30 FAILED");
    u8g2.sendBuffer();
  }

  if (MAX30105.begin(Wire, I2C_SPEED_FAST)) {
    MAX30105.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); // Configure sensor with these settings
    MAX30105.shutDown();
    tft.print("  ");
    activeMAX = true;
  } else {
    tft.print("M ");
    u8g2.drawStr(70, 0, "MAX30105 FAILED");
    u8g2.sendBuffer();
  }

  if (VML.begin(Wire)) {      // VEML6075 UV begin
    tft.print("  ");
    VML.setIntegrationTime(VEML6075::IT_800MS);
    VML.setHighDynamic(VEML6075::DYNAMIC_HIGH);
    VML.setTrigger(VEML6075::TRIGGER_ONE_OR_UV_TRIG); // TRIGGER_ONE_OR_UV_TRIG
    activeVML = true;
  } else {
    tft.print("V ");
    u8g2.drawStr(60, 0, "VML6075 FAILED");
    u8g2.sendBuffer();
  }

  sensors.begin();         // OneWire Dallas Temp begin
  DTdevicecount = sensors.getDeviceCount();
  if (DTdevicecount < 8) {
    tft.setTextColor(TFT_WHITE, TFT_INDIA);
    tft.print(DTdevicecount);
    tft.setTextColor(TFT_BLACK, TFT_INDIA);
  } else {
    tft.print(" ");
  }
  /*
    sensors.setResolution(tempProbe1, 9); // AMB       9-12 Bit, default is 9 Bit
    sensors.setResolution(tempProbe2, 9); // BAT1
    sensors.setResolution(tempProbe3, 9); // LED
    sensors.setResolution(tempProbe4, 9); // ESP
    sensors.setResolution(tempProbe5, 9); // PWR
    sensors.setResolution(tempProbe6, 9); // X
    sensors.setResolution(tempProbe7, 9); // BAT2
    sensors.setResolution(tempProbe8, 9); // BUS
  */

  sensors.setWaitForConversion(false);
  sensors.setHighAlarmTemp(tempProbe1, 50); // AMB    Dallas tempProbe Alarm Thresholds
  sensors.setHighAlarmTemp(tempProbe2, 60); // BAT1
  sensors.setHighAlarmTemp(tempProbe3, 80); // LED
  sensors.setHighAlarmTemp(tempProbe4, 50); // ESP
  sensors.setHighAlarmTemp(tempProbe5, 70); // PWR
  sensors.setHighAlarmTemp(tempProbe6, 50); // X
  sensors.setHighAlarmTemp(tempProbe7, 60); // BAT2
  sensors.setHighAlarmTemp(tempProbe8, 55); // BUS
  sensors.setLowAlarmTemp(tempProbe1, -15); // AMB
  sensors.setLowAlarmTemp(tempProbe2, -10); // BAT1
  sensors.setLowAlarmTemp(tempProbe3, -20); // LED
  sensors.setLowAlarmTemp(tempProbe4, -15); // ESP
  sensors.setLowAlarmTemp(tempProbe5, -15); // PWR
  sensors.setLowAlarmTemp(tempProbe6, -10); // X
  sensors.setLowAlarmTemp(tempProbe7, -10); // BAT2
  sensors.setLowAlarmTemp(tempProbe8, -15); // BUS

  if (myBME280.readTempC() < -10) {
    myHDC1080.heatUp(10);
  } else if (myBME280.readTempC() < 0) {
    myHDC1080.heatUp(5);
  }

  //  if (soc.begin()) {
  //    soc.enableDebugging();
  //    activeSOC = true;
  //  }

  if (ina260.begin()) {      // INA260 begin
    ina260.setAveragingCount(INA260_COUNT_128); // 1, 4, 16, 64, 128, 256, 512, 1024
    ina260.setVoltageConversionTime(INA260_TIME_558_us); // 140_us, 204_us, 332_us, 558_us, 1_1_ms, 2_116_ms, 4_156_ms, 8_244_ms;
    ina260.setCurrentConversionTime(INA260_TIME_558_us);
    ina260.setAlertLimit(6);
    ina260.setAlertType(INA260_ALERT_UNDERVOLTAGE);
    ina260.setAlertLatch(INA260_ALERT_LATCH_TRANSPARENT);   // Alert will reset when fault is cleared
    //    ina260.setAlertLatch(INA260_ALERT_LATCH_ENABLED); // Alert will latch until Mask/Enable register is read
    //    ina260.setAlertPolarity(INA260_ALERT_POLARITY_INVERTED); // Active Low (default is Active High)
    tft.print("  ");
    ina260.setMode(INA260_MODE_TRIGGERED);
    activeINA = true;
  } else {
    tft.print("I ");
    u8g2.drawStr(50, 0, "INA260 FAILED");
    u8g2.sendBuffer();
  }

  if (amg.begin(0x69)) {
    tft.print(" ");
    amg.setMovingAverageMode(AMG88xx_DIFFERENCE); // AMG88xx_ABSOLUTE_VALUE
    Wire.beginTransmission(0x69);   //  AMG8833 Modes
    Wire.write(0x00);   // Register
    Wire.write(0x10);   // Value to Register 0x00 - Normal, 0x10 - Sleep, 0x20 - 60sec, 0x21 - 10sec
    if (Wire.endTransmission() == 0) activeAMG = true;
  } else {
    u8g2.drawStr(40, 0, "AMG8833 FAILED");
    u8g2.sendBuffer();
    tft.print("A");
  }

  /*
    IMU.setWire(&Wire1);          //  !!  MPU9250 begin, using second I2C bus (Wire1)
    if (IMU.readId(&sensorId) == 0) {
      tft.print(" ");
      IMU.beginAccel();
      IMU.beginGyro();
      IMU.beginMag();
      //    IMU.magXOffset = -35;    // You can set your own offset for mag values
      //    IMU.magYOffset = 10;
      //    IMU.magZOffset = 46;
    } else {
      tft.print("M");
      Serial.println("MPU9250 FAILED");
      //    u8g2.drawStr(30, 0, "IMU FAILED");
      //    u8g2.sendBuffer();
    }
  */
  //  tft.print(Revision);
  u8g2.drawStr(0, 0, "...Welcome!");
  u8g2.sendBuffer();
  u8g2.setFontDirection(0);

  delay(600);
  lastWake = millis();

  tft.fillScreen(TFT_BLACK);
  //  tft.setTextColor(TFT_DARKGREY, TFT_BLACK);
  //  tft.setCursor(96, 225);
  //  tft.print(counter);

  tone(beepPin, 2400, 3);

  //  Serial.begin(115200);
  //    delay(100);
  //  SPIFFS.format();

}


void loop() //=================================== VOID LOOP ========================================
{

  page0();     // Menu
  page1();     // System Diagnostics
  page2();     // SD card
  page3();     // Device Stats
  page4();     // Graphs
  page5();     // Home Page
  page6();     // Info Page CO2
  page7();     // Info Page TVOC
  page8();     // Thermal Cam
  page9();     // HeartRate Sensor

}
//=============================================== END MAIN =========================================

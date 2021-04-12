
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
  TFT_eSPI Bodmer
  Adafruit
  CJMCU-8128 - 0x5B -  Marshall Taylor, Nathan Seidle https://github.com/sparkfun/CCS811_Air_Quality_Breakout
  |- HDC1080 - 0x40
  |- BME280  - 0x76
  VEML6075   - 0x10 - Jonathan Dempsey  https://github.com/WifWaf/VEML6075
  MAX30102   - 0x57 - Sparkfun MAX3010X library https://github.com/sparkfun/SparkFun_MAX3010x_Sensor_Library
  MLX90614   - 0x5A - Written by Limor Fried/Ladyada for Adafruit Industries.
  INA219     - 0x41 - Battery Monitor by Flavius Bindea
  RTC DS3231 - 0x68 - The functions are inspired by work of G6EJD ( https://www.youtube.com/channel/UCgtlqH_lkMdIa4jZLItcsTg )
  MPU9250    - 0x69 - asukiaaa Asuki Kono, kevinlhoste, josephlarralde joseph

  todo:
  - on/off buttons for WiFi, SD, Logging, deepSleep, sensors

  known Bugs/Issues:
  MLX90614 not working while other sensors running/activated
  ========================================================================================*/

#define Revision "9.7"

#include <Arduino.h>
#include <Credentials.h>
#include <Preferences.h>
#include <WiFi.h>
#include <Wire.h>
#include <time.h>
#include <ESP32Servo.h> // Beeps
#include <RTClib.h>
#include <rom/rtc.h>
#include "driver/rtc_io.h"
#include "soc/rtc.h"
#include "soc/rtc_cntl_reg.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "FAN18.h"
#include "HR18.h"
#include "HRgreen18.h"
#include "SD18.h"
#include "Wifi12.h"
#include "WifiG12.h"
#include "WifiIdle12.h"
#include "WifiLow12.h"
#include "WifiLower12.h"
#include "WifiOff12.h"
#include "bat5.h"
#include "bat10.h"
#include "bat20.h"
#include "bat30.h"
#include "bat40.h"
#include "bat50.h"
#include "bat60.h"
#include "bat70.h"
#include "bat80.h"
#include "bat100.h"
#include "bTemp22.h"
#include "bTemp42.h"
#include "bTemp80.h"
#include "BuddhaRed240.h"
#include "TProbesB240.h"
#include "HEX240.h"
#include "hex.h"       //tft.pushImage(0, 0, 240, 240, Hex_Blur_240x240); // put where image should be loaded
#include "heartRate.h"

#include <MAX30105.h> // sparkfun MAX3010X library
#include <VEML6075.h>
#include <Adafruit_INA260.h>
#include <Adafruit_MLX90614.h>
#include <ClosedCube_HDC1080.h> // HDC1080
#include <DallasTemperature.h>
#include <MPU9250_asukiaaa.h>
#include <OneWire.h>        // Temp Probes
#include <SparkFunBME280.h> // BME280
#include <SparkFunCCS811.h> // CJMCU-8128 - CCS811 [from Banggood with all 3 sensors]

#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI(); // Invoke custom library
TFT_eSprite spr = TFT_eSprite(&tft); // Sprite object
TFT_eSprite spr2 = TFT_eSprite(&tft); // Sprite object
uint16_t TFTwidth;
uint16_t TFTheight;
uint16_t scrollTFT;
#define wifiX 205
#define batX 222
#define MenuPages 8
byte pageCount = 0;

#define ONE_WIRE_BUS 5

OneWire oneWire(ONE_WIRE_BUS); // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature.
DeviceAddress tempProbe1 = {0x28, 0x12, 0xEF, 0x75, 0xD0, 0x01, 0x3C, 0x77};
DeviceAddress tempProbe3 = {0x28, 0x56, 0xC6, 0x75, 0xD0, 0x01, 0x3C, 0xD5};
DeviceAddress tempProbe2 = {0x28, 0xB9, 0xAA, 0x75, 0xD0, 0x01, 0x3C, 0xE8};
DeviceAddress tempProbe4 = {0x28, 0xC6, 0x99, 0x75, 0xD0, 0x01, 0x3C, 0x9E};
DeviceAddress tempProbe5 = {0x28, 0xBD, 0x6B, 0x75, 0xD0, 0x01, 0x3C, 0xDB};
DeviceAddress tempProbe6 = {0x28, 0xFB, 0x83, 0x75, 0xD0, 0x01, 0x3C, 0xF8};
DeviceAddress tempProbe7 = {0x28, 0x30, 0x14, 0x75, 0xD0, 0x01, 0x3C, 0x79};
int t1, t2, t3, t4, t5, t6, t7;
bool ta1, ta2, ta3, ta4, ta5, ta6, ta7;
byte DTdevicecount;

unsigned long previousTime, currentTime, minElapsed, previousMs;
long cycleCount;
long int counter;
uint32_t loopEndT;
#define uS_TO_S_FACTOR 1000000ULL

#define SDA_PIN 21
#define SCL_PIN 22
#define spiFreq 80000000         // 80Mhz max   --- HSPI, SD
#define SPI_FREQUENCY 80000000   // 27Mhz max   --- VSPI, TFT
#define SPI__READ_FREQUENCY 80000000   // 27Mhz max   --- VSPI, TFT
#define I2C_SPEED_FAST 400000      // 400000 - 400Kb/s max , 3.4Mhz
SPIClass spiSD = SPIClass(HSPI);

bool screenState;              // tft On/Off
unsigned int sleepTimer = 0;   // tft On/Off timer
unsigned int TimeoutT = 4000;  // TFT Backlight Dimm timer in Loop Cycles
int TimeoutT2 = 2000;          // TFT Backlight Off timer in Loop Cycles
#define everyXms 1000          // Stuff that runs everx X ms
#define deepSleepStart 3000    // Deep Sleep Start timer in cycles , must be bigger than TimeoutT
unsigned int sleepWakeupTime = 60; // DeepSleep Wakeup in sec

bool criticalAlarm = false;
#define criticalTemp 80
byte lowVoltAlarm = 6;
double highVoltAlarm = 8.5;
float currentTH = 0.5;     // current threshold for Fan activation in Amps

bool deepSleepActive = false;
bool loggingActive;        // Logging State
bool ButtonsActive = true;        // Physical Touch buttons active
bool FanActive = false;
bool htmlRestart = false;
bool deleteLog;
bool SDpresent;
String SDdata;
String Filename;
File bmpFS;
uint32_t seekOffset;
uint16_t w, h, row, col;
uint8_t  r, g, b;
uint16_t padding;

MAX30105 MAX30105;    //   ======= HR + SpO2 Settings =======
long irValue;
uint32_t ir, red;
double fred, fir;
double SpO2 = 0;  // raw SpO2 before low pass filtered
long delta;
byte irOffset = 0; // 0 - 90 , offset distance from sensor
byte constHRtop = 93 - irOffset;     // HR graph constraints
byte constHRbottom = 90 - irOffset;
byte ledBrightness = 220; // 130 - Options: 0=Off to 255=50mA
byte ledMode = 2; // Options: 1 = IR only, 2 = Red + IR on MH-ET LIVE MAX30102 board
int sampleRate = 3200; // Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
byte sampleAverage = 32;   // Options: 1, 2, 4, 8, 16, 32 --- 16
int pulseWidth = 215; // Options: 69, 118, 215, 411       --- 118
int adcRange = 16384; // Options: 2048, 4096, 8192, 16384

const byte RATE_SIZE = 4; //  Increase this for more HR averaging. 4 is good.
byte rates[RATE_SIZE];
byte rateSpot = 0;
long lastBeat = 0;
float beatsPerMinute;
int beatAvg;

int lastIR = 0;
int lastO2 = 0;
int i = 0;
int Num = 35;   //  50 calculate SpO2 by this sampling interval
double ESpO2 = 90.0; // initial value of estimated SpO2
double FSpO2 = 0.7;  // filter factor for estimated SpO2
double frate = 0.95; // 0.95 low pass filter for IR/red LED value to eliminate AC component
double avered = 0;
double aveir = 0;
double sumirrms = 0;
double sumredrms = 0;

RTC_DS3231 rtc;
bool rtcLostPower;

char LogFile[16];         // char & Strings
char RTCtimeLOG[10];
char RTClog[12];
int yr, mo, da, hr, mi, se;
String RTCt = "";
String RTCprint = "";
String SDloghead = "";
String RTCdate = "";
String ledBprint, currentLine, UVIsd, envData, PowerLog, tempProbes;

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
float mlxtemp;

MPU9250_asukiaaa IMU;
float aX, aY, aZ, aSqrt, gX, gY, gZ, mDirection, mX, mY, mZ;
uint8_t sensorId;

VEML6075 VML(0x10, Wire);
int UVI;

const int CO2TH = 2000;     // Sensor Thresholds
const int VOCTH = 250;
char pressure_value[4];
bool AirWarning;

float tempHDC, tempBME, tempCCS811, tempC, RH;
String pressure;
int CO2, alt, TVOC;
byte pCO2, pTVOC;
int prevCO2, prevTVOC;
byte fanGraph, TempGraph, RHgraph, CCS811err;
#define SEALEVELPRESSURE_HPA (1028.25) // sealevel Pressure Berlin

//                                 // INA219 current and voltage readings
Adafruit_INA260 ina260 = Adafruit_INA260();
#define R_SHUNT 0.00375
#define V_SHUNT_MAX 0.075
#define V_BUS_MAX 16
#define I_MAX_EXPECTED 20

float Amps, Volts, Watts;
int Svolt, Bvolt, Lvolt, currA, powMW, lastpowMW;
byte BatPercent;

#define tPAD1 4                  // I/O PINS
#define tPAD2 2
#define tPAD3 35
#define beep 33
#define fan 26
#define powerOFF 19

#define pwmLED 17  // PWM controlled LED output
#define pwmfreq 20000
#define ledChannel1 1
#define pwmresolution 12
byte ledB = 0;

#define tftPIN 27   // TFT backlight control
#define ledChannel2 2
byte tftBKL = 255;

CCS811 myCCS811(0x5B);     //      CCS811 Settings
ClosedCube_HDC1080 myHDC1080;
BME280 myBME280;

byte Ty = 220;            // graph static visual elements for graph page
byte edgeL = 5; // edgeL
byte box1Top = 5;
byte box1Bottom = 105;
byte box2Top = 120;
byte box2Bottom = 220;
byte boxHeight = 100;
byte boxWidth = 230;

WiFiServer server(80);
Preferences preferences;

int WiFiTimeout = 5; // WiFi tries to connect for x seconds
byte WiFistatus;
String header;
byte wifiNetworks;
String WiFiName;
String encryptionTypeDescription;

const char *ssid = mySSID; //  home WIFI
const char *password = myPassword;

const char *issid = myiSSID; //  iPhone WIFI
const char *ipassword = myiPassword;

const char *NTP_SERVER = "pool.ntp.org"; // NTP Time
const char *TZ_INFO = "CET-1CEST,M3.5.0,M10.5.0/3"; //  CET-1CEST,M3.5.0,M10.5.0/3  ,  CET-1CEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00  ,  WEST-1DWEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00
tm timeinfo;
time_t now;

void IRAM_ATTR buttonInterrupt1() {
  if (ButtonsActive) {
    TFTon();
    pageCount--;
    if (pageCount > MenuPages) pageCount = MenuPages;
  }
}
void IRAM_ATTR buttonInterrupt2() {
  if (ButtonsActive) {
    pageCount++;
    TFTon();
    if (pageCount > MenuPages) pageCount = 0;
  }
}
void IRAM_ATTR buttonInterrupt3() {
  if (ButtonsActive) {
    TFTon();
    if (pageCount == 3) irOffset += 5;
    if (pageCount == 5 || pageCount == 6) {
      scrollTFT -= 50;
      tft.fillScreen(TFT_BLACK);
      tft.setCursor(0, scrollTFT + 50);
    } else if (ledB == 0) {
      ledB = 250; // commands for dimming logic
    } else {
      ledB = 1;   // commands for dimming logic
    }
  }
}

void setup() //=========================================== SETUP ===========================================
{
  // Serial.begin(115200);
  tft.begin();
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_BLACK);
  TFTwidth = tft.width();
  TFTheight = tft.height();

  spiSD.begin(14, 25, 13, 15); // SCK, MISO, MOSI, CS
  spiSD.setFrequency(spiFreq);
  if (SD.begin(15, spiSD, spiFreq)) {
    SDpresent = true;
    loggingActive = true;
  } else {
    SDpresent = false;
    loggingActive = false;
  }

  tft.setTextColor(TFT_WHITE);
  tft.setTextDatum(MC_DATUM);
  tft.setTextSize(1);

  if (!SDpresent) {
    tft.pushImage(0, 0, TFTwidth, TFTheight, BuddhaRed240);
    tft.drawString("DON'T PANIC", TFTwidth / 2, 198, 4);
  } else {
    byte randNumber = random(1, 13);
    if (randNumber == 1) drawBmp("/UI/nasa240.bmp", 0, 0);   // 24bit
    if (randNumber == 2) drawBmp("/UI/nasab240.bmp", 0, 0);   // 24bit
    if (randNumber == 3) drawBmp("/UI/NasaWorm240.bmp", 0, 0);   // 24bit
    if (randNumber == 4) drawBmp("/UI/github240.bmp", 0, 0);   // 24bit
    if (randNumber == 5) drawBmp("/UI/deathstar240.bmp", 0, 0);   // 24bit
    if (randNumber == 6) drawBmp("/UI/MoonEarth240.bmp", 0, 0);   // 24bit
    if (randNumber == 7) drawBmp("/UI/Saturn240.bmp", 0, 0);   // 24bit
    if (randNumber == 8) drawBmp("/UI/Bahamas240.bmp", 0, 0);   // 24bit
    if (randNumber == 9) drawBmp("/UI/ISS240.bmp", 0, 0);   // 24bit
    if (randNumber == 10) drawBmp("/UI/River240.bmp", 0, 0);   // 24bit
    if (randNumber == 11) drawBmp("/UI/EarthNight240.bmp", 0, 0);   // 24bit
    if (randNumber == 12) drawBmp("/UI/Curiosity240.bmp", 0, 0);   // 24bit
    //if (randNumber == 13 && SDpresent) drawBmp("/UI/rebellion240.bmp", 0, 0);   // 24bit
    if (randNumber == 1 || randNumber == 2 || randNumber == 4 || randNumber == 5 || randNumber == 12) {
      tft.drawString("DON'T PANIC", TFTwidth / 2, 198, 4);
    }
  }

  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(I2C_SPEED_FAST);

  pinMode(powerOFF, OUTPUT);
  digitalWrite(powerOFF, HIGH);
  pinMode(fan, OUTPUT);
  digitalWrite(fan, LOW);
  pinMode(tPAD1, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(tPAD1), buttonInterrupt1, RISING);
  pinMode(tPAD2, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(tPAD2), buttonInterrupt2, RISING);
  pinMode(tPAD3, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(tPAD3), buttonInterrupt3, RISING);

  ledcAttachPin(pwmLED, ledChannel1);
  ledcSetup(ledChannel1, pwmfreq, pwmresolution);
  pinMode(tftPIN, OUTPUT);
  analogWrite(tftPIN, 255);

  tft.setTextColor(TFT_BLACK, TFT_INDIA); // Connect WiFi
  tft.setCursor(0, 225);
  tft.setTextSize(2);

  if ((digitalRead(tPAD2)) == HIGH) {
    WiFi.begin(issid, ipassword);
    tft.print("i ");
  } else {
    WiFi.begin(ssid, password);
    tft.print("h ");
  }

  while (WiFi.status() != WL_CONNECTED) {
    delay(30);
    if (millis() > WiFiTimeout * 1000)
      break;
  }

  if (WiFi.status() == WL_CONNECTED) {
    server.begin();
    configTime(0, 0, NTP_SERVER); // See https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv for Timezone codes for your region
    setenv("TZ", TZ_INFO, 1);
    delay(300);

    if (rtc.begin()) {
      time(&now);
      localtime_r(&now, &timeinfo);
      tft.print(" ");
    } else {
      tft.print("R");
    }

    tft.setTextDatum(TL_DATUM);
    if (rtc.lostPower()) {
      rtc.adjust(DateTime(uint32_t(now + 7200))); // + 3600
      tft.print("rR");
      rtcLostPower = true;
      tft.setTextColor(TFT_INDIA);
      tft.setTextSize(1);
      tft.drawString("Hard Reset ", 0, 0, 1);
    } else {
      tft.print("  ");
      rtcLostPower = false;
      tft.setTextColor(TFT_INDIA);
      tft.setTextSize(1);
      tft.drawString("Soft Reset ", 0, 0, 1);
    }
  } else {
    tft.println("W"); // WiFi Failed
  }

  Time(timeinfo);
  print_wakeup_reason();
  tft.setTextSize(2);
  tft.setTextColor(TFT_BLACK, TFT_INDIA);

  if (SDpresent) {
    tft.print("  ");
  } else {
    tft.print("SD");
  }

  mlx.begin();
  //  delay(80);

  myBME280.settings.commInterface = I2C_MODE; 
  myBME280.settings.I2CAddress = 0x76;
  myBME280.settings.runMode = 3;  // 1 = sleep, 2 = forced, 3 = normal
  myBME280.settings.tStandby = 5;    // 4 = 500ms, 5 = 1000ms, 0 = 0.5ms,
  myBME280.settings.filter = 4;     // 4
  myBME280.settings.tempOverSample = 8; // 5
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

  if (!MAX30105.begin(Wire, I2C_SPEED_FAST)) // Initialize MAX30102
  {
    tft.print("M");
    // MAX30105.enableDIETEMPRDY(); //Enable the temp ready interrupt.
  } else {
    MAX30105.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); // Configure sensor with these settings
    MAX30105.shutDown();
    tft.print(" ");
  }

  VML.begin(); // VEML6075 UV begin
  VML.setIntegration(T_100MS);

  if (VML.getID() > 0) {
    tft.print("V ");
  } else {
    tft.print("  ");
  }

  sensors.begin(); // OneWire Dallas Temp begin
  DTdevicecount = sensors.getDeviceCount();
  if (DTdevicecount < 7) {
    tft.setTextColor(TFT_WHITE, TFT_INDIA);
    tft.print(DTdevicecount);
    tft.setTextColor(TFT_BLACK, TFT_INDIA);
  } else {
    tft.print(" ");
  }
  sensors.setWaitForConversion(false);
  sensors.setResolution(tempProbe1, 9); // 9-12 Bit
  sensors.setResolution(tempProbe2, 9);
  sensors.setResolution(tempProbe3, 9);
  sensors.setResolution(tempProbe4, 9);
  sensors.setResolution(tempProbe5, 9);
  sensors.setResolution(tempProbe6, 9);
  sensors.setResolution(tempProbe7, 9);
  sensors.setHighAlarmTemp(tempProbe1, 28); // tempProbe, Threshold
  sensors.setHighAlarmTemp(tempProbe2, 28);
  sensors.setHighAlarmTemp(tempProbe3, 28);
  sensors.setHighAlarmTemp(tempProbe4, 28);
  sensors.setHighAlarmTemp(tempProbe5, 28);
  sensors.setHighAlarmTemp(tempProbe6, 28);
  sensors.setHighAlarmTemp(tempProbe7, 28);
  sensors.setLowAlarmTemp(tempProbe1, -10);
  sensors.setLowAlarmTemp(tempProbe2, -10);
  sensors.setLowAlarmTemp(tempProbe3, -10);
  sensors.setLowAlarmTemp(tempProbe4, -10);
  sensors.setLowAlarmTemp(tempProbe5, -10);
  sensors.setLowAlarmTemp(tempProbe6, -10);
  sensors.setLowAlarmTemp(tempProbe7, -10);


  if (ina260.begin()) {
    tft.print(" ");
    ina260.setMode(INA260_MODE_CONTINUOUS);
    ina260.setAveragingCount(INA260_COUNT_4); // 1, 4, 16, 64, 128, 256, 512, 1024
    ina260.setVoltageConversionTime(INA260_TIME_204_us); // 140_us, 204_us, 332_us, 558_us, 1_1_ms,
    ina260.setCurrentConversionTime(INA260_TIME_204_us); //
  } else {
    tft.print("i");
  }

  IMU.setWire(&Wire);
  uint8_t sensorId;
  if (IMU.readId(&sensorId) == 0) {
    tft.print("  ");
    IMU.beginAccel();
    IMU.beginGyro();
    IMU.beginMag();
    //    IMU.magXOffset = -35;    // You can set your own offset for mag values
    //    IMU.magYOffset = 10;
    //    IMU.magZOffset = 46;
  } else {
    tft.print("I ");
  }

  tft.print("v");
  tft.print(Revision);
  delay(400);

  preferences.begin("my - app", false);
  counter = preferences.getUInt("counter", 0);
  counter++;        // Increase counter by 1
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_DARKGREY, TFT_BLACK);
  tft.setCursor(96, 225);
  tft.print(counter);
  preferences.putUInt("counter", counter); // Store the counter to the Preferences
  preferences.end();                // Close the Preferences

  if (digitalRead(tPAD2) == HIGH && SD.exists(LogFile)) {
    SD.remove(LogFile);
    tone(beep, 3800, 6);
    delay(60);
    tone(beep, 3800, 6);
  }
  delay(400);
  tone(beep, 2400, 3);
}
// Setup Done.

void loop() //        =========================================== VOID LOOP ===========================================
{
  //   drawBmp("/Hex_Blur.bmp", 0, 0); // JPEGdecoder BPM print /w bodmer 4x speed upgrade fix drawBmp("/Tprobes240.bmp", 0, 0); // put .bpm on SD card
  // Serial.begin(115200);

  page0();     // Page 0  Home Page
  page1();     // Page 1  Dallas Temperature Probes & Voltage & Current
  page2();     // Page 2  MAX90614 -- doesnt work with other sensors active :(
  page3();     // Page 3  HeartRate SpO2
  page4();     // Page 4  Graph Co2, TVOC, Voltage & Current
  page5();     // Page 5  Diagnostics
  page6();     // Page 6  SD card Directory
  page7();     // Page 7  Info Page CO2
  page8();     // Page 8  Info Page TVOC

}

/////////////// END MAIN ///////////////

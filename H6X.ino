
/*=============================================================================================================================================================//
                                                         HEX Station (Health Environment Device)
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
  CCS811   - 0x5A -  Marshall Taylor, Nathan Seidle  https://github.com/sparkfun/CCS811_Air_Quality_Breakout
  VEML6075 -      -  Jonathan Dempsey  https://github.com/WifWaf/VEML6075
  MAX30102 -      -

  // Active:
  // Beeper | Bootup counter Current Sensor
  // CJMCU8128 | MAX30102
  // Error Detection [Wifi, CCS811] - WiFi and Current pin not working at the same time or under 4.2v rn
  // 

  =============================================================================================================================================================//
*/

#define Revision "  v7"

#include <WiFi.h>
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
// #include "hex.h"       //tft.pushImage(0, 0, 240, 240, Hex_Blur_240x240);    // put where image should be loaded

#include "MAX30105.h"       // sparkfun MAX3010X library
#include "heartRate.h"
MAX30105 particleSensor;

#include "time.h"


const int VT_PIN = 35;
const int AT_PIN = 34;
const int beep = 13;
//#define LED 2

int i = 0;//                                 ======= HR + SpO2 Settings =======
int Num = 30;             //  calculate SpO2 by this sampling interval

const byte RATE_SIZE = 5; //  Increase this for more HR averaging. 4 is good.
byte rates[RATE_SIZE];
byte rateSpot = 0;
long lastBeat = 0;
float beatsPerMinute;
int beatAvg;

double ESpO2 = 90.0;     //initial value of estimated SpO2
double FSpO2 = 0.7;      //filter factor for estimated SpO2
double frate = 0.94;     // 0.95 low pass filter for IR/red LED value to eliminate AC component
double avered = 0;
double aveir = 0;
double sumirrms = 0;
double sumredrms = 0;


const int tPIN1 = 4;           // capacitive touch button/pin
int buttonState = 0;       // current state of the button
int lastButtonState = 0;
int touchTH = 21;          // touch button/pin threshold !!! wire 10k ohm Pull-Down resistor to GND



CCS811 myCCS811(CCS811_ADDR);  //      CCS811 Settings
ClosedCube_HDC1080 myHDC1080;
BME280 myBME280;

WiFiServer server(80);
Preferences preferences;

const char* ssid       = mySSID;        //  WIFI
const char* password   = myPassword;

unsigned long previousTime = 0; // timeout wifi
const long timeoutTime = 15000; // 20000

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;
String header;

const int CO2TH = 1500;                 // Sensor Thresholds
const int VOCTH = 240;
char pressure_value[4];

int avgS = 15;   // Voltage & Current Sensing Samples
int Calarm = 1; // Current Alarm Threshold

const int low = (2000, 250);            // Beeper (freq, duration)
const int high = (4000, 350);
const int tick = (3000, 6);


void sensorXY()                          // ====== Voids ======
{
  tft.setCursor(6, 24);
  tft.setTextSize(2);
}
void errXY()
{
  tft.setCursor(90, 24);
  tft.setTextSize(2);
}

void printLocalTime()
{
  struct tm timeinfo;

  if (!getLocalTime(&timeinfo)) {
    tft.setCursor(150, 0);                   // Print Time
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.setTextSize(2);
    tft.println("Time Err");
    return;
  }
  tft.setCursor(144, 0);                   // Print Time
  tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
  tft.setTextSize(2);
  tft.println(&timeinfo, "%H:%M:%S");
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
  tft.fillRoundRect(0, 161, 75, 30, 3, TFT_DARKGREY);  // Box #1
  tft.drawRoundRect(0, 123, 75, 70, 3, TFT_MIDDLEGREY);
  tft.drawRoundRect(1, 124, 73, 68, 3, TFT_BLACK);

  tft.fillRoundRect(80, 161, 80, 30, 3, TFT_DARKGREY);  // Box #2
  tft.drawRoundRect(80, 123, 80, 70, 3, TFT_MIDDLEGREY);
  tft.drawRoundRect(81, 124, 78, 68, 3, TFT_BLACK);

  tft.fillRoundRect(165, 161, 75, 30, 3, TFT_DARKGREY);  // Box #3
  tft.drawRoundRect(165, 123, 75, 70, 3, TFT_MIDDLEGREY);
  tft.drawRoundRect(166, 124, 73, 68, 3, TFT_BLACK);
}

void setup()//=========================================== SETUP ===========================================
{

  //Serial.begin(115200);
  //delay(500);

  //pinMode(LED, OUTPUT );                           // Output Pin Define, Setup LED High
  //pinMode(BLK, OUTPUT);                      // screen off
  //digitalWrite(LED, HIGH);
  //digitalWrite(BLK, HIGH);

  tft.begin();                          // TFT Initialize
  tft.setSwapBytes(true);
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);


  {
    tft.setTextColor(TFT_WHITE);             // Connect WiFi
    tft.setCursor(0, 25);
    tft.setTextSize(2);
    tft.println();
    tft.printf("Connecting %s ", ssid);
    tft.println();
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      tft.println(" .");
      delay(200);
      if ((millis() / 1000) > 5)
        break;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
      server.begin();
      tft.setTextColor(TFT_GREEN);
      tft.println("CONNECTED");
      delay(5);
      tft.setTextColor(TFT_WHITE);
      Serial.println(WiFi.localIP());
      tft.println(WiFi.localIP());
      configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
      printLocalTime();
      delay(500);
    } else {
      tft.setTextColor(TFT_RED);
      tft.println("WiFi Failed");
      //tone(beep, low);
      //delay(300);
    }


    WiFi.disconnect(true);                                    // disconnect WiFi
    WiFi.mode(WIFI_OFF);



    myBME280.settings.commInterface = I2C_MODE;              // Initialize CCS811
    myBME280.settings.I2CAddress = 0x76;
    myBME280.settings.runMode = 3;
    myBME280.settings.tStandby = 0;
    myBME280.settings.filter = 4; // 3
    myBME280.settings.tempOverSample = 6; // 5
    myBME280.settings.pressOverSample = 8;
    myBME280.settings.humidOverSample = 8;
    myBME280.begin();
    myHDC1080.begin(0x40);
    CCS811Core::status returnCode = myCCS811.begin();



    if (!particleSensor.begin(Wire, I2C_SPEED_FAST))         // Initialize MAX20103
    {
      Serial.println("MAX30102 not found");
      particleSensor.enableDIETEMPRDY(); //Enable the temp ready interrupt. This is required.
    }

    //Setup to sense a nice looking saw tooth on the plotter
    byte ledBrightness = 205; //Options: 0=Off to 255=50mA
    byte sampleAverage = 16; //Options: 1, 2, 4, 8, 16, 32
    byte ledMode = 2; //Options: 1 = IR only, 2 = Red + IR on MH-ET LIVE MAX30102 board
    int sampleRate = 400; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
    int pulseWidth = 118; //Options: 69, 118, 215, 411
    int adcRange = 16384; //Options: 2048, 4096, 8192, 16384

    particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings
    particleSensor.shutDown();
    //particleSensor.setPulseAmplitudeRed(0x00);  // LED OFF Works!
    //particleSensor.setPulseAmplitudeIR(0x00);

    tft.fillScreen(TFT_BLACK);

    preferences.begin("my-app", false);                       // Bootup Counter
    //preferences.clear(); // Remove all preferences under the opened namespace
    //preferences.remove("counter"); // Or remove the counter key only
    unsigned int counter = preferences.getUInt("counter", 0);
    counter++;  // Increase counter by 1
    tft.setTextColor(TFT_DARKGREY);
    tft.setCursor(105, 225);
    tft.setTextSize(2);
    tft.printf("%u\n", counter);
    preferences.putUInt("counter", counter);// Store the counter to the Preferences
    preferences.end();   // Close the Preferences

    staticGFX(); // Print Static GFX Elements

  }
}                                                                      // Setup Done.


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

  if (WiFi.status() == WL_CONNECTED) {
    printLocalTime();                                                       // Print Time void
  } else {
    tft.setCursor(140, 0);                   // Print Time
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.setTextSize(2);
    tft.println("Wifi Err");
  }

  int at_temp = analogRead(AT_PIN);
  int vt_temp = analogRead(VT_PIN);

  unsigned int x = 0;                                                    // Calculate & Print POWER
  float VcsValue = 0.0, VSamples = 0.0, AvgVcs = 0.0, voltage = 0.0;

  for (int x = 0; x < avgS; x++) { //Get avgS samples
    VSamples = VSamples + vt_temp;  //Add samples together
    delay (3); // let ADC settle before next sample 3ms
  }
  AvgVcs = VSamples / avgS; //Taking Average of Samples
  voltage = AvgVcs / 4095 * 17.8;

  unsigned int y = 0;
  float AcsValue = 0.0, ASamples = 0.0, AvgAcs = 0.0, current = 0.0;

  for (int y = 0; y < avgS; y++) { //Get avgS samples
    ASamples = ASamples + at_temp;  //Add samples together
    delay (3); // let ADC settle before next sample 3ms
  }
  AvgAcs = ASamples / avgS; //Taking Average of Samples
  current = AvgAcs / 4095 * 3;

  tft.setTextSize(2);
  tft.setTextColor(TFT_INDIA, TFT_BLACK);
  tft.setCursor(8, 203);
  tft.print(voltage, 1);
  tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
  tft.print("v");

  if (current > Calarm) {
    tft.setTextColor(TFT_RED, TFT_BLACK);
  } else {
    tft.setTextColor(TFT_GOLD, TFT_BLACK);
  }

  tft.setCursor(67, 203);
  tft.print(current, 1);
  tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
  tft.print("a");

  tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
  tft.setCursor(208, 203);
  tft.print(touchRead(tPIN1));

  //float maHspent = ((current * time) / voltage); // for reading in mAh
  //tft.setTextColor(TFT_NAVY, TFT_BLACK);
  //tft.print(maHspent);
  //tft.println(" maH spent     ");

  //Serial.print(CO2 / 10); // divided by 10 to make easier to see         // Serial Plotter Logging
  //Serial.print(" ");
  //Serial.print(TVOC);
  //Serial.println("");

  printCCS811();                                                 //// CCS811 Function /w error detection////

  readHRO2();                                                   //// HeartRate SpO2 Function /w touch button detection ////


  tft.setCursor(0, 225);                                 // Time elapsed & Code Revision
  tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.print(minElapsed);
  tft.setTextColor(TFT_DARKCYAN, TFT_BLACK);
  tft.print("min");
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.setCursor(191, 225);
  tft.print(Revision);


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
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("<font style='font-family:electric toaster'>");
            client.println();
            client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
            client.println("<meta name='apple-mobile-web-app-status-bar-style' content='white-translucent' />");
            client.println("<HTML>");              // Header
            client.println("<HEAD>");
            client.println("<head><title>HEX 6</title></head>");
            client.println("<BODY>");               //Body
            client.println("<body><div style='text-align: middle'>");
            client.println("<body><body bgcolor='#383838'>");
            client.println("<br />");
            client.println("<a href=\"/?button1on\"\"><button1 style='font-size:300%; background-color:#383838; color:green;border-radius:5px; position:absolute; top:20px; left:30px;'>Sensors</a>");
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
  }
  delay(12);
}


/////////////// END MAIN ///////////////

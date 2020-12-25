#include <WiFi.h>
#include <Preferences.h>
#include <SPI.h>
#include <Adafruit_GFX.h>               // Core graphics library
#include <Adafruit_ST7789.h>            // Hardware-specific library for ST7789
#include <Credentials.h>
#include <ESP32Servo.h>                 // Beeps
#include <SparkFunCCS811.h>             // CJMCU-8128 - CCS811 [from Banggood with all 3 sensors]
#include <SparkFunBME280.h>             // BME280
#include <ClosedCube_HDC1080.h>         // HDC1080
#include "time.h"

//// Define ////

#define Revision "v1.9"
// Active:
// Beeper | Bootup counter |  Error Detection [Wifi, CCS811] | Current Sensor
// CJMCU8128 |
// Serial logging

#define TFT_CS 14                       // chip select pin // TFT/LCD Screen
#define TFT_DC 32                       // data/command pin
#define TFT_RST 15                      // reset pin, or set to -1 and connect to Arduino RESET pin
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

#define LED 2                           // Pinouts & I2Cs
int beep = 13;

//#define BLK 36
//#define PCF8575 0x10                  // I2C Breakout Board PCF8575
#define CCS811_ADDR 0x5A                // CCS811 Env. Connect

CCS811 myCCS811(CCS811_ADDR);
ClosedCube_HDC1080 myHDC1080;
BME280 myBME280;
WiFiServer server(80);
Preferences preferences;

const char* ssid       = mySSID;        //  Integers And Constants
const char* password   = myPassword;

unsigned long previousTime = 0; // timeout wifi
const long timeoutTime = 20000; // 20000

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;
String header;

const int CO2TH = 1500;                 // Sensor Thresholds
const int VOCTH = 240;
char pressure_value[4];

const int low = (2000, 350);            // Beeper (freq, duration)
const int high = (4000, 350);
const int tick = (3000, 6);

void sensorXY()                          // Voids
{
  tft.setCursor(5, 24);
  tft.setTextSize(2);
}
void errXY()
{
  tft.setCursor(100, 24);
  tft.setTextSize(2);
}
void batXY()
{
  tft.setCursor(145, 24);
  tft.setTextSize(2);
}

void printLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    tft.setCursor(70, 0);
    tft.setTextColor(INDIA, BLACK);
    tft.setTextSize(1, 2);
    tft.println("Time Failed");
    return;
  }
  tft.setCursor(74, 0);                   // Print Time
  tft.setTextColor(GREYA, BLACK);
  tft.setTextSize(2);
  tft.println(&timeinfo, "%H:%M:%S");
}



void setup()//                                              /    /   /   /  /  / //////// VOID SETUP //////// /  /  /   /    /
{

  Serial.begin(115200);
  delay(800);

  //pinMode(LED, OUTPUT );                           // Output Pin Define, Setup LED High
  //pinMode(BLK, OUTPUT);                      // screen off
  //digitalWrite(LED, HIGH);
  //digitalWrite(BLK, HIGH);

  tft.init(240, 240);                          // TFT Initialize
  tft.setRotation(2);
  tft.fillScreen(BLACK);

  {
    tft.setTextColor(WHITE, BLACK);             // Connect WiFi
    tft.setCursor(5, 15);
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
      tft.setTextColor(DARKGREEN);
      tft.println("CONNECTED");
      delay(50);
      tft.setTextColor(WHITE);
      Serial.println(WiFi.localIP());
      tft.println(WiFi.localIP());
      delay(500);
    } else {
      tft.setTextColor(RED);
      tft.println(" WiFi Failed");
      tone(beep, low);
      delay(200);
    }

    delay(100);
    tft.fillScreen(BLACK);
    //WiFi.disconnect(true);                                    // disconnect WiFi
    //WiFi.mode(WIFI_OFF);

    {
      myBME280.settings.commInterface = I2C_MODE;              // CCS811 Sensor Setup
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
      //bool error = myCCS811.checkForStatusError();
    }
    preferences.begin("my-app", false);                       // Bootup Counter
    //preferences.clear(); // Remove all preferences under the opened namespace
    //preferences.remove("counter"); // Or remove the counter key only
    unsigned int counter = preferences.getUInt("counter", 0);
    counter++;  // Increase counter by 1
    tft.setTextColor(CYAN, BLACK);
    tft.setCursor(100, 225);
    tft.setTextSize(2);
    tft.printf("%u\n", counter);
    preferences.putUInt("counter", counter);// Store the counter to the Preferences
    preferences.end();   // Close the Preferences

  }
  //digitalWrite(LED, LOW);
}                             // Setup Done.




void loop()                                                                  ///////////////VOID LOOP///////////////
{

  //tft.fillScreen(BLACK);

  const int currentTime = millis() / 1000 / 60;  // in min            /// INT LOOP
  const int temp = myHDC1080.readTemperature() / 1.225;
  const int tempBME = myBME280.readTempC() / 1.225;
  const int RH = myHDC1080.readHumidity();
  const int CO2 = myCCS811.getCO2();
  const int TVOC = myCCS811.getTVOC();
  const int alt = (myBME280.readFloatAltitudeMeters());
  String pressure = String(myBME280.readFloatPressure() * 0.000145038 / 714); // in ATM
  pressure.toCharArray(pressure_value, 4);


  //tft.fillRoundRect(65, 0, 224, 1, 1, GREYC);                // GFX Static Elements
  tft.fillRoundRect(6, 20, 224, 1, 1, GREYB);
  tft.fillRoundRect(6, 41, 224, 1, 1, GREYB);

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();                                                       // Print Time void

  Serial.print(CO2 / 10); // divided by 10 to make easier to see         // Serial Plotter Logging
  Serial.print(" ");
  Serial.print(TVOC);
  Serial.print(" ");
  //Serial.print(tempBME);
  //Serial.print(" ");
  //Serial.print(RH);
  //Serial.print(" ");
  //Serial.print(current);
  //Serial.print(" ");
  //Serial.print(voltage);
  Serial.println("");

  if (myCCS811.dataAvailable())                    //// CCS811 Data Screen Print /////
  {
    myCCS811.readAlgorithmResults(); //compensating the CCS811 with humidity and temperature readings from the HDC1080
    myCCS811.setEnvironmentalData(RH, temp);

    {
      //tft.setCursor(0, 0);
      //tft.setTextColor(YELLOW, BLACK);         // Print Alt
      //tft.print(alt);
      //tft.setTextColor(GREYA, BLACK);
      //tft.println("m ");

      tft.setCursor(0, 0);                   // Print Temp
      tft.setTextSize(2);
      tft.setTextColor(YELLOW, BLACK);
      tft.print(tempBME);
      tft.setTextColor(GREYA, BLACK);
      tft.println("C");

      tft.setCursor(0, 61);
      tft.setTextSize(3);
      tft.setTextColor(GREYA, BLACK);

      //tft.print("  Atm ");                // Print ATM
      //tft.setTextColor(WHITE, BLACK);
      //tft.print(pressure);
      //tft.setTextColor(GREYA, BLACK);
      //tft.println("a  ");

      tft.print("   RH ");                // Print RH
      tft.setTextColor(WHITE, BLACK);
      tft.print(RH);
      tft.setTextColor(GREYA, BLACK);
      tft.println("% ");
      tft.println();

      tft.print("  CO2 ");                 // Print CO2
      if (CO2 > CO2TH) {                   // Air Quality Alarm Beeper Dependent on Sensor Values and Alarm Threshold
        tft.setTextColor(INDIA, BLACK);
        tone(beep, (800 + ((CO2 - 600) / 8)), (((CO2 - 1300) / 200)));
      } else {
        tft.setTextColor(WHITE, BLACK);
      }
      tft.print(CO2);
      tft.println("   ");

      tft.setTextColor(GREYA, BLACK);      // Print tVOC
      tft.print(" tVOC ");
      if (TVOC > VOCTH) {
        tft.setTextColor(INDIA, BLACK);
        tone(beep, (600 + TVOC) / 10), ((CO2 - 1300) / 200);
      } else {
        tft.setTextColor(WHITE, BLACK);
      }
      tft.print(TVOC);
      tft.println("   ");
    }
  }

  tft.setCursor(0, 225);
  tft.setTextColor(GREYA, BLACK);
  tft.setTextSize(2);
  tft.setTextColor(CYAN, BLACK);         // Time elapsed and Code Revision
  tft.print(currentTime);
  tft.setTextColor(DARKCYAN, BLACK);
  tft.print("min");
  tft.setTextColor(CYAN, BLACK);
  tft.setCursor(191, 225);
  tft.print(Revision);
  
  if (myCCS811.checkForStatusError() > 0) {                         //// CCS811 Error Check LIVE no beeping
    CCS811Core::status returnCode2 = myCCS811.begin();
    tft.setTextColor(RED, BLACK);
    sensorXY();
    tft.print("Sensors");
    errXY();
    switch ( returnCode2 )
    {
      case CCS811Core::SENSOR_ID_ERROR:
        tft.print("ID");
        break;
      case CCS811Core::SENSOR_I2C_ERROR:
        tft.print("I2C");
        break;
      case CCS811Core::SENSOR_INTERNAL_ERROR:
        tft.print("ITRNL");
        break;
      case CCS811Core::SENSOR_GENERIC_ERROR:
        tft.print("GNRL");
        break;
    }
  } else {
    sensorXY();
    tft.setTextColor(WHITE, BLACK);
    tft.print("Sensors     ");

  }


  WiFiClient client = server.available();                           ////  WiFi Print to Local IP  ////

  if (client)
  {
    int ccs811 = myCCS811.checkForStatusError();
    sensorXY();
    tft.setTextColor(GREEN);
    tft.print("Sensors");
    String currentLine = ""; //Storing the incoming data in the string
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
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
            client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
            client.println("<HTML>");              // Header
            client.println("<HEAD>");
            client.println("<head><title>HEX 6</title></head>");
            client.println("<BODY>");               //Body
            client.println("<body><div style='text-align: left'>");
            client.println("<body><body bgcolor='#383838'>");
            client.println("<br />");
            if (ccs811 < 0.1) {
              client.println("<a href=\"/?button1on\"\"><button1 style='font-size:300%; background-color:#383838; color:green;border-radius:5px; position:absolute; top:20px; left:30px;'>Sensors</a>");
            } else {
              client.println("<a href=\"/?button1off\"\"><button2 style='font-size:300%; background-color:#383838; color:red;border-radius:5px; position:absolute; top:20px; left:30px;'>Sensors</a>");
            }
            client.println("<br />");
            client.println("<br />");
            client.print("<p style=\"text-align: left; font-size:300%; color: white\"> Altitude: ");
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
            client.print(currentTime);
            client.print("m <br/>");
            client.print("<br/>");
            if (ccs811 > 0) {                     // ccs811 Error check - if yes, set text RED
              CCS811Core::status returnCode = myCCS811.begin();
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

  delay(100);
}


/////////////// END MAIN ///////////////

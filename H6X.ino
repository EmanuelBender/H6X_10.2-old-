#include <WiFi.h>
#include <Preferences.h>
#include <SPI.h>
#include <Wire.h>
#include <Credentials.h>
#include <ESP32Servo.h>                 // Beeps
#include <SparkFunCCS811.h>             // CJMCU-8128 - CCS811 [from Banggood with all 3 sensors]
#include <SparkFunBME280.h>             // BME280
#include <ClosedCube_HDC1080.h>         // HDC1080
#include <TFT_eSPI.h>                   // Hardware-specific library
#include "time.h"

//                                      //  Define

#define Revision "v1.9.1"
// Active:
// Beeper | Bootup counter | Voltage & Current Sensor
// CJMCU8128 |
// Serial logging
// Error Detection [Wifi, CCS811]

#define VT_PIN 35
#define AT_PIN 34

#define LED 2                           // Pinouts & I2Cs
#define beep 13

//#define PCF8575 0x10                  // I2C Breakout Board PCF8575
#define CCS811_ADDR 0x5A                // CCS811 Env. Connect

CCS811 myCCS811(CCS811_ADDR);
ClosedCube_HDC1080 myHDC1080;
BME280 myBME280;

WiFiServer server(80);
Preferences preferences;
TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

const char* ssid       = mySSID;        //  Integers And Constants
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

void sensorXY()                          // Voids
{
  tft.setCursor(6, 24);
  tft.setTextSize(2);
}
void errXY()
{
  tft.setCursor(90, 24);
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
    tft.setCursor(72, 0);                   // Print Time
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.setTextSize(2);
    tft.println("Time Failed");
    return;
  }
  tft.setCursor(74, 0);                   // Print Time
  tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
  tft.setTextSize(2);
  tft.println(&timeinfo, "%H:%M:%S");
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
    tft.setTextColor(TFT_WHITE;             // Connect WiFi
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
      tft.setTextColor(TFT_GREEN);
      tft.println("CONNECTED");
      delay(50);
      tft.setTextColor(TFT_WHITE);
      Serial.println(WiFi.localIP());
      tft.println(WiFi.localIP());
      delay(500);
    } else {
      tft.setTextColor(TFT_RED);
      tft.println(" WiFi Failed");
      tone(beep, low);
      delay(200);
    }

    tft.fillScreen(TFT_BLACK);
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    printLocalTime();
    WiFi.disconnect(true);                                    // disconnect WiFi
    WiFi.mode(WIFI_OFF);

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

    }
    tft.fillScreen(TFT_BLACK);
    preferences.begin("my-app", false);                       // Bootup Counter
    //preferences.clear(); // Remove all preferences under the opened namespace
    //preferences.remove("counter"); // Or remove the counter key only
    unsigned int counter = preferences.getUInt("counter", 0);
    counter++;  // Increase counter by 1
    tft.setTextColor(TFT_DARKGREY, TFT_BLACK);
    tft.setCursor(100, 225);
    tft.setTextSize(2);
    tft.printf("%u\n", counter);
    preferences.putUInt("counter", counter);// Store the counter to the Preferences
    preferences.end();   // Close the Preferences

  }

  tft.drawRoundRect(0, 19, 240, 24, 4, TFT_MIDDLEGREY);                // GFX Static Elements
  tft.fillRoundRect(0, 50, 75, 30, 3, TFT_MIDDLEGREY);
  tft.fillRoundRect(80, 50, 80, 30, 3, TFT_MIDDLEGREY);
  tft.fillRoundRect(165, 50, 75, 30, 3, TFT_MIDDLEGREY);

  tft.drawRoundRect(0, 50, 75, 70, 3, TFT_MIDDLEGREY);
  tft.drawRoundRect(80, 50, 80, 70, 3, TFT_MIDDLEGREY);
  tft.drawRoundRect(165, 50, 75, 70, 3, TFT_MIDDLEGREY);

  tft.drawRoundRect(1, 51, 73, 68, 3, TFT_BLACK);
  tft.drawRoundRect(81, 51, 78, 68, 3, TFT_BLACK);
  tft.drawRoundRect(166, 51, 73, 68, 3, TFT_BLACK);
}                                                                      // Setup Done.


void loop()//=========================================== VOID LOOP ===========================================
{

  const int minElapsed = millis() / 1000 / 60;  // in min            /// INT LOOP
  const int temp = myHDC1080.readTemperature() / 1.225;
  const int tempBME = myBME280.readTempC() / 1.225;
  const int RH = myHDC1080.readHumidity();
  const int CO2 = myCCS811.getCO2();
  const int TVOC = myCCS811.getTVOC();
  const int alt = (myBME280.readFloatAltitudeMeters());
  String pressure = String(myBME280.readFloatPressure() * 0.000145038 / 714); // in ATM
  pressure.toCharArray(pressure_value, 4);

  printLocalTime();                                                       // Print Time void

  int at_temp = analogRead(AT_PIN);
  int vt_temp = analogRead(VT_PIN);

  unsigned int x = 0;
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


  if (current > Calarm) {
    tft.setTextColor(TFT_RED, TFT_BLACK);

  } else {
    tft.setTextColor(TFT_GOLD, TFT_BLACK);
  }
  tft.setTextSize(2);
  tft.setCursor(200, 0);
  tft.print(current, 1);

  tft.setTextColor(TFT_INDIA, TFT_BLACK);
  tft.setCursor(200, 24);
  tft.print(voltage, 1);

  //float W = (voltage * current);
  //tft.print(W, 2);
  //tft.println("W  ");

  //float maHspent = ((current * time) / voltage); // for reading in mAh
  //tft.setTextColor(TFT_NAVY, TFT_BLACK);
  //tft.print(maHspent);
  //tft.println(" maH spent     ");

  Serial.print(CO2 / 10); // divided by 10 to make easier to see         // Serial Plotter Logging
  Serial.print(" ");
  Serial.print(TVOC);
  Serial.println("");

  if (myCCS811.dataAvailable())                    //// CCS811 Data Screen Print /////
  {
    myCCS811.readAlgorithmResults(); //compensating the CCS811 with humidity and temperature readings from the HDC1080
    myCCS811.setEnvironmentalData(RH, temp);

    //tft.setCursor(0, 0);
    //tft.setTextColor(YELLOW, TFT_BLACK);         // Print Alt
    //tft.print(alt);
    //tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
    //tft.println("m ");

    tft.setCursor(0, 0);
    tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);// Print Temp
    tft.setTextSize(2);

    if (tempBME < 15) {
      tft.setTextColor(TFT_CYAN, TFT_BLACK);
    }
    if (tempBME > 28) {
      tft.setTextColor(TFT_ORANGE, TFT_BLACK);
    }
    if (tempBME > 35) {
      tft.setTextColor(TFT_RED, TFT_BLACK);
    }
    
    tft.print(tempBME);
    tft.setTextSize(1);
    tft.print("o ");

    //tft.print("  Atm ");                    // Print ATM
    //tft.setTextColor(TFT_WHITE, TFT_BLACK);
    //tft.print(pressure);
    //tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
    //tft.println("a  ");

    tft.setTextSize(3);
    tft.setCursor(11, 55);
    tft.setTextColor(TFT_BLACK, TFT_MIDDLEGREY);
    tft.print("CO2");
    tft.setCursor(85, 55);
    tft.print("tVOC");
    tft.setCursor(186, 55);
    tft.print("RH");

    if (CO2 > CO2TH) {    // Air Quality Alarm Beeper Dependent on Sensor Values and Alarm Threshold
      tft.setTextColor(TFT_RED, TFT_BLACK);
      tone(beep, (800 + ((CO2 - 600) / 8)), ((CO2 - 1200) / 200));
      delay(30);
      tone(beep, (800 + ((CO2 - 600) / 8)), ((CO2 - 1200) / 200));
    } else {
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
    }
    tft.setCursor(3, 89);
    tft.print(CO2);
    tft.println(" ");

    tft.setCursor(95, 89);
    if (TVOC > 9) {
      tft.setCursor(85, 89);
    }
    if (TVOC > 99) {
      tft.setCursor(77, 89);
    }

    if (TVOC > VOCTH) {
      tft.setTextColor(TFT_RED, TFT_BLACK);
      //tone(beep, (600 + TVOC) / 9), ((CO2 - 1200) / 200);
    } else {
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
    }
    tft.print(" ");
    tft.print(TVOC);
    tft.println(" ");
  }

  tft.setCursor(178, 89);// Print RH
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(3);
  tft.print(RH);
  tft.println("%");

  tft.setCursor(0, 225);                                 // Time elapsed and Code Revision
  tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.print(minElapsed);
  tft.setTextColor(TFT_DARKCYAN, TFT_BLACK);
  tft.print("min");
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.setCursor(191, 225);
  tft.print(Revision);

  if (myCCS811.checkForStatusError() > 0) {                         //// CCS811 Error Check LIVE no beeping
    CCS811Core::status returnCode2 = myCCS811.begin();
    tft.setTextColor(TFT_RED, TFT_BLACK);
    sensorXY();
    tft.print("Status");
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
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.print("Status     ");

  }


  WiFiClient client = server.available();                           ////  WiFi Print to Local IP  ////
  if (client)
  {
    int ccs811 = myCCS811.checkForStatusError();
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
            if (ccs811 < 0.1) {
              client.println("<a href=\"/?button1on\"\"><button1 style='font-size:300%; background-color:#383838; color:green;border-radius:5px; position:absolute; top:20px; left:30px;'>Sensors</a>");
            } else {
              client.println("<a href=\"/?button1off\"\"><button2 style='font-size:300%; background-color:#383838; color:red;border-radius:5px; position:absolute; top:20px; left:30px;'>Sensors</a>");
            }
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

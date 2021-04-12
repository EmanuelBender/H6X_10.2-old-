#include <pgmspace.h>

bool wifiPrint() {

  WiFiClient client = server.available();                           ////  WiFi Print to Local IP  //// if (client)
  if (client) {

    pressure.toCharArray(pressure_value, 4);
    currentTime = millis();
    previousTime = currentTime;
    currentLine = ""; //Storing the incoming data in the string

    while (client.connected() && currentTime - previousTime <= 3000) {  // loop while the client's connected if (client.available())  //if there issome client data available
      currentTime = millis();
      if (client.available()) {

        tft.pushImage(wifiX, 2, 12, 12, WifiG12);

        char c = client.read(); // read a byte
        header += c;
        if (c == '\n') // check for newline character,
        {
          if (currentLine.length() == 0) //if line is blank it means its the end of the client HTTP request
          {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            if (header.indexOf("GET /TFT/off") >= 0) {
              TFTon();
            } else if (header.indexOf("GET /TFT/on") >= 0) {
              TFToff();
            }

            if (pageCount == 3) ledB = 0;
            if (header.indexOf("GET /LED/off") >= 0) {
              ledB = 250;
            } else if (header.indexOf("GET /LED/on") >= 0) {
              ledB = 1;
            }


            if (header.indexOf("GET /LOG/off") >= 0) {
              loggingActive = true;
            } else if (header.indexOf("GET /LOG/on") >= 0) {
              loggingActive = false;
            }

            if (header.indexOf("GET /Powersave/off") >= 0) {      // Low Power Mode
              deepSleepActive = true;
              setCpuFrequencyMhz(80);
              myCCS811.setDriveMode(3); // 0=idle, 1=1sec, 2=10sec, 3=60sec, 4=RAW
              TFToff();
              checkScreenState();
              ledB = 0;
            } else if (header.indexOf("GET /Powersave/on") >= 0) {
              if (Volts > 6.8) {
                deepSleepActive = false;
                setCpuFrequencyMhz(240);
                myCCS811.setDriveMode(1); // 0=idle, 1=1sec, 2=10sec, 3=60sec, 4=RAW
                TFTon();
                checkScreenState();
              }
            }

            if (header.indexOf("GET /WFI/off") >= 0) {
            } else if (header.indexOf("GET /WFI/on") >= 0) {
              client.stop();
              WiFi.disconnect(true);
              WiFi.mode(WIFI_OFF);
            }

            if (header.indexOf("GET /PAGE/next") >= 0) {
              pageCount++;
              if (pageCount > MenuPages) pageCount = 0;
            }
            if (header.indexOf("GET /PAGE/back") >= 0) {
              pageCount--;
              if (pageCount == 255) pageCount = 8;
            }

            if (header.indexOf("GET /RST") >= 0) {
              htmlRestart = 1;
              preferences.begin("my - app", false);
              preferences.putUInt("htmlRestart", htmlRestart); // Store the counter to the Preferences
              preferences.end();
              ESP.restart();
            }
            if (header.indexOf("GET /LOG/del") >= 0) {
              deleteLog = true;
              if (SD.exists(LogFile)) {
                SD.remove(LogFile);
                tone(beep, 3800, 6);
                delay(60);
                tone(beep, 3800, 6);

                print_wakeup_reason();
              }
            }

            if (header.indexOf("GET /SLP/off") >= 0) {
              deepSleepActive = true;
            } else if (header.indexOf("GET /SLP/on") >= 0) {
              deepSleepActive = false;
            }
            if (header.indexOf("GET /WKE/one") >= 0) {
              sleepWakeupTime = 600;
              //esp_sleep_enable_timer_wakeup(sleepWakeupTime * uS_TO_S_FACTOR);
            } else if (header.indexOf("GET /WKE/ten") >= 0) {
              sleepWakeupTime = 60;
              //esp_sleep_enable_timer_wakeup(sleepWakeupTime * uS_TO_S_FACTOR);
            }

            String HTMLpage = "";

            HTMLpage += "<!DOCTYPE html><html>";
            HTMLpage += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
            HTMLpage += "<link rel=\"icon\" href=\"data:, \">";
            HTMLpage += "<meta http-equiv=\"refresh\" content=\"2\";url=/ \"></head>";

            HTMLpage += "<body><body bgcolor = '#000000'>";

            // Web Page Heading
            HTMLpage += "<body>";
            HTMLpage += "<head><title>ESP32</title></head> ";

            HTMLpage += "<table style=width:\"25%\"; font-size: \"200%\"; text-align:\"center\">";
            HTMLpage += "<tr>";
            HTMLpage += "<th>";
            HTMLpage += Volts;
            HTMLpage += " Volts</th>";
            HTMLpage += "<th>";
            HTMLpage += Amps;
            HTMLpage += " Amps</th>";

            HTMLpage += "<tr>";
            HTMLpage += "<th>Alt</th>";
            HTMLpage += "<th>Press</th>";
            HTMLpage += "</tr>";
            HTMLpage += "<tr>";
            HTMLpage += "<td>";
            HTMLpage += alt;
            HTMLpage += "m</td>";
            HTMLpage += "<td>";
            HTMLpage += pressure;
            HTMLpage += "</td></tr>";

            HTMLpage += "<tr><th>Temp</th>";
            HTMLpage += "<th>RH</th>";
            HTMLpage += "</tr>";
            HTMLpage += "<tr>";
            HTMLpage += "<td>";
            HTMLpage += tempBME;
            HTMLpage += "<sup>o</sup></td>";
            HTMLpage += "<td>";
            HTMLpage += RH;
            HTMLpage += "%</td>";
            HTMLpage += "</tr>";

            HTMLpage += "<tr>";
            HTMLpage += "<th>CO<sup>2</sup></th>";
            HTMLpage += "<th><sub>t</sub>VOC</th>";
            HTMLpage += "</tr>";
            HTMLpage += "<tr>";
            HTMLpage += "<td>";
            HTMLpage += CO2;
            HTMLpage += "ppm</td>";
            HTMLpage += "<td>";
            HTMLpage += TVOC;
            HTMLpage += "ppm</td>";
            HTMLpage += "</tr>";

            HTMLpage += "</table>";

            HTMLpage += "<b>UV </b>";
            HTMLpage += UVI;
            HTMLpage += "<br><b>BodyTemp </b>";
            mlxtemp = mlx.readObjectTempC();
            HTMLpage += mlxtemp;
            HTMLpage += "<br>";
            loopEndT = 1000 / loopEndT;
            HTMLpage += "<b>";
            HTMLpage += loopEndT;
            HTMLpage += "</b>";
            HTMLpage += " fps";
            HTMLpage += "<br>";
            //            HTMLpage += "<br>";

            client.println(HTMLpage);

            client.print(minElapsed);
            client.print("m Runtime<br/>");

            client.print("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; color: white;}");
            client.print(".button { background-color: #4CAF50; border: 2px; color: white; padding: 8px 35px;");
            client.print("text-decoration: none; font-size: 22px; margin: 2px; cursor: pointer;}");
            client.print(".button2 {background-color: #555555;} </style></head>");
            client.print("<p style=\"font-size:120%; text-align: center\">");

            if (getCpuFrequencyMhz() == 80) {
              client.print("<a href=\"/Powersave/on\"><button class=\"button\">PWRsave</button></a>");
            } else {
              client.print("<a href=\"/Powersave/off\"><button class=\"button button2\">PWRsave</button></a>");
            }

            client.print("<br/>");
            if (deepSleepActive) {
              client.print("<a href=\"/SLP/on\"><button class=\"button\">Sleep</button></a>");
            } else {
              client.print("<a href=\"/SLP/off\"><button class=\"button button2\">Sleep</button></a>");
            }

            if (sleepWakeupTime == 60) {
              client.print("<a href=\"/WKE/one\"><button class=\"button button2\">");
              client.print(sleepWakeupTime / 60);
              client.print("m</button></a>");
            } else {
              client.print("<a href=\"/WKE/ten\"><button class=\"button button2\">");
              client.print(sleepWakeupTime / 60);
              client.print("m</button></a>");
            }

            if (WiFistatus == 3 || WiFistatus == 0) {
              client.print("<a href=\"/WFI/on\"><button class=\"button\">WiFi</button></a>");
            } else {
              client.print("<a href=\"/WFI/off\"><button class=\"button button2\">WiFi</button></a>");
            }

            client.print("<br/>");
            if (FanActive == 1) {
              client.print("<a href=\"/FAN/on\"><button class=\"button\">FAN</button></a>");
            } else {
              client.print("<a href=\"/FAN/off\"><button class=\"button button2\">FAN</button></a>");
            }

            client.print("<a href=\"/RST\"><button class=\"button button2\">RST</button></a>");
            client.print("<a href=\"/LOG/del\"><button class=\"button button2\">DEL</button></a>");

            client.print("<br/>");
            if (screenState) {
              client.print("<a href=\"/TFT/on\"><button class=\"button\">TFT</button></a>");
            } else {
              client.print("<a href=\"/TFT/off\"><button class=\"button button2\">TFT</button></a>");
            }
            if (ledB > 0) {
              client.print("<a href=\"/LED/on\"><button class=\"button\">LED</button></a>");
            } else {
              client.print("<a href=\"/LED/off\"><button class=\"button button2\">LED</button></a>");
            }
            if (loggingActive) {
              client.print("<a href=\"/LOG/on\"><button class=\"button\">LOG</button></a>");
            } else {
              client.print("<a href=\"/LOG/off\"><button class=\"button button2\">LOG</button></a>");
            }
            client.print("<br/>");

            client.print("<a href=\"/PAGE/back\"><button class=\"button\">BACK</button></a>");
            client.print(" <b>");
            switch ( pageCount ) {
              case 0:
                client.print("HOME");
                break;
              case 1:
                client.print("TEMP");
                break;
              case 2:
                client.print("BODY");
                break;
              case 3:
                client.print("HRO2");
                break;
              case 4:
                client.print("GRPH");
                break;
              case 5:
                client.print("DIAG");
                break;
              case 6:
                client.print("SDCR");
                break;
              case 7:
                client.print("INFO");
                break;
              case 8:
                client.print("INFO");
                break;
            }

            client.print(" </b>");
            client.print("<a href=\"/PAGE/next\"><button class=\"button\">NEXT</button></a>");

            if (CCS811err > 0) {
              CCS811Core::status returnCode = myCCS811.begin();
              //              client.println("<a href=\"/button1off\"><button2 style='font-size:100%;background-color:#383838; color:red;border-radius:5px; position:absolute;top:20px; left:30px;'>Sensors</a>");
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
            client.print("<br>");
            client.print("<p style=\"font-size:100%; text-align: center\">");
            client.print(RTCprint);
            client.println("<br>");
            client.print(RTCdate);
            if (SDpresent == true) {
              client.print("<br><b>SD Online<b/><br/>");
            } else {
              client.print("<br>SD empty<br/>");
            }
            client.println("<br>");
            client.println("</body></html>");
            break;
          }
          else { // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') { // if you got anything else but a carriage return character,
          currentLine += c;       // add it to the end of the currentLine
        }
      }
    }
    header = "";
    client.stop();
    tft.setTextColor(TFT_BLACK);
    tft.fillRect(wifiX, 2, 12, 12, TFT_BLACK);
  }
}



void printTemperature(DeviceAddress deviceAddress) // Dallas Temperature Sensor Void
{
  tempC = sensors.getTempC(deviceAddress);

  if (tempC == DEVICE_DISCONNECTED_C) {
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.print("--");
    tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
    return;
  }
  if (sensors.hasAlarm(deviceAddress)) {
    tft.setTextColor(TFT_RED, TFT_BLACK);
  } else {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
  }
  tft.print(tempC, 0);
  tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
}


void TFToff() {
  sleepTimer = TimeoutT + TimeoutT2 + 5;
}
void TFTon() {
  sleepTimer = 0;
}

void checkScreenState() {

  if (sleepTimer < TimeoutT + TimeoutT2 + deepSleepStart) sleepTimer++;

  if (sleepTimer > TimeoutT) {
    screenState = 0;
  } else {
    screenState = 1;
  }

  if (screenState) {
    while (tftBKL < 254) {
      tftBKL++;
      delay(1);
      analogWrite(tftPIN, tftBKL);
    }
  } else {
    while (tftBKL > 35) {
      tftBKL--;
      delay(3);
      analogWrite(tftPIN, tftBKL);
    }

    if (tftBKL == 35 && sleepTimer > TimeoutT + TimeoutT2) {
      // myCCS811.setDriveMode(2); // RAW 0=idle, 1=1sec, 2=10sec, 3=60sec, 4=RAW
      //      if (minElapsed > 10 && !screenState) myCCS811.setDriveMode(3); // RAW 0=idle, 1=1sec, 2=10sec, 3=60sec, 4=RAW
      while (tftBKL > 0) {
        tftBKL--;
        delay(8);
        analogWrite(tftPIN, tftBKL);
      }
    }
  }
}


void printStatusBar() {

  if (Volts > 8.3) {
    tft.pushImage(batX, 2, 13, 13, bat100);
  } else if (Volts < 8.3 && Volts > 8) {
    tft.pushImage(batX, 2, 13, 13, bat80);
  } else if (Volts < 8 && Volts > 7.8) {
    tft.pushImage(batX, 2, 13, 13, bat70);
  } else if (Volts < 7.8 && Volts > 7.6) {
    tft.pushImage(batX, 2, 13, 13, bat60);
  } else if (Volts < 7.6 && Volts > 7.4) {
    tft.pushImage(batX, 2, 13, 13, bat50);
  } else if (Volts < 7.4 && Volts > 7.2) {
    tft.pushImage(batX, 2, 13, 13, bat40);
  } else if (Volts < 7.2 && Volts > 7) {
    tft.pushImage(batX, 2, 13, 13, bat30);
  } else if (Volts < 7 && Volts > 6.8) {
    tft.pushImage(batX, 2, 13, 13, bat20);
  } else if (Volts < 6.8 && Volts > 6.5) {
    tft.pushImage(batX, 2, 13, 13, bat10);
  } else if (Volts < 6.5) {
    tft.pushImage(batX, 2, 13, 13, bat5);
  }

  if (sleepTimer < TimeoutT + TimeoutT2 && pageCount == 0 || pageCount == 1 || pageCount == 2) { // print minElapsed & Lamp Icon
    tft.setTextColor(TFT_CYAN, TFT_BLACK);
    tft.setTextPadding(30);
    tft.setTextSize(1);
    tft.setTextDatum(BL_DATUM);
    tft.drawString(String(minElapsed) + "min", 0, TFTheight, 2);
    if (ledB > 1 && pageCount == 0 || pageCount == 2) {
      if (SDpresent) drawBmp("/UI/lampon.bmp", 6, 197);
    } else if (ledB == 0 && pageCount == 0 || pageCount == 2) {
      if (SDpresent) drawBmp("/UI/lamp.bmp", 6, 197);
    }
  }

  if (WiFistatus == 3) {
    int WiFiRSSI = WiFi.RSSI();
    if (WiFiRSSI > -60) {
      tft.pushImage(wifiX, 2, 12, 12, Wifi12);
    } else if (WiFiRSSI < -60 && WiFiRSSI > -80)   {
      tft.pushImage(wifiX, 2, 12, 12, WifiLow12);
    } else {
      tft.pushImage(wifiX, 2, 12, 12, WifiLower12);
    }
  } else if (WiFistatus == 6) {
    tft.pushImage(wifiX, 2, 12, 12, WifiOff12);
  } else {
    tft.pushImage(wifiX, 2, 12, 12, WifiIdle12);
  }

  if (SDpresent) {
    drawBmp("/UI/sd13.bmp", 3, 2);   // 24bit
  } else {
    tft.fillRect(3, 1, 12, 12, TFT_BLACK);
  }

  if (loggingActive) {
    if (SDpresent) drawBmp("/UI/logging12.bmp", 24, 2);   // 24bit
  } else {
    tft.fillRect(24, 2, 12, 12, TFT_BLACK);
  }

  if (FanActive) {
    if (SDpresent) drawBmp("/UI/fan12.bmp", 44, 2);   // 24bit
  } else {
    tft.fillRect(44, 2, 12, 12, TFT_BLACK);
  }

  if (deepSleepActive) {
    if (SDpresent) drawBmp("/UI/sleep12.bmp", 60, 2);   // 24bit
  } else {
    tft.fillRect(60, 2, 12, 12, TFT_BLACK);
  }

  if (AirWarning) {
    if (SDpresent) drawBmp("/warn12.bmp", 3, 22);
  } else {
    tft.fillRect(3, 22, 12, 12, TFT_BLACK);
  }
}



void print_wakeup_reason() {

  tft.setTextColor(TFT_INDIA, TFT_BLACK);
  tft.setTextDatum(TL_DATUM);
  tft.setTextPadding(TFTwidth);
  tft.setTextSize(1);
  preferences.begin("my - app", false);
  counter = preferences.getUInt("counter", 0);
  htmlRestart = preferences.getUInt("htmlRestart", 0);
  preferences.end();
  SDloghead = "";

  if (htmlRestart || deleteLog) {
    SDloghead += "\nTime, Bat %, Load V, Current, Watts, t1, t2, t3, t4, t5, t6, t7, CO2, tVOC, Temp, RH, Alt, UV, Backlight, Fan, LED\n";
    SDloghead += RTClog;
    if (deleteLog) SDloghead += "Log Deleted, #";
    if (htmlRestart) SDloghead += "htmlRestart, #";
    SDloghead += String(counter);
    SDloghead += ", v";
    SDloghead += String(Revision);
    SDloghead += "\n";
    if (htmlRestart) {
      htmlRestart = 0;
      preferences.begin("my - app", false);
      preferences.putUInt("htmlRestart", 0);
      preferences.end();
      tft.drawString("htmlRestart", 0, 0, 1);
    }
    TFTon();
    checkScreenState();
    deepSleepActive = false;
  } else {

    esp_sleep_wakeup_cause_t wakeup_reason;
    wakeup_reason = esp_sleep_get_wakeup_cause();
    rtc_gpio_force_hold_dis_all();

    switch (wakeup_reason)
    {
      case ESP_SLEEP_WAKEUP_EXT0 : tft.drawString("Wakeup by RTC_IO", 0, 0, 1);
        deepSleepActive = true;
        TFTon();
        checkScreenState();
        SDloghead += RTClog;
        SDloghead += "RTC_IO, #";
        SDloghead += String(counter);
        SDloghead += ", v";
        SDloghead += String(Revision);
        SDloghead += "\n";
        break;
      case ESP_SLEEP_WAKEUP_EXT1 : tft.drawString("Wakeup by external signal RTC_CNTL", 0, 0, 1);
        deepSleepActive = true;
        TFTon();
        checkScreenState();
        SDloghead += RTClog;
        SDloghead += "RTC_CNTL, #";
        SDloghead += String(counter);
        SDloghead += ", v";
        SDloghead += String(Revision);
        SDloghead += "\n";
        break;
      case ESP_SLEEP_WAKEUP_TIMER : tft.drawString("Wakeup by timer", 0, 0, 1);
        deepSleepActive = true;
        TFToff();
        checkScreenState();
        SDloghead += "\nTime, Bat %, Load V, Current, Watts, t1, t2, t3, t4, t5, t6, t7, CO2, tVOC, Temp, RH, Alt, UV, Backlight, Fan, LED\n";
        SDloghead += RTClog;
        SDloghead += "RTC_TIMER, #";
        SDloghead += String(counter);
        SDloghead += ", v";
        SDloghead += String(Revision);
        SDloghead += "\n";
        break;
      case ESP_SLEEP_WAKEUP_TOUCHPAD : tft.drawString("Wakeup by touchpad", 0, 0, 1);
        deepSleepActive = true;
        TFTon();
        checkScreenState();
        SDloghead += "\nTime, Bat %, Load V, Current, Watts, t1, t2, t3, t4, t5, t6, t7, CO2, tVOC, Temp, RH, Alt, UV, Backlight, Fan, LED\n";
        SDloghead += RTClog;
        SDloghead += "RTC_TOUCHPAD, #";
        SDloghead += String(counter);
        SDloghead += ", v";
        SDloghead += String(Revision);
        SDloghead += "\n";
        break;
      case ESP_SLEEP_WAKEUP_ULP : tft.drawString("Wakeup by ULP program", 0, 0, 1);
        deepSleepActive = true;
        TFTon();
        checkScreenState();
        SDloghead += "\nTime, Bat %, Load V, Current, Watts, t1, t2, t3, t4, t5, t6, t7, CO2, tVOC, Temp, RH, Alt, UV, Backlight, Fan, LED\n";
        SDloghead += RTClog;
        SDloghead += "RTC_ULP, #";
        SDloghead += String(counter);
        SDloghead += ", v";
        SDloghead += String(Revision);
        SDloghead += "\n";
        break;
      default:
        deepSleepActive = false;
        TFTon();
        checkScreenState();
        SDloghead += "\nTime, Bat %, Load V, Current, Watts, t1, t2, t3, t4, t5, t6, t7, CO2, tVOC, Temp, RH, Alt, UV, Backlight, Fan, LED\n";
        SDloghead += RTClog;
        SDloghead += "RESTART, #";
        SDloghead += String(counter);
        SDloghead += ", v";
        SDloghead += String(Revision);
        if (rtcLostPower) {                           // RTC setup
          SDloghead += ", Hard Reset\n";
        } else if (!rtcLostPower) {
          SDloghead += ", Soft Reset\n";
        }
        break;
    }
  }
  if (SDpresent) appendFile(SD, LogFile, SDloghead.c_str());
}


void print_reset_reason(RESET_REASON reason)
{
  switch ( reason)
  {
    case 1 : Serial.println ("POWERON_RESET"); break;         /**<1,  Vbat power on reset*/
    case 3 : Serial.println ("SW_RESET"); break;              /**<3,  Software reset digital core*/
    case 4 : Serial.println ("OWDT_RESET"); break;            /**<4,  Legacy watch dog reset digital core*/
    case 5 : Serial.println ("DEEPSLEEP_RESET"); break;       /**<5,  Deep Sleep reset digital core*/
    case 6 : Serial.println ("SDIO_RESET"); break;            /**<6,  Reset by SLC module, reset digital core*/
    case 7 : Serial.println ("TG0WDT_SYS_RESET"); break;      /**<7,  Timer Group0 Watch dog reset digital core*/
    case 8 : Serial.println ("TG1WDT_SYS_RESET"); break;      /**<8,  Timer Group1 Watch dog reset digital core*/
    case 9 : Serial.println ("RTCWDT_SYS_RESET"); break;      /**<9,  RTC Watch dog Reset digital core*/
    case 10 : Serial.println ("INTRUSION_RESET"); break;      /**<10, Instrusion tested to reset CPU*/
    case 11 : Serial.println ("TGWDT_CPU_RESET"); break;      /**<11, Time Group reset CPU*/
    case 12 : Serial.println ("SW_CPU_RESET"); break;         /**<12, Software reset CPU*/
    case 13 : Serial.println ("RTCWDT_CPU_RESET"); break;     /**<13, RTC Watch dog Reset CPU*/
    case 14 : Serial.println ("EXT_CPU_RESET"); break;        /**<14, for APP CPU, reseted by PRO CPU*/
    case 15 : Serial.println ("RTCWDT_BROWN_OUT_RESET"); break; /**<15, Reset when the vdd voltage is not stable*/
    case 16 : Serial.println ("RTCWDT_RTC_RESET"); break;     /**<16, RTC Watch dog reset digital core and rtc module*/
    default : Serial.println ("NO_IDEA");
  }
}
void verbose_print_reset_reason(RESET_REASON reason)
{
  switch (reason)
  {
    case 1  : tft.print ("Vbat power on reset"); break;
    case 3  : tft.print ("Software reset digital core"); break;
    case 4  : tft.print ("Legacy watch dog reset digital core"); break;
    case 5  : tft.print ("Deep Sleep reset digital core"); break;
    case 6  : tft.print ("Reset by SLC module, reset digital core"); break;
    case 7  : tft.print ("Timer Group0 Watch dog reset digital core"); break;
    case 8  : tft.print ("Timer Group1 Watch dog reset digital core"); break;
    case 9  : tft.print ("RTC Watch dog Reset digital core"); break;
    case 10 : tft.print ("Instrusion tested to reset CPU"); break;
    case 11 : tft.print ("Time Group reset CPU"); break;
    case 12 : tft.print ("Software reset CPU"); break;
    case 13 : tft.print ("RTC Watch dog Reset CPU"); break;
    case 14 : tft.print ("for APP CPU, reseted by PRO CPU"); break;
    case 15 : tft.print ("Voltage Brownout caused Reset"); break;
    case 16 : tft.print ("RTC Watch dog reset digital core and rtc module"); break;
    default : tft.print ("NO_IDEA");
  }
}


void printDirectory(File dir, int numTabs) {

  while (true) {
    File entry =  dir.openNextFile();

    if (! entry) {
      // no more files
      i = 0;
      break;
    }

    for (uint8_t i = 0; i < numTabs; i++) {
      tft.print('\t');
    }

    Filename = entry.name();
    if (Filename.indexOf(".", 0) == true || Filename.indexOf(".", 1) == true) {
      entry.close();
      break;
    } else {
      if (Filename == LogFile) {
        tft.setTextColor(TFT_DARKGREEN, TFT_BLACK);
      } else {
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
      }
      tft.print(Filename); tft.print(" ");
    }

    if (entry.isDirectory()) {
      //      tft.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      if (entry.size() / 1024 > 1024) {
        tft.print(entry.size() / 1024 / 1024, DEC);
        tft.println("mb");
      } else {
        tft.print(entry.size() / 1024, DEC);
        tft.println("kb");
      }
    }
    entry.close();
  }
}


void readFile(fs::FS & fs, const char * path) {

  File file = fs.open(path);
  if (!file) {
    return;
  }
  while (file.available()) {
    tft.print(file.read());
  }
  file.close();
}

void appendFile(fs::FS & fs, const char * path, const char * message) {
  //Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    SDpresent = false;
    loggingActive = false;
    return;
  }
  file.print(message);//  Message appended
  file.close();
}


void drawBmp(const char *filename, int16_t x, int16_t y) {

  if ((x >= TFTwidth) || (y >= TFTwidth)) return;

  bmpFS = SD.open(filename);

  if (!bmpFS)
  {
    tft.println("no bmp");
    SDpresent = false;
    return;
  }

  if (read16(bmpFS) == 0x4D42)
  {
    read32(bmpFS);
    read32(bmpFS);
    seekOffset = read32(bmpFS);
    read32(bmpFS);
    w = read32(bmpFS);
    h = read32(bmpFS);

    if ((read16(bmpFS) == 1) && (read16(bmpFS) == 24) && (read32(bmpFS) == 0))
    {
      y += h - 1;

      tft.setSwapBytes(true);
      bmpFS.seek(seekOffset);

      padding = (4 - ((w * 3) & 3)) & 3;
      uint8_t lineBuffer[w * 3];

      for (row = 0; row < h; row++) {
        bmpFS.read(lineBuffer, sizeof(lineBuffer));
        uint8_t*  bptr = lineBuffer;
        uint16_t* tptr = (uint16_t*)lineBuffer;
        // Convert 24 to 16 bit colours
        for (uint16_t col = 0; col < w; col++)
        {
          b = *bptr++;
          g = *bptr++;
          r = *bptr++;
          *tptr++ = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
        }
        // Read any line padding
        if (padding) bmpFS.read((uint8_t*)tptr, padding);
        // Push the pixel row to screen, pushImage will crop the line if needed
        tft.pushImage(x, y--, w, 1, (uint16_t*)lineBuffer);
      }
    } else tft.println("BMP not recognized");
  }
  bmpFS.close();
}

String translateEncryptionType(wifi_auth_mode_t encryptionType) {

  switch (encryptionType) {
    case (WIFI_AUTH_OPEN):
      return "Open";
    case (WIFI_AUTH_WEP):
      return "WEP";
    case (WIFI_AUTH_WPA_PSK):
      return "WPA";
    case (WIFI_AUTH_WPA2_PSK):
      return "WPA2";
    case (WIFI_AUTH_WPA_WPA2_PSK):
      return "WPA_WPA2";
    case (WIFI_AUTH_WPA2_ENTERPRISE):
      return "WPA2_ENT";
  }
}

const char* wl_status_to_string(wl_status_t status) {
  switch (status) {
    case WL_NO_SHIELD: return "NO_SHIELD";
    case WL_IDLE_STATUS: return "IDLE_STATUS";
    case WL_NO_SSID_AVAIL: return "NO_SSID";
    case WL_SCAN_COMPLETED: return "SCAN_COMPLETE";
    case WL_CONNECTED: return "CONNECTED";
    case WL_CONNECT_FAILED: return "CONNECT_FAILED";
    case WL_CONNECTION_LOST: return "CONNECT_LOST";
    case WL_DISCONNECTED: return "DISCONNECTED";
  }
}

uint16_t read16(fs::File & f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}


uint32_t read32(fs::File & f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}

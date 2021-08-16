#include <pgmspace.h>

bool wifiPrint() {

  WiFiClient client = server.available();                           ////  WiFi Print to Local IP  //// if (client)
  if (client) {
    millisElapsed = millis();
    previousTime = millisElapsed;
    currentLine = "";

    while (client.connected() && millisElapsed - previousTime <= 4000) {  // loop while the client's connected if (client.available())  //if there issome client data available
      millisElapsed = millis();
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

            if (pageCount == 4) ledB = 0;
            if (header.indexOf("GET /LED/off") >= 0) {
              ledBon = true;
              amgSetHiRes = !amgSetHiRes;
            } else if (header.indexOf("GET /LED/on") >= 0) {
              ledBon = false;
              amgSetHiRes = !amgSetHiRes;
            }

            if (header.indexOf("GET /ALARM/off") >= 0) {
              alarmEnable = true;
            } else if (header.indexOf("GET /ALARM/on") >= 0) {
              alarmEnable = false;
            }

            if (header.indexOf("GET /LOG/off") >= 0) {
              loggingActive = true;
              putPersistentBool("loggingActive", loggingActive);
            } else if (header.indexOf("GET /LOG/on") >= 0) {
              loggingActive = false;
              putPersistentBool("loggingActive", loggingActive);
            }

            if (header.indexOf("GET /MUTE/off") >= 0) {
              silentMode = true;
            } else if (header.indexOf("GET /MUTE/on") >= 0) {
              silentMode = false;
            }

            if (header.indexOf("GET /Powersave/off") >= 0) {      // Power Saving Mode
              deepSleepActive = true;
              lowPowerMode = true;
              setCpuFrequencyMhz(80);
              myCCS811.setDriveMode(3);   // 0=idle, 1=1sec, 2=10sec, 3=60sec, 4=RAW
              scd30.setMeasurementInterval(60);
              ina260.setAveragingCount(INA260_COUNT_64);
              ina260.setVoltageConversionTime(INA260_TIME_8_244_ms); // 140_us, 204_us, 332_us, 558_us, 1_1_ms,
              ina260.setCurrentConversionTime(INA260_TIME_8_244_ms);
              ledB = 0;
            } else if (header.indexOf("GET /Powersave/on") >= 0) {
              if (Volts > 6.6) {
                deepSleepActive = false;
                lowPowerMode = false;
                setCpuFrequencyMhz(240);
                myCCS811.setDriveMode(1);   // 0=idle, 1=1sec, 2=10sec, 3=60sec, 4=RAW
                scd30.setMeasurementInterval(5);
                ina260.setAveragingCount(INA260_COUNT_128); // 128 * 558us = 71ms
                ina260.setVoltageConversionTime(INA260_TIME_558_us); // 140_us, 204_us, 332_us, 558_us, 1_1_ms,
                ina260.setCurrentConversionTime(INA260_TIME_558_us);
              }
              TFTon();
            }

            if (header.indexOf("GET /WFI/off") >= 0) {
            } else if (header.indexOf("GET /WFI/on") >= 0) {
              client.stop();
              WiFi.disconnect(true);
              WiFi.mode(WIFI_OFF);
            }

            if (header.indexOf("GET /PAGE/next") >= 0) {
              if (pageCount == 0) {
                menuCar++;
              } else {
                pageCount++;
              }
              if (pageCount > menuPages) pageCount = 0;
            }
            if (header.indexOf("GET /PAGE/back") >= 0) {

              if (pageCount == 0) {
                menuCar--;
              } else {
                pageCount--;
              }
              if (pageCount > menuPages) pageCount = 0;
            }

            if (header.indexOf("GET /RST") >= 0) {
              htmlRestart = true;
              putPersistentBool("htmlRestart", htmlRestart);
              ESP.restart();
            }
            if (header.indexOf("GET /LOG/del") >= 0) {
              deleteLog = true;
              if (SD.exists(LogFile)) {
                SD.remove(LogFile);
                if (!silentMode) tone(beepPin, 3800, 6);
                delay(60);
                if (!silentMode) tone(beepPin, 3800, 6);
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
            } else if (header.indexOf("GET /WKE/ten") >= 0) {
              sleepWakeupTime = 60;
            }

            String HTMLpage = "";

            HTMLpage += "<!DOCTYPE html><html>";
            HTMLpage += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
            HTMLpage += "<link rel=\"icon\" href=\"data:, \">";
            HTMLpage += "<meta http-equiv=\"refresh\" content=\"5\";url=/ \"></head>";

            HTMLpage += "<body><body bgcolor = '#000000'>";

            // Web Page Heading
            HTMLpage += "<body>";
            HTMLpage += "<head><title>ESP32</title></head> ";

            HTMLpage += "<table style=width:\"25%\"; font-size: \"200%\"; text-align:\"center\">";
            HTMLpage += "<tr>";
            HTMLpage += "<th>";
            HTMLpage += voltsAvg;
            HTMLpage += " V</th>";
            HTMLpage += "<th>";
            HTMLpage += ampsAvg;
            HTMLpage += " A</th>";

            HTMLpage += "<tr>";
            HTMLpage += "<th>Alt</th>";
            HTMLpage += "<th>Press</th>";
            HTMLpage += "</tr>";
            HTMLpage += "<tr>";
            HTMLpage += "<td>";
            HTMLpage += altBME;
            HTMLpage += "m</td>";
            HTMLpage += "<td>";
            HTMLpage += pressureBME;
            HTMLpage += "</td></tr>";

            HTMLpage += "<tr><th>Temp</th>";
            HTMLpage += "<th>RH</th>";
            HTMLpage += "</tr>";
            HTMLpage += "<tr>";
            HTMLpage += "<td>";
            HTMLpage += tempBME;
            HTMLpage += "<sup>o</sup></td>";
            HTMLpage += "<td>";
            HTMLpage += humidSCD;
            HTMLpage += "%</td>";
            HTMLpage += "</tr>";

            HTMLpage += "<tr>";
            HTMLpage += "<th>CO<sup>2</sup></th>";
            HTMLpage += "<th><sub>t</sub>VOC</th>";
            HTMLpage += "</tr>";
            HTMLpage += "<tr>";
            HTMLpage += "<td>";
            HTMLpage += co2SCD;
            HTMLpage += "ppm</td>";
            HTMLpage += "<td>";
            HTMLpage += tvocSMPL;
            HTMLpage += "ppm</td>";
            HTMLpage += "</tr>";

            HTMLpage += "</table>";

            HTMLpage += "<b>UV </b>";
            //            HTMLpage += UVI;
            HTMLpage += "<br><b>Steps </b>";
            HTMLpage += steps;
            HTMLpage += "<br>";
            HTMLpage += "<b>";
            FPS = 1000 / FPS;
            HTMLpage += FPS;
            HTMLpage += "</b>";
            HTMLpage += " fps";
            HTMLpage += "<br>";

            client.println(HTMLpage);

            client.print(minElapsed);
            client.print("m Runtime<br/>");

            client.print("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; color: white;}");
            client.print(".button { background-color: #4CAF50; border: 2px; color: white; padding: 8px 35px;");
            client.print("text-decoration: none; font-size: 22px; margin: 2px; cursor: pointer;}");
            client.print(".button2 {background-color: #555555;} </style></head>");
            client.print("<p style=\"font-size:120%; text-align: center\">");

            if (getCpuFrequencyMhz() == 80) {
              client.print("<a href=\"/Powersave/on\"><button class=\"button\">loPwr</button></a>");
            } else {
              client.print("<a href=\"/Powersave/off\"><button class=\"button button2\">loPwr</button></a>");
            }

            if (deepSleepActive) {
              client.print("<a href=\"/SLP/on\"><button class=\"button\">Slp</button></a>");
            } else {
              client.print("<a href=\"/SLP/off\"><button class=\"button button2\">Slp</button></a>");
            }

            if (alarmEnable) {
              client.print("<a href=\"/ALARM/on\"><button class=\"button\">ALR</button></a>");
            } else {
              client.print("<a href=\"/ALARM/off\"><button class=\"button button2\">ALR</button></a>");
            }

            client.print("<br/>");

            if (silentMode) {
              client.print("<a href=\"/MUTE/on\"><button class=\"button\">Mute</button></a>");
            } else {
              client.print("<a href=\"/MUTE/off\"><button class=\"button button2\">Mute</button></a>");
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
            if (fanActive) {
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
                client.print("MENU");
                break;
              case 1:
                client.print("DEBU");
                break;
              case 2:
                client.print("SD");
                break;
              case 3:
                client.print("SYST");
                break;
              case 4:
                client.print("GRPH");
                break;
              case 5:
                client.print("HOME");
                break;
              case 6:
                client.print("INFO");
                break;
              case 7:
                client.print("INFO");
                break;
              case 8:
                client.print("THER");
                break;
              case 9:
                client.print("HR");
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
            client.print(RTCd);
            if (SDpresent) {
              client.print("<br><b>SD Online<b/><br/>");
            } else {
              client.print("<br>SD ---<br/>");
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
    //    tft.fillRect(wifiX, 2, 12, 12, TFT_BLACK);
  }
}

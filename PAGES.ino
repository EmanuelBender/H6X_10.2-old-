#include <pgmspace.h>

void page0() {

  if (pageCount == 0) {      // MENU
    tft.fillScreen(TFT_BLACK);
    tft.setTextDatum(TC_DATUM);
    drawBmp(SPIFFS, "/Moon240.bmp", 0, 190);

    tft.setTextSize(1);
    tft.setTextColor(TFT_BLACK);
    tft.setTextDatum(BL_DATUM);
    tft.drawString("a" + String(Revision), 202, 240, 2);

    byte earthPositionX = map(hr, 0, 24, 0, 230);
    byte earthPositionY = map(hr, 0, 24, 160, 175);

    tft.drawRoundRect(mX, 84, 40, 40, 7, TFT_MIDDLEGREY);
    mY = 160;
    menuIcons();

    //    tft.readRect(0, 88, TFT_WIDTH, 32, menuReadRect);   // x, y, w, h, data array 7680

    while (pageCount == 0) {
      if (!notiOn) everyXsec();
      checkScreenState();
      if (everyXsecFlag && !notiOn) printStatusBar();
      notiWarnings();
      wifiPrint();
      readEnvironmentData();   // CCS811 Function
      SYSTEM();

      if (menuCar == 0) menuCar = 5;
      if (menuCar > 5) menuCar = 1;

      tft.setTextSize(1);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.setTextDatum(TC_DATUM);
      if (everyXsecFlag) menuIcons();

      tft.setTextPadding(90);
      switch ( menuCar ) {     // X axis
        case 1:
          while (mX > 5) {
            if (mX == 50) tft.drawString("", mX + 20, 130, 2);
            tft.drawRoundRect(mX, 84, 40, 40, 7, TFT_BLACK);
            mX -= menuSpeed;
            tft.drawRoundRect(mX, 84, 40, 40, 7, TFT_MIDDLEGREY);
            //            tft.drawString(" Settings ", mX + 20, 130, 2);
            drawBmp(SPIFFS, icon1, carX1, 89);
            drawBmp(SPIFFS, icon2, carX2, 89);
            mY = 160;
          }
          break;

        case 2:
          while (mX > 50) {
            if (mX == 95) tft.drawString("", mX + 20, 130, 2);
            tft.drawRoundRect(mX, 84, 40, 40, 7, TFT_BLACK);
            mX -= menuSpeed;
            tft.drawRoundRect(mX, 84, 40, 40, 7, TFT_MIDDLEGREY);
            //            tft.drawString(" System ", mX + 20, 130, 2);
            drawBmp(SPIFFS, icon2, carX2, 89);
            drawBmp(SPIFFS, icon3, carX3, 89);
            mY = 160;
          }
          while (mX < 50) {
            if (mX == 5) tft.drawString("", mX + 20, 130, 2);
            tft.drawRoundRect(mX, 84, 40, 40, 7, TFT_BLACK);
            mX += menuSpeed;
            tft.drawRoundRect(mX, 84, 40, 40, 7, TFT_MIDDLEGREY);
            //            tft.drawString(" System ", mX + 20, 130, 2);
            drawBmp(SPIFFS, icon1, carX1, 89);
            drawBmp(SPIFFS, icon2, carX2, 89);
            mY = 160;
          }
          break;

        case 3:
          while (mX > 95) {
            if (mX == 140) tft.drawString("", mX + 20, 130, 2);
            tft.drawRoundRect(mX, 84, 40, 40, 7, TFT_BLACK);
            mX -= menuSpeed;
            tft.drawRoundRect(mX, 84, 40, 40, 7, TFT_MIDDLEGREY);
            //            tft.drawString(" HOME ", mX + 20, 130, 2);
            drawBmp(SPIFFS, icon3, carX3, 89);
            drawBmp(SPIFFS, icon4, carX4, 89);
            mY = 160;
          }
          while (mX < 95) {
            if (mX == 50) tft.drawString("", mX + 20, 130, 2);
            tft.drawRoundRect(mX, 84, 40, 40, 7, TFT_BLACK);
            mX += menuSpeed;
            tft.drawRoundRect(mX, 84, 40, 40, 7, TFT_MIDDLEGREY);
            //            tft.drawString(" HOME ", mX + 20, 130, 2);
            drawBmp(SPIFFS, icon2, carX2, 89);
            drawBmp(SPIFFS, icon3, carX3, 89);
            mY = 160;
          }
          break;

        case 4:
          while (mX > 140) {
            if (mX == 185) tft.drawString("", mX + 20, 130, 2);
            tft.drawRoundRect(mX, 84, 40, 40, 7, TFT_BLACK);
            mX -= menuSpeed;
            tft.drawRoundRect(mX , 84, 40, 40, 7, TFT_MIDDLEGREY);
            drawBmp(SPIFFS, icon4, carX4, 89);
            drawBmp(SPIFFS, icon5, carX5, 89);
            mY = 160;
          }
          while (mX < 140) {
            if (mX == 95) tft.drawString("", mX + 20, 130, 2);
            tft.drawRoundRect(mX, 84, 40, 40, 7, TFT_BLACK);
            mX += menuSpeed;
            tft.drawRoundRect(mX, 84, 40, 40, 7, TFT_MIDDLEGREY);
            drawBmp(SPIFFS, icon3, carX3, 89);
            drawBmp(SPIFFS, icon4, carX4, 89);
            mY = 160;
          }
          break;

        case 5:
          while (mX > 185) {
            tft.drawRoundRect(mX, 84, 40, 40, 7, TFT_BLACK);
            mX -= menuSpeed;
            tft.drawRoundRect(mX, 84, 40, 40, 7, TFT_MIDDLEGREY);
            drawBmp(SPIFFS, icon5, carX5, 89);
            mY = 160;
          }
          while (mX < 185) {
            if (mX == 140) tft.drawString("", mX + 20, 130, 2);
            tft.drawRoundRect(mX, 84, 40, 40, 7, TFT_BLACK);
            mX += menuSpeed;
            tft.drawRoundRect(mX, 84, 40, 40, 7, TFT_MIDDLEGREY);
            drawBmp(SPIFFS, icon4, carX4, 89);
            drawBmp(SPIFFS, icon5, carX5, 89);
            mY = 160;
          }
          break;
      }


      switch ( menuCar ) { //  Y Axis Text
        case 1: {
            while (mY > 130) {
              delay(2);
              //              tft.drawFastHLine(mX, mY + 14, 70, TFT_BLACK);
              //              tft.drawFastHLine(mX, mY + 15, 70, TFT_BLACK);
              tft.setTextColor(TFT_BLACK);
              tft.drawString("System", mX + 20, mY, 2);
              mY--;
              if (mY < 160 && mY > 150) {
                tft.drawString("     ", 120, 130, 2);
                tft.setTextColor(TFT_DARKGREY);
              } else if (mY < 150 && mY > 145) {
                tft.setTextColor(TFT_MIDDLEGREY);
              } else if (mY < 145 && mY > 137) {
                tft.setTextColor(TFT_LIGHTGREY);
              } else {
                tft.setTextColor(TFT_WHITE);
              }
              tft.drawString("System", mX + 20, mY, 2);
            }
            drawBmp(SPIFFS, "/EarthSmall.bmp", earthPositionX, earthPositionY);
            break;
          }
        case 2: {
            while (mY > 130) {
              delay(2);
              //              tft.drawFastHLine(mX, mY + 14, 70, TFT_BLACK);
              //              tft.drawFastHLine(mX, mY + 15, 70, TFT_BLACK);
              tft.setTextColor(TFT_BLACK);
              tft.drawString("Temp & Graph", mX + 20, mY, 2);
              mY--;
              if (mY < 160 && mY > 150) {
                tft.drawString("     ", 120, 130, 2);
                tft.setTextColor(TFT_DARKGREY);
              } else if (mY < 150 && mY > 145) {
                tft.setTextColor(TFT_MIDDLEGREY);
              } else if (mY < 145 && mY > 137) {
                tft.setTextColor(TFT_LIGHTGREY);
              } else {
                tft.setTextColor(TFT_WHITE);
              }
              tft.drawString("Temp & Graph", mX + 20, mY, 2);
            }
            drawBmp(SPIFFS, "/EarthSmall.bmp", earthPositionX, earthPositionY);
            break;
          }
        case 3: {
            while (mY > 130) {
              delay(2);
              tft.setTextColor(TFT_BLACK);
              tft.drawString("HOME", mX + 20, mY, 2);
              mY--;
              if (mY < 160 && mY > 150) {
                tft.drawString("     ", 120, 130, 2);
                tft.setTextColor(TFT_DARKGREY);
              } else if (mY < 150 && mY > 145) {
                tft.setTextColor(TFT_MIDDLEGREY);
              } else if (mY < 145 && mY > 137) {
                tft.setTextColor(TFT_LIGHTGREY);
              } else {
                tft.setTextColor(TFT_WHITE);
              }
              tft.drawString("HOME", mX + 20, mY, 2);
            }
            drawBmp(SPIFFS, "/EarthSmall.bmp", earthPositionX, earthPositionY);
            break;
          }
        case 4: {
            while (mY > 130) {
              delay(2);
              tft.setTextColor(TFT_BLACK);
              tft.drawString("Thermal Cam", mX + 20, mY, 2);
              mY--;
              if (mY < 160 && mY > 150) {
                tft.drawString("     ", 120, 130, 2);
                tft.setTextColor(TFT_DARKGREY);
              } else if (mY < 150 && mY > 145) {
                tft.setTextColor(TFT_MIDDLEGREY);
              } else if (mY < 145 && mY > 137) {
                tft.setTextColor(TFT_LIGHTGREY);
              } else {
                tft.setTextColor(TFT_WHITE);
              }
              tft.drawString("Thermal Cam", mX + 20, mY, 2);
            }
            drawBmp(SPIFFS, "/EarthSmall.bmp", earthPositionX, earthPositionY);
            break;
          }
        case 5: {
            while (mY > 130) {
              delay(2);
              tft.setTextColor(TFT_BLACK);
              tft.drawString("Heartrate", mX + 20, mY, 2);
              mY--;
              if (mY < 160 && mY > 150) {
                tft.drawString("     ", 120, 130, 2);
                tft.setTextColor(TFT_DARKGREY);
              } else if (mY < 150 && mY > 145) {
                tft.setTextColor(TFT_MIDDLEGREY);
              } else if (mY < 145 && mY > 137) {
                tft.setTextColor(TFT_LIGHTGREY);
              } else {
                tft.setTextColor(TFT_WHITE);
              }
              tft.drawString("Heartrate", mX + 20, mY, 2);
            }
            drawBmp(SPIFFS, "/EarthSmall.bmp", earthPositionX, earthPositionY);
            break;
          }
      }


      //        tft.setTextDatum(TC_DATUM);
      //        tft.setTextPadding(60);
      //        tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
      //        tft.drawString(String(SOC), 120, 171, 2);
      //        tft.drawString(String(socVolts) + "V", 120, 187, 2);

    }
    //      tft.setTextColor(TFT_WHITE, TFT_BLACK);
    //      tft.setCursor(205, 19);
    //      FPS = millis() - millisElapsed;
    //      tft.print(FPS); tft.print("ms  ");
  }
  switch ( pageCount ) {
    //      case 0: page0();
    case 1: page1();
    //      case 2: page2();
    case 3: page3();
    //      case 4: page4();
    case 5: page5();
    //      case 6: page6();
    //      case 7: page7();
    case 8: page8();
    case 9: page9();
  }
}


void page1() {   // Settings / Diagnostics

  if (pageCount == 1) {

    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    tft.setTextPadding(0);
    tft.fillRoundRect(-12, 171 - scrollTFT, 188, 32, 15, TFT_DARKGREY); // wifi box
    tft.fillRoundRect(-12, 181 - scrollTFT, 188, 32, 15, TFT_BLACK); // wifi box
    tft.drawFastHLine(0, 51 - scrollTFT, 240, TFT_MIDDLEGREY);
    tft.drawFastHLine(0, 93 - scrollTFT, 240, TFT_MIDDLEGREY);
    //        tft.drawFastHLine(0, 105 - scrollTFT, 240, TFT_MIDDLEGREY);
    tft.drawFastHLine(0, 132 - scrollTFT, 240, TFT_DARKGREY);
    tft.drawFastVLine(175, 94 - scrollTFT, 250, TFT_DARKGREY);
    tft.drawFastVLine(122, 94 - scrollTFT, 75, TFT_DARKGREY);
    tft.drawFastVLine(55, 94 - scrollTFT, 75, TFT_DARKGREY);

    scrollTFT = 0;
    chipId = 0;
    previousTime1 = 0;

    while (pageCount == 1) {
      SYSTEM();
      if (!notiOn) {
        everyXsec();

        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setCursor(0, 0 - scrollTFT);
        tft.setTextSize(2);

        tft.print(WiFi.SSID()); tft.print(" ");
        if (WiFistatus == 3) tft.setTextColor(TFT_MIDDLEGREEN, TFT_BLACK);
        tft.println(translate_wl_status(WiFi.status()));
        tft.setTextColor(TFT_WHITE);
        tft.print(WiFi.localIP()); tft.print(" ");
        tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
        tft.print(WiFi.RSSI()); tft.println("dB");
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
      }

      tft.setTextSize(1);
      tft.setTextDatum(TC_DATUM);
      tft.setTextPadding(50);

      if (everyXsecFlag || previousTime1 == 0) {
        WiFistatus = WiFi.status();

        /*
          tft.drawString("MPU9250", 25, 108 - scrollTFT, 1);
          if (IMU.readId(&sensorId) > 0) {
          tft.setTextColor(TFT_RED, TFT_BLACK);
          tft.drawString("ERROR", 25, 118 - scrollTFT, 1);
          } else {
          tft.setTextColor(TFT_GREEN, TFT_BLACK);
          tft.drawString(" ok ", 25, 118 - scrollTFT, 1);
          }
        */

        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.drawString("AMG8833", 25, 98 - scrollTFT, 1);

        Wire.beginTransmission(0x69);  //  AMG8833 Modes
        Wire.write(0x00);     // Register
        Wire.write(0x00);     // Value to Register 0x00 - Normal, 0x10 - Sleep, 0x20 - 60sec, 0x21 - 10sec
        if (Wire.endTransmission() != 0) activeAMG = false;

        if (activeAMG) {
          drawBmp(SPIFFS, "/ok12.bmp", 19, 107 - scrollTFT);
          tft.drawString(String(amg.readThermistor(), 1), 25, 121 - scrollTFT, 1);
        } else {
          drawBmp(SPIFFS, "/notok12.bmp", 19, 107 - scrollTFT);
        }

        tft.setTextColor(TFT_WHITE);
        tft.drawString("VEML6075", 90, 98 - scrollTFT, 1);
        if (VML.begin()) {
          if (VML.isConnected()) {
            drawBmp(SPIFFS, "/ok12.bmp", 84, 107 - scrollTFT);
            tft.drawString(String(VML.getIntegrationTime()) + "ms", 90, 121 - scrollTFT, 1);
            activeVML = true;
          } else {
            drawBmp(SPIFFS, "/inactive12.bmp", 84, 107 - scrollTFT);
          }
        } else {
          activeVML = false;
          drawBmp(SPIFFS, "/notok12.bmp", 84, 107 - scrollTFT);
          tft.drawString("err:" + String(VML.begin()) + " " + String(VML.getIntegrationTime()) + "ms", 90, 121 - scrollTFT, 1);
        }


        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.drawString("DS3231", 150, 98 - scrollTFT, 1);
        if (rtc.begin()) {
          drawBmp(SPIFFS, "/ok12.bmp", 144, 107 - scrollTFT);
          tft.drawString(String(tempRTC) + "*", 150, 121 - scrollTFT, 1);
          activeRTC = true;
        } else {
          drawBmp(SPIFFS, "/notok12.bmp", 144, 107 - scrollTFT);
          activeRTC = false;
        }


        tft.drawString("MAX30105", 210, 98 - scrollTFT, 1);
        if (MAX30105.begin(Wire, I2C_SPEED_FAST)) {
          if (MAX30105.readPartID() == 21) {
            activeMAX = true;
            drawBmp(SPIFFS, "/ok12.bmp", 204, 107 - scrollTFT);
          } else {
            drawBmp(SPIFFS, "/inactive12.bmp", 204, 107 - scrollTFT);
            activeMAX = false;
          }
          //          drawBmp(SPIFFS, "/ok12.bmp", 204, 107 - scrollTFT);
          tft.setTextColor(TFT_WHITE); tft.drawString(String(ledBrightness) + " " + String(irOffset), 210, 121 - scrollTFT, 1);
          //          tft.setTextColor(TFT_WHITE); tft.drawString(String(ledBrightness) + " " + String(irOffset), 210, 121 - scrollTFT, 1);
        } else {
          activeMAX = false;
          drawBmp(SPIFFS, "/notok12.bmp", 204, 107 - scrollTFT);
        }

        tft.setTextColor(TFT_WHITE);
        tft.drawString("INA260", 25, 137 - scrollTFT, 1);
        switch (ina260.getMode()) {
          case 0x00: // shutdown
            drawBmp(SPIFFS, "/inactive12.bmp", 19, 146 - scrollTFT);
            activeINA = false;
            break;
          case 0x03: // triggered
            drawBmp(SPIFFS, "/ok12.bmp", 19, 146 - scrollTFT);
            tft.drawString("tr " + String(ina260.getCurrentConversionTime()) + ", " + String(ina260.getCurrentConversionTime()), 25, 161 - scrollTFT, 1);
            activeINA = true;
            break;
          case 0x07: // continuous
            drawBmp(SPIFFS, "/ok12.bmp", 19, 146 - scrollTFT);
            tft.drawString("co " + String(ina260.getCurrentConversionTime()) + ", " + String(ina260.getCurrentConversionTime()), 25, 161 - scrollTFT, 1);
            activeINA = true;
            break;
          default: activeINA = false; drawBmp(SPIFFS, "/notok12.bmp", 19, 146 - scrollTFT); break;
        }

        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.drawString("SCD30", 90, 137 - scrollTFT, 1);
        if (scd30.begin()) {
          drawBmp(SPIFFS, "/ok12.bmp", 84, 146 - scrollTFT);
          if (!scd30.getAutoSelfCalibration()) scd30.setAutoSelfCalibration(true);
          //          tft.drawString("Offs: " + (String(scd30.getTemperatureOffset(), 1) + "C"), 90, 147 - scrollTFT, 1);
          tft.drawString(String(scd30.getTemperatureOffset(), 1)  + "* " + String(scd30.getAutoSelfCalibration()), 90, 161 - scrollTFT, 1);
          activeSCD = true;
        } else {
          activeSCD = false;
          drawBmp(SPIFFS, "/notok12.bmp", 84, 146 - scrollTFT);
        }

        tft.drawString("CCS811", 150, 137 - scrollTFT, 1);
        if (CCS811err) {
          tft.drawString(printSensorError(), 150, 161 - scrollTFT, 1);
          drawBmp(SPIFFS, "/notok12.bmp", 144, 146 - scrollTFT);
          activeCCS = false;
        } else {
          if (myCCS811.appValid()) {
            drawBmp(SPIFFS, "/ok12.bmp", 144, 146 - scrollTFT);
            tft.drawString(String(myCCS811.getResistance(), 1), 150, 161 - scrollTFT, 1);
            activeCCS = true;
          } else {
            drawBmp(SPIFFS, "/inactive12.bmp", 144, 146 - scrollTFT);
            tft.drawString("appinv", 150, 161 - scrollTFT, 1);
          }
        }

        tft.drawString("DS18B20", 210, 137 - scrollTFT, 1);
        if (DTdevicecount < 8) {
          drawBmp(SPIFFS, "/inactive12.bmp", 204, 146 - scrollTFT);
        } else if (DTdevicecount == 0) {
          drawBmp(SPIFFS, "/notok12.bmp", 204, 146 - scrollTFT);
        } else {
          drawBmp(SPIFFS, "/ok12.bmp", 204, 146 - scrollTFT);
        }
        tft.drawString(String(DTdevicecount) + " / 8", 210, 161 - scrollTFT, 1);
      }

      x = 179;
      y = 173;
      tft.setTextDatum(TL_DATUM);
      if (SDpresent) {
        tft.setTextColor(TFT_GREEN);
      } else {
        tft.setTextColor(TFT_LIGHTGREY);
      }
      tft.drawString("SD Card", x, y - scrollTFT, 1);

      if (loggingActive) {
        tft.setTextColor(TFT_GREEN);
      } else {
        tft.setTextColor(TFT_LIGHTGREY);
      }
      tft.drawString("logging", x, y + 10 - scrollTFT, 1);

      if (lowPowerMode) {
        tft.setTextColor(TFT_GREEN);
      } else {
        tft.setTextColor(TFT_LIGHTGREY);
      }
      tft.drawString("lowPower", x, y + 20 - scrollTFT, 1);

      if (deepSleepActive) {
        tft.setTextColor(TFT_GREEN);
      } else {
        tft.setTextColor(TFT_LIGHTGREY);
      }
      tft.drawString("deepSleep", x, y + 30 - scrollTFT, 1);

      if (chargingActive) {
        tft.setTextColor(TFT_GREEN);
      } else {
        tft.setTextColor(TFT_LIGHTGREY);
      }
      tft.drawString("Charging", x, y + 40 - scrollTFT, 1);

      if (alarmEnable) {
        tft.setTextColor(TFT_GREEN, TFT_BLACK);
      } else {
        tft.setTextColor(TFT_RED, TFT_BLACK);
      }
      tft.drawString("Alarms", x, y + 50 - scrollTFT, 1);

      tft.setTextColor(TFT_GREEN, TFT_BLACK);
      tft.drawString(String(bklTimeout) + "s t/o", x, y + 60 - scrollTFT, 1);

      tft.setTextColor(TFT_WHITE);
      //      tft.drawString("SPI " + String(int(SPI_FREQUENCY / uS_TO_S_FACTOR)) + "MHz", x, y + 70 - scrollTFT, 1);
      tft.drawString("SPI " + String(SPI_FREQUENCY / uS_TO_S_FACTOR) + "MHz", x, y + 70 - scrollTFT, 1);
      tft.drawString("I2C " + String(Wire.getClock()) + "MHz", x, y + 80 - scrollTFT, 1);
      tft.drawString("I2C " + String(I2C_SPEED_FAST / 1000) + "kb/s", x, y + 90 - scrollTFT, 1);

      tft.drawString(String("     "), x, y + 100 - scrollTFT, 1);

      if (!notiOn) {
        tft.setTextDatum(TC_DATUM);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setCursor(0, 32 - scrollTFT);
        tft.setTextSize(2);
        //tft.print(esp_get_free_internal_heap_size() / 1024); tft.println("kb intRAM ");
        tft.print(esp_get_free_heap_size() / 1024); tft.println("kb RAM ");
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setTextSize(1);
        tft.println();
        tft.print(esp_get_idf_version()); // tft.print(ESP.getSdkVersion());

        for (int i = 0; i < 17; i = i + 8) {
          chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
        }

        tft.print(" - ");
        tft.printf("%s Rev%d\n", ESP.getChipModel(), ESP.getChipRevision());
        tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
        tft.print("Chip: "); tft.print(chipId); tft.print(" - ");
        tft.print(ESP.getChipCores()); tft.print("x ");
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.print(getCpuFrequencyMhz()); tft.println("MHz ");
        tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
        tft.print("CPU0: "); tft.setTextColor(TFT_WHITE, TFT_BLACK); verbose_print_reset_reason(rtc_get_reset_reason(0)); tft.println();
        tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
        tft.print("CPU1: "); tft.setTextColor(TFT_WHITE, TFT_BLACK); verbose_print_reset_reason(rtc_get_reset_reason(1)); tft.println();
      }

      notiWarnings();
      wifiPrint();
      readEnvironmentData();   // CCS811 Function

      if ( millisElapsed - previousTime1 > 9000 ) {     // WiFi Network Scanner every 9 sec

        previousTime1 = millisElapsed;
        yield();
        wifiNetworks = WiFi.scanNetworks();

        tft.setTextSize(1);
        tft.setCursor(0, 172 - scrollTFT);
        tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
        tft.print(wifiNetworks); tft.println(" Networks ");
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.println();

        for (int thisNet = 0; thisNet < wifiNetworks; thisNet++) {
          wiFiName = WiFi.SSID(thisNet);
          tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
          tft.print(thisNet);
          tft.print(" ");
          tft.setTextColor(TFT_WHITE, TFT_BLACK);
          tft.print(wiFiName.substring(0, 14));
          tft.print(" ");
          tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
          tft.print(WiFi.RSSI(thisNet));
          tft.print("dB ");
          tft.setTextColor(TFT_DARKGREY, TFT_BLACK);
          tft.print(translateEncryptionType(WiFi.encryptionType(thisNet)));

          i = 14 - wiFiName.length();
          for (i; i > 0; i--) {
            tft.print(" ");
          }
          tft.println();
          tft.setTextColor(TFT_WHITE, TFT_BLACK);
        }
      }


      tft.setTextSize(1);
      tft.setTextDatum(MC_DATUM);
      tft.drawRoundRect(193, 35, 55, 12, 3, TFT_MIDDLEGREY); // (xO, yO, Length, Width, Radius, color)
      tft.setCursor(196, 37);
      FPS = millis() - millisElapsed;
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.print(FPS); tft.print("ms ");
      //      tft.setCursor(161, 4);
      //      tft.print(everyX); tft.print("ms ");
    }
    scrollTFT = 0;
    if (pageCount != 1) {
      Wire.beginTransmission(0x69);   //  AMG8833 Modes
      Wire.write(0x00);   // Register
      Wire.write(0x10);   // Value to Register 0x00 - Normal, 0x10 - Sleep, 0x20 - 60sec, 0x21 - 10sec
      if (Wire.endTransmission() != 0) activeAMG = false;
    }
    if (pageCount == 2) page2();
    if (pageCount == 0) pageCount = 0; menuCar = 1; page0();
  }
}


void page2() {                     // SD Directories

  if (pageCount == 2) {
    tft.fillScreen(TFT_BLACK);
    scrollTFT = 0;
    tft.setCursor(0, 60);
    tft.setTextSize(2);
    drawBmp(SPIFFS, "/car/folder.bmp", 205, 3);
    //    tft.drawFastHLine(0, 56 - scrollTFT, 240, TFT_MIDDLEGREY);

    if (SD.begin(15, spiSD, SPI_FREQUENCY)) {
      SDpresent = true;
      if (loggingActive) drawBmp(SPIFFS, "/logging12.bmp", 180, 8);
    } else {
      tft.setTextSize(2);
      tft.print(" --- NO SD Card --- ");
      spiSD.begin(14, 25, 13, 15);
      SDpresent = false;
      loggingActive = false;
    }

    tft.setTextSize(2);
    tft.setTextColor(TFT_BLUE, TFT_BLACK);
    tft.setCursor(0, 0);
    tft.print("Size: ");
    if (SDpresent) {
      if (SD.cardSize() == 0) {
        tft.print("---");
        loggingActive = false;
      } else {
        tft.print(SD.cardSize() / (1024 * 1024));
      }
      tft.println(" Mb ");
    } else {
      tft.println("no sd");
    }
    tft.print("Used: ");
    if (SDpresent) {
      if (SD.usedBytes() == 0) {
        tft.print("---");
      } else {
        tft.print(SD.usedBytes() / uS_TO_S_FACTOR);
      }
      tft.println(" Mb ");
    } else {
      tft.println("no sd");
    }

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setCursor(0, scrollTFT + 55);

    while (pageCount == 2) {
      SYSTEM();
      if (!notiOn) {
        drawBmp(SPIFFS, "/car/folder2.bmp", 205, 3);
        everyXsec();
      }

      tft.drawFastHLine(9, 34, 218, TFT_MIDDLEGREY);
      tft.drawFastHLine(7, 35, 217, TFT_MIDDLEGREY);

      tft.setTextSize(2);
      tft.setCursor(5, 38);

      if (!notiOn) {
        tft.fillRoundRect(3, 34, 52, 18, 4, TFT_MIDDLEGREY);
        tft.fillRoundRect(185, 34, 52, 18, 4, TFT_MIDDLEGREY);
        tft.setTextColor(TFT_BLACK, TFT_MIDDLEGREY);
        tft.setTextDatum(TC_DATUM);
        tft.drawString(LogFile, 120, 36, 1);
      }

      tft.setTextColor(TFT_WHITE);

      notiWarnings();
      wifiPrint();
      checkScreenState();
      readEnvironmentData();   // CCS811 Function

      tft.setCursor(0, 60 - scrollTFT);
      File root = SD.open("/");

      tft.setTextSize(1);
      if (!notiOn) printDirectory(root, 0);
      tft.println("                    ");
      tft.println("                    ");
      tft.println("                    ");
      tft.println("                    ");
      tft.println("                    ");
      tft.println("                    ");
    }
  }
  if (pageCount == 1) page1();
  if (pageCount == 3) pageCount = 0; menuCar = 1; page0();
}

void page3() {         // System

  if (pageCount == 3) {
    previousMs = 0;
    tft.fillScreen(TFT_BLACK);

    drawBmp(SPIFFS, "/tProbesD240.bmp", 88, 0);   // 24bit
    //    tft.pushImage(0, 0, TFT_WIDTH, TFT_HEIGHT, tProbes240transp);
    //    tft.pushImage(0, 0, TFT_WHIDTH, TFT_HEIGHT, TProbesB240);

    byte t1y = 40;  // AMB
    byte t2y = 66;  // BAT
    byte t3y = 205; // LED
    byte t4y = 33;  // ESP
    byte t5y = 64;  // PWR
    byte t6y = 152; // X
    byte t7y = 178; // BAT
    byte t8y = 203; // BUS

    tft.drawFastHLine(0, 17, 90, TFT_MIDDLEGREY);
    tft.drawFastHLine(154, 17, 90, TFT_MIDDLEGREY);
    tft.drawFastHLine(0, TFT_HEIGHT - 17, 90, TFT_MIDDLEGREY);
    tft.drawFastHLine(152, TFT_HEIGHT - 17, 92, TFT_MIDDLEGREY);

    tft.drawRoundRect(193, 17, 55, 12, 3, TFT_MIDDLEGREY); // (xO, yO, width, length, Radius, color)
    tft.setTextColor(TFT_MIDDLEGREY);
    tft.drawRoundRect(168, 90, 64, 106, 5, TFT_LIGHTGREY); // temp box
    tft.drawRoundRect(8, 85, 64, 60, 5, TFT_LIGHTGREY); // temp box
    tft.setTextDatum(TL_DATUM);
    tft.setTextPadding(50);
    tft.setTextSize(2);

    tft.drawLine(134, 31, 161, t1y + 6, TFT_WHITE); //t1
    tft.drawLine(161, t1y + 2, 161, t1y + 11, TFT_WHITE);
    tft.setCursor(168, t1y);
    tft.print("AMB");

    tft.drawLine(143, 86, 161, t2y + 6, TFT_WHITE); //t2
    tft.drawLine(161, t2y + 2, 161, t2y + 11, TFT_WHITE);
    tft.setCursor(168, t2y);
    tft.print("BAT");

    tft.drawLine(128, 211, 161, t3y + 6, TFT_WHITE); //t3
    tft.drawLine(161, t3y + 2, 161, t3y + 11, TFT_WHITE);
    tft.setCursor(168, t3y);
    tft.print("LED");

    tft.drawLine(113, 39, 78, t4y + 6, TFT_WHITE); //t4
    tft.drawLine(78, t4y + 2, 78, t4y + 11, TFT_WHITE);
    tft.setCursor(38, t4y);
    tft.print("ESP");

    tft.drawLine(111, 116, 78, t5y + 6, TFT_WHITE); //t5
    tft.drawLine(78, t5y + 2, 78, t5y + 11, TFT_WHITE);
    tft.setCursor(38, t5y);
    tft.print("PW1");

    tft.drawLine(98, 153, 78, t6y + 6, TFT_WHITE); //t6
    tft.drawLine(78, t6y + 2, 78, t6y + 11, TFT_WHITE);
    tft.setCursor(38, t6y);
    tft.print("PW2");

    tft.drawLine(97, 163, 78, t7y + 6, TFT_WHITE); //t7
    tft.drawLine(78, t7y + 2, 78, t7y + 11, TFT_WHITE);
    tft.setCursor(38, t7y);
    tft.print("BAT");

    tft.drawLine(102, 209, 78, t8y + 6, TFT_WHITE); //t8
    tft.drawLine(78, t8y + 2, 78, t8y + 11, TFT_WHITE);
    tft.setCursor(38, t8y);
    tft.print("BUS");

    tft.setTextSize(1);
    tft.setTextDatum(TC_DATUM);
    tft.setTextColor(TFT_MIDDLEGREY);
    tft.drawString("tempBME", 200, 109, 1);
    tft.drawString("tempHDC", 200, 134, 1);
    tft.drawString("tempSCD", 200, 159, 1);
    tft.drawString("dew Point", 200, 184, 1);

    tft.drawString("humidHDC", 40, 106, 1);
    tft.drawString("humidSCD", 40, 131, 1);

    tft.setTextSize(1);
    tft.setTextColor(TFT_CYAN);
    tft.setTextDatum(BL_DATUM);
    tft.drawString("a" + String(Revision), 202, 240, 2);

    while (pageCount == 3) {
      SYSTEM();
      if (!notiOn) everyXsec();

      tft.setTextSize(1);
      tft.setTextPadding(50);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.setTextDatum(TC_DATUM);
      if (screenState) {
        tft.drawString(String(tempBME), 200, 93, 2);
        tft.drawString(String(tempHDC), 200, 118, 2);
        tft.drawString(String(tempSCD), 200, 143, 2);
        tft.drawString(String(dewPoint), 200, 168, 2);

        if (wetAlarm) tft.setTextColor(TFT_INDIA, TFT_BLACK);
        tft.drawString(String(humidHDC), 40, 90, 2);
        tft.drawString(String(humidSCD), 40, 115, 2);

        if (everyXsecFlag) {
          tft.setTextSize(2);
          tft.setTextDatum(TL_DATUM);

          if (!notiOn) {
            if (ta1) {
              tft.setTextColor(TFT_RED, TFT_BLACK);
            } else if (t1 > tA1) {
              tft.setTextColor(TFT_GOLD, TFT_BLACK);
            } else {
              tft.setTextColor(TFT_WHITE, TFT_BLACK);
            }
            tft.setCursor(210, t1y);
            tft.print(t1);

            if (ta2) {
              tft.setTextColor(TFT_RED, TFT_BLACK);
            } else if (t2 > tA2) {
              tft.setTextColor(TFT_GOLD, TFT_BLACK);
            } else {
              tft.setTextColor(TFT_WHITE, TFT_BLACK);
            }
            tft.setCursor(210, t2y);
            tft.print(t2);
          }

          if (ta3) {
            tft.setTextColor(TFT_RED, TFT_BLACK);
          } else if (t3 > tA3) {
            tft.setTextColor(TFT_GOLD, TFT_BLACK);
          } else {
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
          }
          tft.setCursor(210, t3y);
          tft.print(t3);

          if (!notiOn) {
            if (ta4) {
              tft.setTextColor(TFT_RED, TFT_BLACK);
            } else if (t4 > tA4) {
              tft.setTextColor(TFT_GOLD, TFT_BLACK);
            } else {
              tft.setTextColor(TFT_WHITE, TFT_BLACK);
            }
            tft.setCursor(3, t4y);
            tft.print(t4);

            if (ta5) {
              tft.setTextColor(TFT_RED, TFT_BLACK);
            } else if (t5 > tA5) {
              tft.setTextColor(TFT_GOLD, TFT_BLACK);
            } else {
              tft.setTextColor(TFT_WHITE, TFT_BLACK);
            }
            tft.setCursor(3, t5y);
            tft.print(t5);
          }

          if (ta6) {
            tft.setTextColor(TFT_RED, TFT_BLACK);
          } else if (t6 > tA6) {
            tft.setTextColor(TFT_GOLD, TFT_BLACK);
          } else {
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
          }
          tft.setCursor(3, t6y);
          tft.print(t6);

          if (ta7) {
            tft.setTextColor(TFT_RED, TFT_BLACK);
          } else if (t7 > tA7) {
            tft.setTextColor(TFT_GOLD, TFT_BLACK);
          } else {
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
          }
          tft.setCursor(3, t7y);
          tft.print(t7);

          if (ta8) {
            tft.setTextColor(TFT_RED, TFT_BLACK);
          } else if (t8 > tA8) {
            tft.setTextColor(TFT_GOLD, TFT_BLACK);
          } else {
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
          }
          tft.setCursor(3, t8y);
          tft.print(t8);
        }
      }
      wifiPrint();
      checkScreenState();
      notiWarnings();
      readEnvironmentData();   // CCS811 Function
      if (screenState && everyXsecFlag) printStatusBar();
      smlPRNT2(String(Volts) + "v", String(Amps) + "a", -16, 0);

      tft.setTextSize(1);
      tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
      tft.setCursor(199, 19);
      FPS = millis() - millisElapsed;
      if (!notiOn) {
        tft.print(FPS);
        tft.print("ms ");
        tft.setCursor(165, 4);
        tft.print(everyX); tft.print("ms ");
      }
    }
    if (pageCount == 4); page4();
    if (pageCount == 2) pageCount = 0; menuCar = 2; page0();
  }
}


void page4() {  // Graph Page    --     Sensors go into High Speed mode todo: sample Rate sensor values

  if (pageCount == 4) {
    tft.fillScreen(TFT_BLACK);
    edgeL = 5;
    tft.drawRoundRect(193, 17, 55, 12, 3, TFT_MIDDLEGREY); // (xO, yO, Length, Width, Radius, color)
    tft.drawRoundRect(edgeL, box1Top, boxWidth, boxHeight, 3, TFT_LIGHTGREY);
    tft.drawRoundRect(edgeL, box2Top, boxWidth, boxHeight, 3, TFT_LIGHTGREY);
    staticGraphGFX();
    cycleCount = 0;

    prevCO2 = box1Bottom - 2; // graphlines startpoints
    prevTVOC = box1Bottom - 2;
    lastpowMW = box2Bottom - 10;

    //    scd30.setMeasurementInterval(2);
    myCCS811.setDriveMode(4); // 0=idle, 1=1sec, 2=10sec, 3=60sec, 4=RAW
    myBME280.setStandbyTime(1);  // 4 = 500ms, 5 = 1000ms, 0 = 0.5ms,

    everyXms = 500; // print dataPoint every 0.5 sec

    while (pageCount == 4) {
      if (!notiOn) everyXsec();
      SYSTEM();

      if (everyXsecFlag) { // print dataPoint every x sec
        // Lvolt = map(Volts, lowVoltAlarm, highVoltAlarm, box2Bottom - 1, box2Top + 1); // value, fromLow, fromHigh, toLow, toHigh

        Lvolt = map(SOC, 0, 100, box2Bottom - 2, box2Top + 2); // value, fromLow, fromHigh, toLow, toHigh
        currA = map(Amps, 0, 5, box2Bottom - 2, box2Top + 2);

        tft.setTextSize(1);
        if (Watts > 6000) {                            // converts from milliWatts to Watts
          powMW = map(Watts, 0, 12000, box2Bottom - 1, box2Top + 2);
        } else {
          powMW = map(Watts, 0, 6000, box2Bottom - 1, box2Top + 2);
        }

        pCO2 = map(co2SCD, 0, 5000, box1Bottom, box1Top - 1); // 8000
        pTVOC = map(tvocSMPL, 0, 2500, box1Bottom, box1Top - 1); // 2500
        TempGraph = map(tempSCD, 0, 100, box1Bottom, box1Top - 1);
        RHgraph = map(humidSCD, 0, 99, box1Bottom, box1Top - 1);

        tft.drawPixel(edgeL + 1, TempGraph - 2, TFT_WHITE);
        tft.drawPixel(edgeL + 1, RHgraph - 2, TFT_OLIVE);

        tft.drawLine(edgeL + 1, prevTVOC - 2, edgeL + 1, pTVOC - 2, TFT_ORANGE);
        prevTVOC = pTVOC;
        tft.drawLine(edgeL + 1, prevCO2 - 2, edgeL + 1, pCO2 - 2, TFT_CYAN);
        prevCO2 = pCO2;

        tft.drawPixel(edgeL + 1, Lvolt - 2, TFT_INDIA);

        if (chargingActive) {
          tft.drawLine(edgeL + 1, -3 - lastpowMW, edgeL + 1, -3 - powMW, TFT_GREEN);
        } else {
          tft.drawLine(edgeL + 1, lastpowMW - 3, edgeL + 1, powMW - 3, TFT_YELLOW);
        }
        lastpowMW = powMW;

        if (fanActive) tft.drawPixel(edgeL + 1, box2Bottom - 4, TFT_RED);
        //        if (screenState) tft.drawPixel(edgeL + 1, box2Bottom - 2, TFT_GREEN);

        if (edgeL == 10 || edgeL == 60 || edgeL == 110 || edgeL == 160 || edgeL == 208) {
          tft.setTextColor(TFT_LIGHTGREY);
          tft.setCursor(edgeL - 1, Lvolt + 3);
          tft.print(Volts);
          //          tft.setCursor(edgeL - 1, box2Top + 6);
          //          if (Volts < 8) tft.print(hr + ":" + mi); // print time on graph
        }

        if (edgeL > 229) {
          edgeL = 5;
          tft.fillRoundRect(edgeL + 1, box2Top + 1, boxWidth - 2, boxHeight - 2, 3, TFT_BLACK);
          tft.fillRoundRect(edgeL + 1, box1Top + 1, boxWidth - 2, boxHeight - 2, 3, TFT_BLACK);
          staticGraphGFX();
          tft.drawRoundRect(193, 17, 55, 12, 3, TFT_MIDDLEGREY); // (xO, yO, Length, Width, Radius, color)
        }
        edgeL++;
      }

      tft.setTextColor(TFT_CYAN, TFT_BLACK);
      tft.setCursor(28, box1Bottom + 4);
      tft.print(co2SCD);
      tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
      tft.print("ppm  ");
      tft.setTextColor(TFT_GOLD, TFT_BLACK);
      tft.setCursor(105, box1Bottom + 4);
      tft.print(tvocSMPL);
      tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
      tft.print("ppb  ");
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.setCursor(172, box1Bottom + 4);
      tft.print(tempSCD, 0);
      tft.setTextColor(TFT_OLIVE, TFT_BLACK);
      tft.setCursor(214, box1Bottom + 4);
      tft.print(humidSCD, 0);

      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.setCursor(51, box2Bottom + 4);
      if (Volts < 7 && Volts > 6.5) tft.setTextColor(TFT_ORANGE, TFT_BLACK);
      if (Volts <= 6.5) tft.setTextColor(TFT_INDIA, TFT_BLACK);
      tft.print(Volts);
      tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
      tft.print("v");
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.setCursor(118, box2Bottom + 4);
      if (Amps > ampsFanTH) tft.setTextColor(TFT_INDIA, TFT_BLACK);
      tft.print(Amps);
      tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
      tft.print("a ");


      tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
      tft.print("LOG:");
      if (loggingActive)
      {
        tft.setTextColor(TFT_MIDDLEGREEN, TFT_BLACK);
        tft.print("ON  ");
      } else {
        tft.print("OFF ");
      }

      tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
      tft.print("FAN:");
      if (fanActive)
      {
        tft.setTextColor(TFT_MIDDLEGREEN, TFT_BLACK);
        tft.print("ON ");
      } else {
        tft.print("OF");
      }

      notiWarnings();
      wifiPrint();
      readEnvironmentData();   // CCS811 Function

      tft.setTextSize(1);
      tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
      if (!notiOn) {
        tft.setCursor(197, 19);
        FPS = millis() - millisElapsed;
        tft.print(FPS); tft.print("ms  ");
      }
    }
    myCCS811.setDriveMode(1); // 0=idle, 1=1sec, 2=10sec, 3=60sec, 4=RAW
    myBME280.setStandbyTime(4);  // 4 = 500ms, 5 = 1000ms, 0 = 0.5ms,
    scd30.setMeasurementInterval(5);
    everyXms = 1000;
    if (pageCount == 3) page3();
    if (pageCount == 5) pageCount = 0; menuCar = 2; page0();
  }
}

void page5() {

  if (pageCount == 5) {    // HOME
    previousMs = 0;

    tft.fillScreen(TFT_BLACK);
    //    drawBmp(SPIFFS, "/HEX240.bmp", 0, 0);   // 24bit
    tft.pushImage(0, 0, TFT_WIDTH, TFT_HEIGHT, HexWabe240);  // HEX240R_8bit

    /*
        tft.setTextSize(1);
        tft.setTextColor(TFT_CYAN);
        tft.setTextDatum(BL_DATUM);
        tft.drawString("v" + String(Revision), 210, 240, 2);
        tft.setTextColor(TFT_BLACK);
        tft.setTextDatum(BC_DATUM);
        tft.drawNumber(counter, 120, 225, 2);

        tft.drawRoundRect(193, 17, 55, 12, 3, TFT_MIDDLEGREY);
    */

    spr.setTextPadding(65);
    spr.setTextDatum(TL_DATUM);
    spr.setColorDepth(8);      // Create an 8bpp Sprite
    spr.setTextSize(1);

    tft.setTextSize(1);
    tft.setTextDatum(MC_DATUM);
    tft.setTextColor(TFT_LIGHTGREY);
    tft.setTextPadding(30);


    angle = 30;
    needle.fillCircle(needle.width() / 2, 5, 3, TFT_DARKGREY);
    while (angle > -150) {
      plotDial(dialX, dialY, angle, TFT_BLACK);
      angle -= 2;
      if (angle < -150) break;
    }
    needle.fillCircle(needle.width() / 2, 5, 3, TFT_WHITE);

    angle = -30;
    needle2.fillCircle(needle2.width() / 2, 5, 3, TFT_DARKGREY);
    while (angle < 150) {
      plotDial2(dial2X, dial2Y, angle, TFT_BLACK);
      angle += 2;
      if (angle > 150) break;
    }
    needle2.fillCircle(needle2.width() / 2, 5, 3, TFT_WHITE);

    angle = 270;
    needle3.fillCircle(needle3.width() / 2, 5, 3, TFT_DARKGREY); // change color of dial needle
    while (angle > 90) {
      plotDial3(dial3X, dial3Y, angle, TFT_BLACK);
      angle -= 2;
      if (angle < 90) break;
    }
    needle3.fillCircle(needle3.width() / 2, 5, 3, TFT_WHITE);

    tft.setSwapBytes(false);

    tft.setPivot(17, 185);
    spr.createSprite(55, 20);
    spr.setPivot(32, 35);      //32,55 Set pivot relative to top left corner of Sprite
    spr.fillSprite(TFT_WHITE);
    spr.setTextColor(TFT_BLACK, TFT_WHITE);
    spr.drawString("   UVI", 0, 0, 2);
    spr.pushRotated(60, 8);
    spr.deleteSprite();

    tft.setPivot(245, 186);
    spr.createSprite(50, 20);
    spr.setPivot(32, 55);      //32,55 Set pivot relative to top left corner of Sprite
    spr.fillSprite(TFT_WHITE);
    spr.setTextColor(TFT_BLACK, TFT_WHITE);
    if (map(co2SCD, 0, 5000, -150, 30) > map(tvocSMPL, 0, 800, -150, 30)) {
      spr.drawString("  CO2", 0, 0, 2);
    } else {
      spr.drawString("  VOC", 0, 0, 2);
    }
    spr.pushRotated(-60, 12);
    tft.setSwapBytes(true);
    spr.deleteSprite();

    while (pageCount == 5) {
      SYSTEM();
      everyXsec();

      if (screenState) {
        tft.setTextDatum(MC_DATUM);
        tft.setTextSize(1);

        if (everyXsecFlag && !powerAlarm && !tempAlarm) {
          tft.setTextPadding(100);
          tft.setTextColor(TFT_WHITE, TFT_BLACK);
          tft.drawString(RTCprint, 120, 105, 4);

          tft.setTextPadding(60);
          tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
          tft.drawString(String(daysOfTheWeek[dow]) + " " + RTCd, 120, 120, 2);

          if (!notiOn) {
            tft.setPivot(245, 186);
            spr.createSprite(50, 20);
            spr.setPivot(32, 55);      // 32, 55 Set pivot relative to top left corner of Sprite
            spr.fillSprite(TFT_WHITE);
            spr.setTextColor(TFT_BLACK, TFT_WHITE);
            if (map(co2SCD, 0, 5000, -150, 30) > map(tvocSMPL, 0, 800, -150, 30)) {
              spr.drawString("  CO2", 0, 0, 2);
            } else {
              spr.drawString("  VOC", 0, 0, 2);
            }
            spr.pushRotated(-60, 12);

            if (map(co2SCD, 0, 5000, -150, 30) > map(tvocSMPL, 0, 800, -150, 30)) {
              angle = map(co2SCD, 0, 5000, -150, 30);
            } else {
              angle = map(tvocSMPL, 0, 800, -150, 30);
            }

            if (angle < 0) angle += 30; // max angle is 30
            needle.fillCircle(needle.width() / 2, 5, 3, TFT_DARKGREY);
            while (angle > -140) {
              plotDial(dialX, dialY, angle, TFT_BLACK);
              angle -= 2;
              if (angle <= -140) break;
            }

            tft.setTextPadding(22);
            if (AirQI > 4) {
              dial.setTextColor(TFT_INDIA, TFT_BLACK);
              //            needle.fillCircle(needle.width() / 2, 5, 3, TFT_INDIA);
            } else if (AirQI > 2 && AirQI < 4) {
              dial.setTextColor(TFT_GOLD, TFT_BLACK);
              //            needle.fillCircle(needle.width() / 2, 5, 3, TFT_GOLD);
            } else if (AirQI < 2) {
              dial.setTextColor(TFT_WHITE, TFT_BLACK);
              //            needle.fillCircle(needle.width() / 2, 5, 3, TFT_WHITE);
            }


            if (map(co2SCD, 0, 5000, -150, 30) > map(tvocSMPL, 0, 800, -150, 30)) {
              angle = map(co2SCD, 0, 5000, -150, 30);
            } else {
              angle = map(tvocSMPL, 0, 800, -150, 30);
            }

            if (angle == -150) angle += 10;
            needle.fillCircle(needle.width() / 2, 5, 3, TFT_WHITE);
            while (angle > -150) {
              angle -= 2;
              plotDial(dialX, dialY, angle, TFT_BLACK);
              if (angle <= -150) break;
            }


            dial2.setTextColor(uviColor());
            angle = map(UVI, 0, 13, 150, -30);
            angle += 20;
            needle2.fillCircle(needle2.width() / 2, 5, 3, TFT_DARKGREY);
            while (angle < 140) {
              plotDial2(dial2X, dial2Y, angle, TFT_BLACK);
              angle += 2;
              if (angle >= 140) break;
            }
            needle2.fillCircle(needle2.width() / 2, 5, 3, TFT_WHITE);

            angle = map(UVI, 0, 13, 150, -30);
            if (angle == 150) angle -= 10;
            while (angle < 150) {
              plotDial2(dial2X, dial2Y, angle, TFT_BLACK);
              angle += 2;
              if (angle >= 150) break;
            }

            angle = map(tempBME, -15, 45, 270, 90);
            needle3.fillCircle(needle3.width() / 2, 5, 3, TFT_WHITE); // change color of dial needle
            plotDial3(dial3X, dial3Y, angle, TFT_TRANSPARENT);

            tft.setTextColor(TFT_BLACK, TFT_WHITE);
            tft.setTextDatum(TC_DATUM);
            tft.setTextPadding(105);
            tft.drawString(String(humidHDC, 1) + "%  " + String(altBME) + "m", 120, 16, 2);
            //            tft.drawString("Alt: " + String(altBME) + "m", 120, 207, 2);
          }
        }

        if (everyXsecFlag && !notiOn) {
          printStatusBar();

          tft.setTextDatum(TC_DATUM);
          tft.setTextPadding(92);
          //          tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
          byte batMap = map(SOC, 0, 100, 0, 88);

          tft.fillRoundRect(71 + batMap, 211, 93 - batMap, 11, 3, TFT_LIGHTGREY);
          tft.fillRoundRect(77, 211, batMap, 11, 3, TFT_BATCOLOR);
          tft.drawRoundRect(77, 210, 88, 12, 3, TFT_LIGHTGREY);
          tft.drawRoundRect(76, 209, 90, 14, 4, TFT_LIGHTGREY);
          tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
          tft.drawString(BatteryTime + " " + String(capacityLeft / 1000.0, 1) + "Ah", 120, 189, 2);
          if (SOC > 50) {
            tft.setTextColor(TFT_LIGHTGREY);
          } else {
            tft.setTextColor(TFT_WHITE);
          }
          tft.drawString(String(SOC) + "%", 121, 213, 1);
        }

        //        tft.setTextPadding(22);
        //        tft.setTextSize(1);
        //        tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
        //        tft.setCursor(197, 19);
        FPS = millis() - millisElapsed;
        //        if (!notiOn) {
        //          tft.print(FPS);
        //          tft.print("ms  ");
        //          tft.setCursor(165, 4);
        //          tft.print(everyX); tft.print("ms ");
        //        }
      }
      //      checkScreenState();
      notiWarnings();
      wifiPrint();
      readEnvironmentData();   // CCS811 Function
    }
    if (pageCount == 6); page6();
    if (pageCount == 4) pageCount = 0; menuCar = 3; page0();
  }
}


void page6() { // Info CO2

  if (pageCount == 6) {
    tft.fillScreen(TFT_BLACK);
    drawBmp(SPIFFS, "/Moon240.bmp", 0, 190); // 154
    //    drawBmp(SPIFFS, "/EarthSmall.bmp", 167, 180);
    drawBmp(SPIFFS, "/car/mountain.bmp", 200, 8);

    edgeL = 6;
    tft.setTextSize(1);
    tft.setTextColor(TFT_BLACK);
    tft.setTextDatum(TL_DATUM);
    tft.drawString("High Exposure to CO2 can produce", edgeL, 56, 2);
    tft.drawString("a variety of health effects. These", edgeL, 71, 2);
    tft.drawString("may include headaches, dizziness, ", edgeL, 86, 2);
    tft.drawString("restlessness, tiredness, increased" , edgeL, 101, 2);
    tft.drawString("heartrate & decreased cognitive " , edgeL, 116, 2);
    tft.drawString("capacity. Prolonged CO2 levels as " , edgeL, 131, 2);
    tft.drawString("low as 1,000ppm (parts per Million)" , edgeL, 146, 2);
    tft.drawString("can cause health problems." , edgeL, 160, 2);
    tft.drawString("Sources are decomposition, respiration", edgeL, 175, 2);
    tft.drawString("and outgassing from Industrial Areas", edgeL, 190, 2);
    tft.drawString("Traffic and deforestation.", edgeL, 205, 2);
    tft.setTextColor(TFT_WHITE);
    edgeL = 5;
    tft.drawString("High Exposure to CO2 can produce", edgeL, 55, 2);
    tft.drawString("a variety of health effects. These", edgeL, 70, 2);
    tft.drawString("may include headaches, dizziness, ", edgeL, 85, 2);
    tft.drawString("restlessness, tiredness, increased" , edgeL, 100, 2);
    tft.drawString("heartrate & decreased cognitive " , edgeL, 115, 2);
    tft.drawString("capacity. Prolonged CO2 levels as " , edgeL, 130, 2);
    tft.drawString("low as 1,000ppm (parts per Million)" , edgeL, 145, 2);
    tft.drawString("can cause health problems." , edgeL, 159, 2);
    tft.drawString("Sources are decomposition, respiration", edgeL, 174, 2);
    tft.drawString("and outgassing from Industrial Areas", edgeL, 189, 2);
    tft.drawString("Traffic and deforestation.", edgeL, 204, 2);


    while (pageCount == 6) {
      SYSTEM();
      if (!notiOn) {
        everyXsec();

        tft.setTextSize(1);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        //        tft.print("CO2 ");
        if (co2SCD > 1000 && co2SCD < 2000) tft.setTextColor(TFT_GOLD, TFT_BLACK);
        if (co2SCD > 2000 && co2SCD < 3000) tft.setTextColor(TFT_ORANGE, TFT_BLACK);
        if (co2SCD > 4000 && co2SCD < 5000) tft.setTextColor(TFT_INDIA, TFT_BLACK);
        if (co2SCD > 5000) tft.setTextColor(TFT_RED, TFT_BLACK);
        if (!notiOn) tft.drawString("CO2  " + String(co2SCD) + "ppm", 10, 15, 4);
      }
      notiWarnings();
      wifiPrint();
      checkScreenState();
      readEnvironmentData();   // CCS811 Function

      //      tft.setTextSize(1);
      //      tft.setTextDatum(TL_DATUM);
      //      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      //      FPS = millis() - millisElapsed;
      //      if (!notiOn) {
      //        tft.drawString(String(FPS) + "ms ", 200, 37, 1);
      //        tft.drawRoundRect(193, 35, 55, 12, 3, TFT_MIDDLEGREY); // (xO, yO, Length, Width, Radius, color)
      //      }

    }
    if (pageCount == 5) page5();
    if (pageCount == 7) page7();
  }
}

void page7() {   // Info tVOC

  if (pageCount == 7) {
    tft.fillScreen(TFT_BLACK);

    drawBmp(SPIFFS, "/Moon240.bmp", 0, 190); // 154
    drawBmp(SPIFFS, "/car/mountain.bmp", 200, 8);

    tft.setTextSize(1);
    tft.setTextColor(TFT_BLACK);
    tft.setTextDatum(TL_DATUM);
    edgeL = 6;
    tft.drawString("Total Volatile Organic Compounds:", edgeL, 56, 2);
    tft.drawString("Are potenitally harmful Gases that", edgeL, 71, 2);
    tft.drawString("and can pose health and cancer risks", edgeL, 86, 2);
    //    tft.drawString("" , edgeL, 101, 2);
    tft.drawString("Outoor Sources:" , edgeL, 116, 2);
    tft.drawString("Traffic, Industrial Areas, Benzenes" , edgeL, 131, 2);
    tft.drawString("Oil/Gas extraction & processing." , edgeL, 146, 2);
    //    tft.drawString("" , edgeL, 160, 2);
    tft.drawString("Indoor Sources: ", edgeL, 175, 2);
    tft.drawString("Burning material, Appliances, Paint", edgeL, 190, 2);
    tft.drawString("Smoking, Aerosols, Flammable Gases", edgeL, 205, 2);
    //    tft.drawString("", edgeL, 220, 2);

    edgeL = 5;
    tft.setTextColor(TFT_WHITE);
    tft.drawString("Total Volatile Organic Compounds:", edgeL, 55, 2);
    tft.drawString("Are potenitally harmful Gases that", edgeL, 70, 2);
    tft.drawString("and can pose health and cancer risks", edgeL, 85, 2);
    //    tft.drawString("" , edgeL, 101, 2);
    tft.drawString("Outoor Sources:" , edgeL, 115, 2);
    tft.drawString("Traffic, Industrial Areas, Benzenes" , edgeL, 130, 2);
    tft.drawString("Oil/Gas extraction & processing." , edgeL, 145, 2);
    //    tft.drawString("" , edgeL, 159, 2);
    tft.drawString("Indoor Sources: ", edgeL, 174, 2);
    tft.drawString("Burning material, Appliances, Paint", edgeL, 189, 2);
    tft.drawString("Smoking, Aerosols, Flammable Gases", edgeL, 204, 2);
    //    tft.drawString("", edgeL, 219, 2);

    while (pageCount == 7) {
      SYSTEM();
      if (!notiOn) {
        everyXsec();
        tft.setTextSize(1);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        if (tvocCCS > 80 && tvocCCS < 180) tft.setTextColor(TFT_GOLD, TFT_BLACK);
        if (tvocCCS > 180 && tvocCCS < 400) tft.setTextColor(TFT_ORANGE, TFT_BLACK);
        if (tvocCCS > 400 && tvocCCS < 1500) tft.setTextColor(TFT_INDIA, TFT_BLACK);
        if (tvocCCS > 1500) tft.setTextColor(TFT_RED, TFT_BLACK);
        if (!notiOn) tft.drawString("tVOC  " + String(tvocSMPL) + "ppb", 10, 15, 4);
      }
      notiWarnings();
      wifiPrint();
      checkScreenState();
      readEnvironmentData();   // CCS811 Function


      //      tft.setTextSize(1);
      //      tft.setTextDatum(TL_DATUM);
      //      tft.drawRoundRect(193, 35, 55, 12, 3, TFT_MIDDLEGREY); // (xO, yO, Length, Width, Radius, color)
      //      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      FPS = millis() - millisElapsed;
      //      if (!notiOn) tft.drawString(String(FPS) + "ms ", 200, 37, 1);

    }
    if (pageCount == 6) page6();
    if (pageCount == 8) pageCount = 0; menuCar = 3; page0();
  }
}

void page8() {     // Thermal Cam

  if (pageCount == 8) {
    tft.fillScreen(TFT_BLACK);
    Wire.beginTransmission(0x69);   //  AMG8833 Modes
    Wire.write(0x00);     // Power Register
    Wire.write(0x00);     // Value to Register Normal 0x00, Sleep 0x10, 60sec 0x20, 10sec 0x21
    if (Wire.endTransmission() != 0) activeAMG = false;

    if (activeAMG) {
      tft.setTextSize(1);
      TFTon();
      count = millis();
      smlPRNT(String("--"), "CELSIUS", 0, 0);

      if (loggingActive) appendFile(SD, LogFile, "\nThermal Cam Measuring...\n");

      while (pageCount == 8) {
        SYSTEM();

        tft.setTextDatum(BC_DATUM);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);

        if (everyXsecFlag) everyXsecFlag = false;
        if (millis() - count > 1000) {
          everyXsecFlag = true;
          count = millis();
        }

        if (burstReading) {      // measure Burst Reading
          amgreadIndex = 0;
          amgtotal = 0;
          amgaverage = 0;

          while (burstReading) {
            millisElapsed = millis();
            if (everyXsecFlag) everyXsecFlag = false;
            if (millisElapsed - count > 1000) {
              everyXsecFlag = true;
              count = millis();
            }

            for (amgreadIndex; amgreadIndex <= amgNumReadings; amgreadIndex++) {

              if (measurePoint) {
                if (pixels[27] > pixels[28]) { //      Insert Input here <<--- 2 Center Pixel Max Burst reading
                  amgReadings[amgreadIndex] = pixels[27];
                } else {
                  amgReadings[amgreadIndex] = pixels[28]; // 35 ,36
                }
              } else {
                amgReadings[amgreadIndex] = maxTempAMG; //   Insert Input here <<--- MaxValue Burst reading
              }
              amgtotal += amgReadings[amgreadIndex];
              amgreadIndex++;
              if (amgreadIndex >= amgNumReadings) burstReading = false; break;
            }

            if (everyXsecFlag) { // everyX while burst reading
              if (measurePoint) {
                switch (amgreadIndex) {
                  case 0 ... 17: smlPRNT(String("3"), "Center", 0, 0); break;
                  case 18 ... 33: smlPRNT(String("2"), "Center", 0, 0); break;
                  case 34 ... amgNumReadings: smlPRNT(String("1"), "Center", 4, 0); break;
                }
              } else {
                switch (amgreadIndex) {
                  case 0 ... 17: smlPRNT(String("3"), "MAX", 0, 0); break;
                  case 18 ... 33: smlPRNT(String("2"), "MAX", 0, 0); break;
                  case 34 ... amgNumReadings: smlPRNT(String("1"), "MAX", 4, 0); break;
                }
              }
              if (amgSetHiRes) {
                COLS = 120; // 120, 111
                ROWS = 111;
                tft.setTextColor(TFT_BLACK, TFT_WHITE);
                tft.drawString("HiRes", 20, 20, 2);
                tft.setTextColor(TFT_WHITE, TFT_BLACK);
              } else {
                COLS = 30; // 30 , 28
                ROWS = 28; // 60, 56
              }
              boxsize = min(TFT_WIDTH / COLS, TFT_HEIGHT / ROWS);
            }

            if (amgSetHiRes) {          // Thermal Image print while Burst Reading
              amg.readPixels(pixels);
              maxTempAMG = pixels[64];  // find max value
              for (idx = 1; idx < 64; ++idx) {
                if (pixels[idx] > maxTempAMG) maxTempAMG = pixels[idx]; // find biggest value
              }
              minTempAMG = pixels[64];
              for (idx = 1; idx < 64; ++idx) {
                if (pixels[idx] < minTempAMG) minTempAMG = pixels[idx]; // find smallest value
              }
            } else {
              amg8833();
            }

            tft.drawRoundRect(-1, -11, TFT_WIDTH + 2, TFT_WIDTH - 5, 2, TFT_BLACK);
            tft.drawRoundRect(-1, -11, TFT_WIDTH + 2, TFT_WIDTH - 5, 4, TFT_BLACK);
            tft.drawRoundRect(-1, -11, TFT_WIDTH + 2, TFT_WIDTH - 5, 6, TFT_BLACK);
            tft.drawRoundRect(-1, -11, TFT_WIDTH + 2, TFT_WIDTH - 5, 7, TFT_BLACK);
            tft.drawRoundRect(-1, -11, TFT_WIDTH + 2, TFT_WIDTH - 5, 8, TFT_BLACK);
            tft.drawRoundRect(-1, -11, TFT_WIDTH + 2, TFT_WIDTH - 5, 10, TFT_BLACK);
            tft.drawRoundRect(-1, -11, TFT_WIDTH + 2, TFT_WIDTH - 5, 12, TFT_BLACK);

            if (measurePoint) {
              tft.drawRoundRect(80, 77, 80, 80, 38, TFT_RED);
              tft.drawRoundRect(81, 78, 78, 78, 37, TFT_INDIA);

              tft.setTextColor(TFT_GREEN, TFT_BLACK);
              if (pixels[27] > pixels[28]) {
                tft.drawString(String(pixels[27], 1) + " C", 120, 143, 2);
              } else {
                tft.drawString(String(pixels[28], 1) + " C", 120, 143, 2);
              }
              tft.setTextColor(TFT_WHITE, TFT_BLACK);
              //  tft.drawString(String("center Point"), 120, 160, 2);
              tft.drawFastHLine(115, 115, 11, TFT_RED);
              tft.drawFastVLine(120, 110, 11, TFT_RED);
            } else {
              //            tft.drawString(String("Max Value"), 120, 160, 2);
              tft.drawRoundRect(0, -10, 240, 234, 11, TFT_RED);
              tft.drawRoundRect(1, -9, 238, 232, 10, TFT_RED);
              tft.drawFastHLine(0, 0, 240, TFT_RED);
              tft.drawFastHLine(0, 1, 240, TFT_RED);
              tft.setTextColor(TFT_GREEN, TFT_BLACK);
            }

            /*
                      colorIndex = constrain(map(maxTempAMG, MINTEMP, MAXTEMP, 0, 255), 0, 255);        // print color bar
                      colorIndex2 = constrain(map(minTempAMG, MINTEMP, MAXTEMP, 0, 255), 0, 255);
                      idx = constrain(map(maxTempAMG, MINTEMP, MAXTEMP, 230, 10), 230, 10);
                      tft.fillRoundRect(8, 208, 225, 8, 3, TFT_BLACK);
                                for (idx; 10 < idx; --idx) {
                                  if (colorIndex > colorIndex2) colorIndex--;
                                  tft.drawFastVLine(idx, 209, 6, camColors[colorIndex]);
                                }
            */

            tft.setTextPadding(70);
            tft.drawString("Max " + String(maxTempAMG, 1) + " C", 192, 240, 2);
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.drawString("Min " + String(minTempAMG, 1) + " C", 50, 240, 2);
            tft.setTextPadding(0);

            FPS = millis() - millisElapsed;
            tft.setCursor(102, 225);
            tft.print(1000 / FPS); tft.print("fps ");
            tft.setCursor(106, 233);
            tft.print(everyX); tft.print("ms ");
          }
          amgaverage = amgtotal / amgreadIndex;
          smlPRNT(String(amgaverage), "CELSIUS", 5, -20);
        }

        amg8833();  // Main Thermal Image Print

        /*
          colorIndex = constrain(map(maxTempAMG, MINTEMP, MAXTEMP, 0, 255), 0, 255);        // print color bar
          colorIndex2 = constrain(map(minTempAMG, MINTEMP, MAXTEMP, 0, 255), 0, 255);
          tft.fillRoundRect(8, 208, 225, 8, 3, TFT_BLACK);
          for (colorIndex; colorIndex2 < colorIndex; --colorIndex) { // print color bar
            tft.fillRect((colorIndex / 1.15) + 10, 209, 1, 6, camColors[colorIndex]); // dynamic postition gradient
          }


                colorIndex = constrain(map(maxTempAMG, MINTEMP, MAXTEMP, 0, 255), 0, 255);        // print color bar
                colorIndex2 = constrain(map(minTempAMG, MINTEMP, MAXTEMP, 0, 255), 0, 255);
                idx = constrain(map(maxTempAMG, MINTEMP, MAXTEMP, 230, 10), 230, 10);
                tft.fillRoundRect(8, 208, 225, 8, 3, TFT_BLACK);
                for (idx; 10 < idx; --idx) {                   // print color bar
                if (colorIndex > colorIndex2) colorIndex--;
                tft.drawFastVLine(idx, 209, 6, camColors[colorIndex]);
                }
        */

        if (amgSetHiRes) {
          tft.drawFastHLine(0, 222, 240, TFT_BLACK);
          tft.drawFastHLine(0, 223, 240, TFT_BLACK);
        }
        tft.drawFastHLine(115, 115, 11, TFT_WHITE);
        tft.drawFastVLine(120, 110, 11, TFT_WHITE);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        if (pixels[27] > pixels[28]) {
          tft.drawString(String(pixels[27], 1) + " C", 120, 143, 2);
        } else {
          tft.drawString(String(pixels[28], 1) + " C", 120, 143, 2);
        }
        tft.drawRoundRect(-1, -11, TFT_WIDTH + 2, TFT_WIDTH - 5, 2, TFT_BLACK);
        tft.drawRoundRect(-1, -11, TFT_WIDTH + 2, TFT_WIDTH - 5, 4, TFT_BLACK);
        tft.drawRoundRect(-1, -11, TFT_WIDTH + 2, TFT_WIDTH - 5, 6, TFT_BLACK);
        tft.drawRoundRect(-1, -11, TFT_WIDTH + 2, TFT_WIDTH - 5, 7, TFT_BLACK);
        tft.drawRoundRect(-1, -11, TFT_WIDTH + 2, TFT_WIDTH - 5, 8, TFT_BLACK);
        tft.drawRoundRect(-1, -11, TFT_WIDTH + 2, TFT_WIDTH - 5, 10, TFT_BLACK);
        tft.drawRoundRect(-1, -11, TFT_WIDTH + 2, TFT_WIDTH - 5, 12, TFT_BLACK);

        if (everyXsecFlag) {
          //        tft.setTextDatum(BC_DATUM);
          //        tft.setTextSize(1);
          tft.setTextPadding(0);
          if (amgSetHiRes) {
            COLS = 120;
            ROWS = 111;
            tft.setTextColor(TFT_BLACK, TFT_WHITE);
            tft.drawString("HiRes", 20, 20, 2);
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
          } else if (!amgSetHiRes) {
            if (MINTEMP - MAXTEMP > 5) MINTEMP = 22, MAXTEMP = 33;
            COLS = 30; // 30 , 28
            ROWS = 28; // 60, 56
          }
          boxsize = min(TFT_WIDTH / COLS, TFT_HEIGHT / ROWS);
        }

        tft.setTextPadding(75);
        tft.drawString("Max " + String(maxTempAMG, 1) + " C", 192, 240, 2);
        tft.drawString("Min " + String(minTempAMG, 1) + " C", 50, 240, 2);
        tft.setTextPadding(0);

        wifiPrint();

        FPS = millis() - millisElapsed;
        tft.setCursor(102, 225);
        tft.print(1000 / FPS); tft.print("fps ");
        tft.setCursor(106, 233);
        tft.print(everyX); tft.print("ms ");
      }
    } else {
      tft.setTextDatum(TC_DATUM);
      tft.setTextSize(1);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.drawString("Thermal Camera Offline", 120, 140, 2);
      drawBmp(SPIFFS, "/car/error.bmp", 105, 85);
      while (pageCount == 8) {
        SYSTEM();
        everyXsec();
        notiWarnings();
        wifiPrint();
        checkScreenState();
        readEnvironmentData();
        printStatusBar();
      }
    }
    Wire.beginTransmission(0x69);   //  AMG8833 Modes
    Wire.write(0x00);   // Register
    Wire.write(0x10);   // Value to Register 0x00 - Normal, 0x10 - Sleep, 0x20 - 60sec, 0x21 - 10sec
    if (Wire.endTransmission() != 0) activeAMG = false;
    MINTEMP = 22, MAXTEMP = 33;
    if (pageCount == 7 || pageCount == 9) pageCount = 0; menuCar = 4; page0();
  }
}

void page9() {     // MAX30105 HRO2 particle

  if (pageCount == 9) {
    tft.fillScreen(TFT_BLACK);
    if (activeMAX) {

      if (screenState) {
        tft.drawRoundRect(193, 17, 55, 12, 3, TFT_MIDDLEGREY); // (xO, yO, Length, Width, Radius, color)
        ledBon = false;
        MAX30105.wakeUp();
        if (loggingActive) appendFile(SD, LogFile, "\nHeartRate Measuring...  \n");
        m = 0;
        edgeL = 5;
        sleepTimer = 0;

        tft.drawRoundRect(edgeL, box1Top, boxWidth, boxHeight, 3, TFT_LIGHTGREY);
        tft.drawRoundRect(edgeL, box2Top, boxWidth, boxHeight, 3, TFT_LIGHTGREY);
        staticGraphGFX();

        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        drawBmp(SPIFFS, "/HR18.bmp", 15, 194);
        smlPRNT(String(beatAvg), "BPM", 0, 0);
        tft.setTextSize(1);
        tft.setCursor(185, box1Bottom + 4);
        tft.print(ledBrightness / 5.1); tft.print("mAh");
      }

      while (pageCount == 9) {
        millisElapsed = millis();

        //        if (everyXsecFlag) everyXsecFlag = false;
        if (millis() - count > 1000) {
          //          everyXsecFlag = true;
          count = millis();
          SYSTEM();
        }

        //      wifiPrint();
        //      readEnvironmentData();   // CCS811 Function

        if (screenState) {
          MAX30105.check();
          while (MAX30105.available()) {    //do we have new data
            red = MAX30105.getFIFOIR();     // swap inputs for MH-ET LIVE !! red=IR, IR=red
            ir = MAX30105.getFIFORed();     // getFIFORed output IR data by MAX30102 on MH-ET LIVE breakout board
            m++;
            fred = (double)red;
            fir = (double)ir;
            avered = avered * frate + (double)red * (1.0 - frate);   //average red level by low pass filter
            aveir = aveir * frate + (double)ir * (1.0 - frate);     //average IR level by low pass filter
            sumredrms += (fred - avered) * (fred - avered);         //square sum of alternate component of red level
            sumirrms += (fir - aveir) * (fir - aveir);              //square sum of alternate component of IR level
            if ((m % Num) == 0) {
              double R = (sqrt(sumredrms) / avered) / (sqrt(sumirrms) / aveir);
              SpO2 = -23.3 * (R - 0.4) + 100;                   //http://ww1.microchip.com/downloads/jp/AppNotes/00001525B_JP.pdf
              ESpO2 = FSpO2 * ESpO2 + (1.0 - FSpO2) * SpO2;     //low pass filter
              sumredrms = 0.0; sumirrms = 0.0; m = 0;
              break;
            }
            MAX30105.nextSample();                        //We're finished with this sample so move to next sample
          }

          irValue = MAX30105.getIR();
          if (checkForBeat(irValue)) {  // we sensed a Beat!
            if (!silentMode) tone(beepPin, 600, 2);
            smlPRNT(String(beatAvg), "BPM", 0, 0);

            delta = millis() - lastBeat;
            lastBeat = millis();
            beatsPerMinute = 60 / (delta / 1000.0);

            if (beatsPerMinute < 200 && beatsPerMinute > 30) // 255, 30
            {
              rates[rateSpot++] = (byte)beatsPerMinute; // Store this reading in the array
              rateSpot %= RATE_SIZE; // Wrap variable

              beatAvg = 0;           // Take average of readings
              for (byte x = 0 ; x < RATE_SIZE ; x++) {
                beatAvg += rates[x];
                beatAvg /= RATE_SIZE;
              }
            }
          }
          irValue = irValue  / 10;

          tft.setTextDatum(TL_DATUM);
          tft.setTextPadding(30);
          tft.drawNumber(irValue, 55, box1Bottom + 4, 1);
          tft.drawNumber(irOffset, 100, box1Bottom + 4, 1);
          tft.drawFloat(ESpO2, 2, 8, box2Bottom + 4, 1);

          // unadjusted graph
          //   tft.drawPixel(edgeL + 1, map(constrain(irValue, ledBrightness * constHRbottom, ledBrightness * constHRtop), ledBrightness * constHRbottom, ledBrightness * constHRtop, box1Bottom - 1, box1Top + 2) - 1, TFT_MIDDLEGREEN); // 780 , 1000

          if (irValue > constHRtop * ledBrightness) { // adjust graph in case its out of bounds
            irValue -= 720; //  720
          }
          if (irValue < constHRbottom * ledBrightness) {
            irValue += 720; //  720
          }
          tft.drawPixel(edgeL + 1, map(constrain(irValue, ledBrightness * constHRbottom, ledBrightness * constHRtop), ledBrightness * constHRbottom, ledBrightness * constHRtop, box1Bottom - 1, box1Top + 2) - 1, TFT_GREEN);
          //        tft.drawLine(edgeL + 1, map(constrain(irValue, ledBrightness * constHRbottom, ledBrightness * constHRtop), ledBrightness * constHRbottom, ledBrightness * constHRtop, box1Bottom - 1, box1Top + 2) - 1, edgeL + 1, map(constrain(lastIR, ledBrightness * constHRbottom, ledBrightness * constHRtop), ledBrightness * constHRbottom, ledBrightness * constHRtop, box1Bottom - 1, box1Top + 2) - 1, TFT_GREEN); // 780 , 1000
          //        lastIR = irValue;

          tft.setTextColor(TFT_WHITE, TFT_BLACK);
          tft.drawNumber(irValue, 8, box1Bottom + 4, 1);
          tft.setTextSize(3);
          tft.setTextPadding(40);
          tft.drawNumber(beatAvg, 10, 78, 1);

          //      tft.drawPixel(edgeL + 1, map(ESpO2, 85, 105, box2Bottom, box2Top - 1) , TFT_BLUE);
          tft.drawLine(edgeL + 1, map(constrain(ESpO2 * 10, 700, 1000), 700, 1020, box2Bottom - 1, box2Top + 1) , edgeL + 1, map(constrain(lastO2 * 10, 700, 1000), 700, 1020, box2Bottom - 1, box2Top + 1), TFT_BLUE);
          lastO2 = ESpO2;
          edgeL++;

          if (edgeL > 229) {
            edgeL = 5;
            tft.fillRoundRect(edgeL + 1, box1Top + 1, boxWidth - 2, boxHeight - 2, 3, TFT_BLACK);
            tft.fillRoundRect(edgeL + 1, box2Top + 1, boxWidth - 2, boxHeight - 2, 3, TFT_BLACK);
            staticGraphGFX();
            //                    drawBmp(SPIFFS, "/HR18.bmp", 15, 194);
          }

          tft.setTextSize(1);
          tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
          tft.setCursor(200, 19);
          FPS = millis() - millisElapsed;
          tft.print(FPS); tft.print("ms ");
        }
      }
    } else {
      tft.setTextDatum(TC_DATUM);
      tft.setTextSize(1);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      drawBmp(SPIFFS, "/car/error.bmp", 105, 85);
      tft.drawString("HeartRate Sensor Offline", 120, 140, 2);
      while (pageCount == 9) {
        SYSTEM();
        everyXsec();
        notiWarnings();
        wifiPrint();
        checkScreenState();
        readEnvironmentData();   // CCS811 Function
        printStatusBar();
      }
    }
    MAX30105.shutDown();
    u8g2.clearBuffer();
    ledBon = false;
    if (pageCount == 8) pageCount = 0; menuCar = 5; page0();
  }
}


void staticGraphGFX() {

  edgeL = 6;
  tft.drawFastHLine(edgeL, 95 , l, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, 85 , l, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, 75 , l, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, 65 , l, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, 55 , l, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, 45 , l, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, 35 , l, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, 25 , l, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, 15 , l, TFT_DARKGREY);

  tft.drawFastHLine(edgeL, 210, l, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, 200, l, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, 190, l, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, 180, l, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, 170, l, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, 160, l, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, 150, l, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, 140, l, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, 130, l, TFT_DARKGREY);

  edgeL = 5;
  if (pageCount == 4) {
    tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
    tft.setTextSize(1);
    tft.setCursor(edgeL, box1Bottom + 4);
    tft.print("CO2");
    tft.print("         ");
    tft.print("tVOC         ");
    tft.print(" T   ");
    tft.print("* ");
    tft.print("RH   ");
    tft.print("% ");

    tft.setCursor(edgeL, box2Bottom + 4);
    tft.print("Voltage");
    tft.print("       ");
    tft.print("Amps");
  }
}

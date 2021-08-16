#include <pgmspace.h>

void everyXsec() {

  if (everyXsecFlag) everyXsecFlag = false;     // Code that runs every X ms - 1 SEC
  if (millisElapsed - previousMs > everyXms) {
    previousMs = millis();
    everyXsecFlag = true;

    Logging();
    readUV();  // VEML6075 Combined UV-A, UV-B Readings
    Time(timeinfo); // update Time

    WiFiRSSI = WiFi.RSSI();
    CCS811err = myCCS811.checkForStatusError();


    if (deepSleepActive) {
      gotoDeepSleep();
    }

    if (Amps < -0.02) {        // is device Charging
      chargingActive = true;
    } else {
      chargingActive = false;
    }

    if (SOC < 15 || lowPowerMode) {
      bklTimeout =   6;       // TFT Backlight Off timer in Sec
    } else {
      bklTimeout =   30;       // TFT Backlight Off timer in Sec
    }

    DTdevicecount = sensors.getDeviceCount();
    t1 = sensors.getTempC(tempProbe1);
    t2 = sensors.getTempC(tempProbe2);
    t3 = sensors.getTempC(tempProbe3);
    t4 = sensors.getTempC(tempProbe4);
    t5 = sensors.getTempC(tempProbe5);
    t6 = sensors.getTempC(tempProbe6);
    t7 = sensors.getTempC(tempProbe7);
    t8 = sensors.getTempC(tempProbe8);
    ta1 = sensors.hasAlarm(tempProbe1);
    ta2 = sensors.hasAlarm(tempProbe2);
    ta3 = sensors.hasAlarm(tempProbe3);
    ta4 = sensors.hasAlarm(tempProbe4);
    ta5 = sensors.hasAlarm(tempProbe5);
    ta6 = sensors.hasAlarm(tempProbe6);
    ta7 = sensors.hasAlarm(tempProbe7);
    ta8 = sensors.hasAlarm(tempProbe8);
    sensors.requestTemperatures();

    if (fanActive) {
      mySensVals[0] = t1;
      mySensVals[1] = t2;
      mySensVals[2] = t3;
      mySensVals[3] = t4;
      mySensVals[4] = t5;
      mySensVals[5] = t6;
      mySensVals[6] = t7;
      mySensVals[7] = t8;

      max_probe_temp = mySensVals[7];
      for (idx = 1; idx < 7; idx++) {
        if (mySensVals[idx] > max_probe_temp); max_probe_temp = mySensVals[idx]; // find biggest value
      }
      switch ( idx ) {
        case 1: max_probe_idx = "Ambient LED"; break;
        case 2: max_probe_idx = "Battery 1"; break;
        case 3: max_probe_idx = "LED"; break;
        case 4: max_probe_idx = "ESP32"; break;
        case 5: max_probe_idx = "Power Mgmt 1"; break;
        case 6: max_probe_idx = "Power Mgmt 2"; break;
        case 7: max_probe_idx = "Battery 2"; break;
        case 8: max_probe_idx = "Power Bus"; break;
      }
      high_temp_message = max_probe_idx + " is at " + max_probe_temp + " C";
    }


    if (loggingActive) {
      tempProbes = "";
      tempProbes += String(t1) + ", ";
      tempProbes += String(t2) + ", ";
      tempProbes += String(t3) + ", ";
      tempProbes += String(t4) + ", ";
      tempProbes += String(t5) + ", ";
      tempProbes += String(t6) + ", ";
      tempProbes += String(t7) + ", ";
      tempProbes += String(t8) + ", ";
    }

    if (tempAlarm || powerAlarm) {
      smlICON("C");    // "C"
    } else if (chargingActive) {
      smlCHRG();
    } else {
      switch ( pageCount ) {
        case 0:  smlCarousel(); break;
        case 1:  smlCarousel(); break; // smlICON("L"); break; // "L" settings icon
        case 2:  smlICON("B"); break; // SD icon
        case 3:  break; // is being handled by the page
        case 4:  smlPRNT2(String(co2SCD),  String(co2SMPL), 0, 0); break;
        case 5:  smlCarousel(); break;
        case 6:  smlPRNT(String(co2SCD),  "CO2", 0, 0); break; // "B"
        case 7:  smlPRNT(String(tvocCCS), "VOC", 0, 0); break;
        case 8:  break; // is being handled by the page
        case 9:  smlPRNT(String(beatAvg), "bpm", 0, 0); break;
      }
    }
    everyX = millis() - previousMs;
  }
}

void smlCarousel() {
  switch ( count ) {
    case 0 ... 2: smlPRNT2(String(hr) + ":" + String(mi), String(RTCd), -17, -10); break;
    case 3:       smlPRNT(String(SOC) + "%", "BATTERY", -8, -20); break;
    case 4:       smlPRNT(String(tempSCD, 0),  "TEMP", 3, -1); break;
    case 5:       smlPRNT(String(UVI),         "UV INDEX", 0, -32); break;
    case 6:       smlPRNT(String(AirQI),       "AirQI", 16, -7); break;     // smlPRNT(String(steps), "STEPS", 16, -8); break;
    case 7:       smlPRNT2(String(co2SCD),     String(co2CCS), -9, 2); count = 0; break;
      //    default: count = 0; break;
  }
  count++;
}

/*
   smlCarousel();
   smlPRNT2(String(Volts), String(Amps), 0);
   smlPRNT(String(beatAvg), "bpm", 0);
   smlPRNT2(String(co2SCD, 0), String(co2SMPL), 0);
   smlPRNT(String(co2SCD, 0), "CO2", 0);
   smlPRNT(String(tvocCCS), "VOC", 0);
*/

void checkforAlarms() {

  millisElapsed = millis();

  Warnings();     // updating Warnings & triggering Alarms
  //   readIMU();      // MPU9250 IMU Readings and Step Counter

  if (alarmEnable && powerAlarm || tempAlarm) {
    cycleCount = 0;
    tft.fillScreen(TFT_BLACK);
    tft.setTextPadding(152);
    MAX30105.shutDown();

    TFTon();

    tft.fillRoundRect(40, 30, 160, 180, 12, TFT_DARKGREY);
    tft.drawRoundRect(43, 33, 154, 174, 12, TFT_WHITE);

    while (alarmEnable && powerAlarm || tempAlarm) {
      millisElapsed = millis();
      everyXsec();
      Warnings();
      readEnvironmentData();
      printStatusBar();
      panicLog();
      TFTon();

      cycleCount++;
      if (cycleCount > 100) gotoDeepSleep();      // simulate powerOFF while critical alarm

      if (cycleCount % 3 == 0) {
        tft.fillCircle(TFT_WIDTH - 20, TFT_HEIGHT - 105, 10, TFT_BLACK);
        tft.fillCircle(TFT_WIDTH - 20, TFT_HEIGHT - 75, 10, TFT_RED);
        tft.fillCircle(TFT_WIDTH - 20, TFT_HEIGHT - 45, 10, TFT_BLACK);
        ledB = 200;
        ledcWrite(1, ledB);
        tone(beepPin, 2600, 300);
      } else {
        tft.fillCircle(TFT_WIDTH - 20, TFT_HEIGHT - 105, 10, TFT_RED);
        tft.fillCircle(TFT_WIDTH - 20, TFT_HEIGHT - 75, 10, TFT_BLACK);
        tft.fillCircle(TFT_WIDTH - 20, TFT_HEIGHT - 45, 10, TFT_RED);
        tone(beepPin, 2900, 300);
        if (ledB > 10) ledB -= 10;
      }

      tft.setTextDatum(MC_DATUM);
      tft.setTextSize(1);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.drawNumber(100 - cycleCount, TFT_WIDTH - 20, TFT_HEIGHT - 10, 4);
      tft.setTextColor(TFT_WHITE, TFT_DARKGREY);

      if (tempAlarm) {                             // High Temp Alarm Display
        tft.setTextColor(TFT_RED, TFT_DARKGREY);
        if (!silentMode) tone(beepPin, 2640, 70);
        tft.drawString("TEMP ALARM", TFT_WIDTH / 2, 45, 2);
      } else {
        tft.drawString("TEMP OK", TFT_WIDTH / 2, 45, 2);
      }

      tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
      if (powerAlarm) {
        tft.setTextColor(TFT_RED, TFT_DARKGREY);
        if (!silentMode) tone(beepPin, 2340, 70);
        tft.drawString("VOLTAGE ALARM", TFT_WIDTH / 2, 65, 2);
      } else {
        tft.drawString("VOLTAGE OK", TFT_WIDTH / 2, 65, 2);
      }
      tft.drawString(String(Volts), TFT_WIDTH / 2, 100, 7);

      tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
      if (Amps > ampsFanTH) {
        tft.setTextColor(TFT_RED, TFT_DARKGREY);
        if (!silentMode) tone(beepPin, 2000, 70);
        tft.drawString("CURRENT ALARM", TFT_WIDTH / 2, 190, 2);
      } else {
        tft.drawString("CURRENT OK", TFT_WIDTH / 2, 190, 2);
      }
      tft.drawString(String(Amps), TFT_WIDTH / 2, 155, 7);

      tft.setCursor(0, 63);
      tft.setTextSize(2);
      printTemperature(tempProbe1); tft.println(" ");
      printTemperature(tempProbe2); tft.println(" ");
      printTemperature(tempProbe3); tft.println(" ");
      printTemperature(tempProbe4); tft.println(" ");
      printTemperature(tempProbe5); tft.println(" ");
      printTemperature(tempProbe6); tft.println(" ");
      printTemperature(tempProbe7); tft.println(" ");
      printTemperature(tempProbe8); tft.println(" ");

      tft.setTextSize(1);
      tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
      tft.setCursor(197, 25);
      tft.drawRoundRect(193, 23, 55, 12, 3, TFT_MIDDLEGREY); // (xO, yO, Length, Width, Radius, color)
      FPS = millis() - millisElapsed;
      tft.print(1000 / FPS); tft.print("fps ");
    }
    tft.fillScreen(TFT_BLACK);
    cycleCount = 0;
    switch ( pageCount ) {
      case 0: page0();
      case 1: page1();
      case 2: page2();
      case 3: page3();
      case 4: page4();
      case 5: page5();
      case 6: page6();
      case 7: page7();
      case 8: page8();
      case 9: page9();
    }
  }
}

void Warnings() {

  readSystemPower();

  if (t1 > tA1 || t2 > tA2 || t3 > tA3 || t4 > tA4 || t5 > tA5 || t6 > tA6 || t7 > tA7 || t8 > tA8 ||
      Amps > ampsFanTH ||     // Fan Activation when Temp Warning or CurrentTH
      chargingActive ||
      tempBME > 45 ||
      tempSCD > 45) {
    fanActive = true;
    digitalWrite(fan, HIGH);
  } else {
    fanActive = false;
    digitalWrite(fan, LOW);
  }

  if (humidSCD > 95 || dewPoint > 50) {
    wetAlarm = true;
  } else {
    wetAlarm = false;
  }

  if (ta1 || ta2 || ta3 || ta4 || ta5 || ta6 || ta7 || ta8) {  // critical temp alarms
    tempAlarm = true;
  } else {
    tempAlarm = false;
  }

  if (Volts < lowVoltAlarm || Volts > highVoltAlarm || Amps > 8 && Amps < 15) {  //   Critical Temp & overCurrent Alarm Enable
    powerAlarm = true;
  } else {
    powerAlarm = false;
  }

  if (AirQI > 3) {     //   Critical Air Quality
    airWarning = true;
  } else {
    airWarning = false;
  }

  if (ledBon) {  // if you want to trigger ledB fade on, set ledB = 250
    if (ledB < ledBmax) {
      ledB += 15;
      if (ledB > ledBmax - 20) ledB = ledBmax;
      ledcWrite(1, ledB);
    }
  }

  if (!ledBon) {  // if you want to trigger ledB fade off, set ledB = 1
    if (ledB > 0) {
      ledB -= 15;
      if (ledB < 15) ledB = 0;
      ledcWrite(1, ledB);
    }
  }
}

void notification(String line1, String line2, bool notiFlag, byte alarmType, long int tS) {

  if (notiFlag) {
    tft.setTextDatum(TL_DATUM);
    tft.setTextPadding(180);
    tft.setTextSize(1);
    TFTon();

    if (notiY <= 19 && millisElapsed - tS < 3000) {
      notiY = notiY + 4;
      tft.fillRoundRect(10, notiY - 4, 220, 10, 8, TFT_BLACK);
      tft.fillRoundRect(10, notiY, 220, 60, 8, TFT_DARKGREY);
      tft.setTextColor(TFT_WHITE);
      tft.drawString(line1, 20, notiY + 22, 4);
      tft.drawString(line2, 20, notiY + 38, 4);
      switch ( alarmType ) {
        case 0: drawBmp(SPIFFS, "/inactive12.bmp", 18, notiY + 7); break;
        case 1: drawBmp(SPIFFS, "/warnRoundW12.bmp", 19, notiY + 6); break;
        case 2: drawBmp(SPIFFS, "/warnRoundY12.bmp", 19, notiY + 6); break;
        case 3: drawBmp(SPIFFS, "/warnRoundR12.bmp", 19, notiY + 6); break;
      }
    } else if (notiY == 20 && millisElapsed - tS < 3000) {
      tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
      tft.drawString(line1, 20, notiY + 22, 4);
      tft.drawString(line2, 20, notiY + 38, 4);
      switch ( alarmType ) {
        case 0: drawBmp(SPIFFS, "/inactive12.bmp", 18, notiY + 7); break;
        case 1: drawBmp(SPIFFS, "/warnRoundW12.bmp", 19, notiY + 6); break;
        case 2: drawBmp(SPIFFS, "/warnRoundY12.bmp", 19, notiY + 6); break;
        case 3: drawBmp(SPIFFS, "/warnRoundR12.bmp", 19, notiY + 6); break;
      }
    } else if (millisElapsed - tS > 3000) {
      if (notiY >= -60) {
        notiY = notiY - 4;
        tft.fillRoundRect(10, notiY + 50, 220, 20, 8, TFT_BLACK);
        tft.fillRoundRect(10, notiY, 220, 60, 8, TFT_DARKGREY);
        tft.setTextColor(TFT_WHITE);
        tft.drawString(line1, 20, notiY + 22, 4);
        tft.drawString(line2, 20, notiY + 38, 4);
        switch ( alarmType ) {
          case 0: drawBmp(SPIFFS, "/inactive12.bmp", 18, notiY + 7); break;
          case 1: drawBmp(SPIFFS, "/warnRoundW12.bmp", 19, notiY + 6); break;
          case 2: drawBmp(SPIFFS, "/warnRoundY12.bmp", 19, notiY + 6); break;
          case 3: drawBmp(SPIFFS, "/warnRoundR12.bmp", 19, notiY + 6); break;
        }

        if (notiY <= -60) {
          if (nFanFlag) nFanFlag = false;
          if (nAirFlag) nAirFlag = false;
          if (nTempFlag) nTempFlag = false;
          if (nLedFlag) nLedFlag = false;
          if (nWetFlag) nWetFlag = false;
          notiOn = false;

          switch ( pageCount ) {
            case 0: page0();
            case 1: page1();
            case 2: page2();
            case 3: page3();
            case 4: page4();
            case 5: page5();
            case 6: page6();
            case 7: page7();
            case 8: page8();
            case 9: page9();
          }
        }
      }
    }
  }
}

void notiWarnings() {

  if (fanActive && millisElapsed - notiTimestampF > 60010) { // Rising Edge
    notiTimestampF = millisElapsed;
    tone(beepPin, 1400, 3);
    nFanFlag = true;
  }

  if (airWarning && millisElapsed - notiTimestampA > 20010) {
    notiTimestampA = millisElapsed;
    tone(beepPin, 1400, 3);
    nAirFlag = true;
  }

  //  if (tempAlarm && millisElapsed - notiTimestampT > 20010) {
  //    notiTimestampT = millisElapsed;
  //    tone(beepPin, 1400, 3);
  //    nTempFlag = true;
  //  }

  if (ledBon && millisElapsed - notiTimestampL > 60010) {
    notiTimestampL = millisElapsed;
    tone(beepPin, 1400, 3);
    nLedFlag = true;
  }

  if (wetAlarm && millisElapsed - notiTimestampW > 10010) {
    notiTimestampW = millisElapsed;
    tone(beepPin, 1400, 3);
    nWetFlag = true;
  }

  if (nFanFlag || nAirFlag || nTempFlag || nLedFlag || nWetFlag) {
    notiOn = true;
  }

  notification("High Temperature Detected", high_temp_message, nFanFlag, 1, notiTimestampF);
  notification("Air Quality Warning", "Index: " + String(AirQI), nAirFlag, 2, notiTimestampA);
  notification("LED is at " + String(map(ledB, 0, 255, 0, 100)) + "% ", "LED Temp: " + String(t3) + " C", nLedFlag, 0, notiTimestampL);
  notification("Water Ingress Detected", "SHUT OFF device immediately!!!", nWetFlag, 3, notiTimestampW);
  //  notification("Temperature", "", nTempFlag, 3, notiTimestampT);
}



void smlPRNT(String sensor, const char* text, int x, int x2) { // sml print data
  u8g2.clearBuffer();     // clear the internal memory
  sensor.toCharArray(charArr, 9);

  u8g2.setFont(u8g2_font_logisoso20_tf);
  u8g2.drawStr((u8g2.getStrWidth(charArr) / 2) + 32 + x, 24, charArr);

  u8g2.setFont(u8g2_font_chroma48medium8_8r); // choose a suitable font
  u8g2.drawStr((u8g2.getStrWidth(text) / 2) + 32 + x2, 32, text); // write something to the internal memory

  u8g2.sendBuffer();     // transfer internal memory to the display
}

void smlPRNT2(String val1, String val2, int x, int x2) {
  u8g2.clearBuffer();     // clear the internal memory
  val1.toCharArray(charArr, 9);
  u8g2.setFont(u8g2_font_logisoso18_tn);
  u8g2.drawStr((u8g2.getUTF8Width(charArr) / 2) + 32 + x, 20, charArr); // write something to the internal memory

  val2.toCharArray(charArr, 9);
  u8g2.setFont(u8g2_font_helvR10_tn);
  u8g2.drawStr((u8g2.getUTF8Width(charArr) / 2) + 32 + x2, 32, charArr); // write something to the internal memory

  u8g2.sendBuffer();     // transfer internal memory to the display
}


void smlCHRG() {
  //  tft.drawNumber(count, 20, 50, 2);
  u8g2.clearBuffer();     // clear the internal memory
  u8g2.setFont(u8g2_font_battery19_tn); // 8 x 19

  if (count == 1) {
    u8g2.drawStr(37, 6, "0"); count++;
  } else if (count == 2) {
    u8g2.drawStr(37, 6, "1"); count++;
  } else if (count == 3) {
    u8g2.drawStr(37, 6, "2"); count++;
  } else if (count == 4) {
    u8g2.drawStr(37, 6, "3"); count++;
  } else if (count == 5) {
    u8g2.drawStr(37, 6, "4"); count++;
  } else if (count >= 6) {
    u8g2.drawStr(37, 6, "5");
    switch (SOC) {
      case 0 ... 20:   count = 1; break;
      case 21 ... 40:  count = 2; break;
      case 41 ... 60:  count = 3; break;
      case 61 ... 80:  count = 4; break;
      case 81 ... 100: count = 5; break;
    }
  }
  u8g2.sendBuffer();
}

void smlICON(const char *message) {
  u8g2.clearBuffer();     // clear the internal memory

  u8g2.setFont(u8g2_font_open_iconic_embedded_4x_t);
  u8g2.drawStr(u8g2.getUTF8Width(message) / 2 + 32, 0, message);

  u8g2.sendBuffer();
}

void gotoDeepSleep() {
  putPersistentBool("loggingActive", loggingActive);

  Wire.beginTransmission(0x69);   //  AMG8833 Modes   0x00 - Normal, 0x10 - Sleep, 0x20 - 60sec, 0x21 - 10sec
  Wire.write(0x00);   // Register
  Wire.write(0x10);   // Value to Register
  Wire.endTransmission();

  ledcWrite(1, 0);
  TFToff();
  u8g2.clearBuffer();
  u8g2.sleepOn();

  ina260.setAveragingCount(INA260_COUNT_128); // 128 * 8.2ms = 1.05sec
  ina260.setVoltageConversionTime(INA260_TIME_8_244_ms); // 140_us, 204_us, 332_us, 558_us, 1_1_ms,
  ina260.setCurrentConversionTime(INA260_TIME_8_244_ms);
  //  ina260.setMode(INA260_MODE_SHUTDOWN);
  myCCS811.setDriveMode(0); // IDLE
  scd30.StopMeasurement();
  MAX30105.shutDown();
  myBME280.setMode(0);
  VML.shutdown();
  //  rtc_gpio_init(GPIO_NUM_17); //initialize the RTC GPIO port
  //  rtc_gpio_init(GPIO_NUM_27); //initialize the RTC GPIO port
  //  rtc_gpio_init(GPIO_NUM_26); //initialize the RTC GPIO port
  //  rtc_gpio_hold_dis(GPIO_NUM_17); //disable hold before setting the level
  //  rtc_gpio_hold_dis(GPIO_NUM_27); //disable hold before setting the level
  //  rtc_gpio_hold_dis(GPIO_NUM_26); // disable hold before setting the level
  //  rtc_gpio_set_level(GPIO_NUM_17, LOW); //set high/low
  //  rtc_gpio_set_level(GPIO_NUM_26, HIGH); //set high/low
  //  rtc_gpio_set_level(GPIO_NUM_27, HIGH); //set high/low
  //  rtc_gpio_set_direction(GPIO_NUM_17, RTC_GPIO_MODE_INPUT_ONLY);
  //  rtc_gpio_set_direction(GPIO_NUM_27, RTC_GPIO_MODE_INPUT_ONLY);
  //  rtc_gpio_set_direction(GPIO_NUM_26, RTC_GPIO_MODE_INPUT_ONLY);

  rtc_gpio_hold_en(GPIO_NUM_17); // led
  rtc_gpio_hold_en(GPIO_NUM_27); // tftBLK
  rtc_gpio_hold_en(GPIO_NUM_26); // fan
  //  gpio_deep_sleep_hold_en();
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  btStop();
  esp_bt_controller_disable();
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_2, 1); // 1 = High, 0 = Low, 2,4,35
  //  if (powerAlarm) sleepWakeupTime += (3600 * uS_TO_S_FACTOR);
  esp_sleep_enable_timer_wakeup(sleepWakeupTime * uS_TO_S_FACTOR);
  esp_deep_sleep_start();
}

void TFToff() {
  screenState = 0;
  checkScreenState();
}

void TFTon() {
  lastWake = millisElapsed;
  screenState = 1;
  checkScreenState();
}

void checkScreenState() {

  sleepTimer = (millisElapsed - lastWake) / 1000;
  if (sleepTimer > bklTimeout) screenState = 0;

  if (screenState) {
    if (tftBKL < tftBKLmax) {
      tftBKL += 8;
      if (tftBKL > tftBKLmax - 10) tftBKL = tftBKLmax;
      analogWrite(tftPIN, tftBKLmax);
    }
  } else if (tftBKL > 1) {
    tftBKL -= 6;
    if (tftBKL < 12) tftBKL = 0;
    analogWrite(tftPIN, tftBKL);
  }
}


void printStatusBar() {

  drawBmp(SPIFFS, "/batLine.bmp", batX, 2);

  if (chargingActive) {
    TFT_BATCOLOR = TFT_GREEN;
  } else if (lowPowerMode) {
    TFT_BATCOLOR = TFT_YELLOW;
  } else {
    TFT_BATCOLOR = TFT_WHITE;
  }

  if (SOC > 90) {
    tft.fillRect(batX + 1, 7, 9, 2, TFT_BATCOLOR);
  } else if (SOC < 90 && SOC > 80) {
    tft.fillRect(batX + 1, 6, 8, 4, TFT_BATCOLOR);
  } else if (SOC < 80 && SOC > 70) {
    tft.fillRect(batX + 1, 6, 7, 4, TFT_BATCOLOR);
  } else if (SOC < 70 && SOC > 60) {
    tft.fillRect(batX + 1, 6, 6, 4, TFT_BATCOLOR);
  } else if (SOC < 60 && SOC > 50) {
    tft.fillRect(batX + 1, 6, 5, 4, TFT_BATCOLOR);
  } else if (SOC < 50 && SOC > 40) {
    tft.fillRect(batX + 1, 6, 4, 4, TFT_BATCOLOR);
  } else if (SOC < 40 && SOC > 30) {
    tft.fillRect(batX + 1, 6, 3, 4, TFT_BATCOLOR);
  } else if (SOC < 30 && SOC > 20) {
    tft.fillRect(batX + 1, 6, 2, 4, TFT_BATCOLOR);
  } else if (SOC < 20 && SOC > 10) {
    if (!chargingActive) TFT_BATCOLOR = TFT_ORANGE;
    tft.fillRect(batX + 1, 6, 2, 4, TFT_BATCOLOR);
  } else if (SOC < 10 && SOC > 0) {
    if (!chargingActive) TFT_BATCOLOR = TFT_RED;
    tft.fillRect(batX + 1, 6, 1, 4, TFT_BATCOLOR);
  }

  if (pageCount == 3) { // print minElapsed & Lamp Icon
    tft.setTextColor(TFT_CYAN, TFT_BLACK);
    tft.setTextPadding(30);
    tft.setTextSize(1);
    tft.setTextDatum(BL_DATUM);
    tft.drawString(String(minElapsed) + "min", 0, TFT_HEIGHT, 2);
  }

  if (WiFistatus == 3) {
    if (WiFiRSSI > -60) {
      tft.pushImage(wifiX, 2, 12, 12, Wifi12);
    } else if (WiFiRSSI < -60 && WiFiRSSI > -80)   {
      tft.pushImage(wifiX, 2, 12, 12, WifiLow12);
    } else {
      tft.pushImage(wifiX, 2, 12, 12, WifiLower12);
    }
  } else if (WiFistatus == 6 || WiFistatus == 255) {
    tft.pushImage(wifiX, 2, 12, 12, WifiOff12);
  } else if (WiFistatus == 0) {
    if (WiFiRSSI > -60) {
      tft.pushImage(wifiX, 2, 12, 12, Wifi12);
    } else if (WiFiRSSI < -60 && WiFiRSSI > -80)   {
      tft.pushImage(wifiX, 2, 12, 12, WifiLow12);
    } else {
      tft.pushImage(wifiX, 2, 12, 12, WifiLower12);
    }
  } else {
    tft.pushImage(wifiX, 2, 12, 12, WifiIdle12);
  }

  if (silentMode) {
    drawBmp(SPIFFS, "/soundOff12.bmp", 2, 2);
    //    tft.pushImage(60, 2, 12, 12, sleep12);
    //    if (SDpresent) drawBmp("/UI/sleep12.bmp", 60, 2);   // 24bit
  } else {
    drawBmp(SPIFFS, "/soundOn12.bmp", 2, 2);
    //    tft.fillRect(60, 2, 12, 12, TFT_BLACK);
  }

  if (SDpresent) {
    drawBmp(SPIFFS, "/sd12.bmp", 20, 2);
    //    tft.pushImage(3, 2, 12, 12, sd13);
  } else {
    tft.fillRect(20, 2, 12, 12, TFT_BLACK);
  }

  if (loggingActive) {
    drawBmp(SPIFFS, "/logging12.bmp", 38, 2);
    //    tft.pushImage(23, 2, 12, 12, logging12);
    //    if (SDpresent) drawBmp("/UI/logging12.bmp", 24, 2);   // 24bit
  } else {
    tft.fillRect(38, 2, 12, 12, TFT_BLACK);
  }

  if (fanActive) {
    drawBmp(SPIFFS, "/fan12.bmp", 56, 2);
    //    tft.pushImage(44, 2, 12, 12, fan12);
    //    if (SDpresent) drawBmp("/UI/fan12.bmp", 44, 2);   // 24bit
  } else {
    tft.fillRect(56, 2, 12, 12, TFT_BLACK);
  }

  if (deepSleepActive) {
    drawBmp(SPIFFS, "/sleep12.bmp", 75, 2);
    //    tft.pushImage(60, 2, 12, 12, sleep12);
    //    if (SDpresent) drawBmp("/UI/sleep12.bmp", 60, 2);   // 24bit
  } else {
    tft.fillRect(75, 2, 12, 12, TFT_BLACK);
  }

  if (pageCount == 5) {
    if (airWarning) {
      drawBmp(SPIFFS, "/warnRoundR12.bmp", 197, 115);
      //    tft.pushImage(3, 22, 12, 12, warn12);
      //    if (SDpresent) drawBmp(SD, "/UI/warn12.bmp", 3, 22);
    } else {
      tft.fillRect(197, 115, 12, 12, TFT_BLACK);
    }

    if (uvWarning) {
      drawBmp(SPIFFS, "/warnRoundY12.bmp", 33, 115);
      //    tft.pushImage(3, 22, 12, 12, warn12);
      //    if (SDpresent) drawBmp(SD, "/UI/warn12.bmp", 3, 22);
    } else {
      tft.fillRect(33, 115, 12, 12, TFT_BLACK);
    }

    if (ledBon) {
      drawBmp(SPIFFS, "/lampon.bmp", 111, 147);
    } else if (!ledBon && pageCount == 5) {
      drawBmp(SPIFFS, "/lamp.bmp", 111, 147);
    }
  }
}

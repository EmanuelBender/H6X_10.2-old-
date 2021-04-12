#include <pgmspace.h>

void checkforAlarms() {

  Alarms(); // <-- actually checking here for critical alarms

  currentTime = millis();
  minElapsed = currentTime / 1000 / 60; // time elapsed since boot in min

  if (criticalAlarm) {
    tftBKL = 255;
    analogWrite(tftPIN, tftBKL);
    sleepTimer = 0;
    cycleCount = 0;

    tft.setTextDatum(MC_DATUM);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
    tft.setTextPadding(50);
    //tft.fillScreen(TFT_BLACK);
    tft.fillRoundRect(40, 30, 160, 180, 5, TFT_DARKGREY);
    tft.drawRoundRect(43, 33, 154, 174, 5, TFT_WHITE);

    while (criticalAlarm) {
      currentTime = millis();
      wifiPrint();
      printStatusBar();
      Alarms();
      cycleCount++;
      everyXsec();
      tft.setTextDatum(MC_DATUM);
      tft.setTextSize(1);
      tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
      if ( t1 > criticalTemp ||
           t2 > criticalTemp ||
           t3 > criticalTemp ||
           t4 > criticalTemp ||
           t5 > criticalTemp ||
           t6 > criticalTemp ||
           t7 > criticalTemp) {
        tft.setTextColor(TFT_RED, TFT_DARKGREY);
        //tone(beep, 2640, 70);
        tft.drawString("HIGH TEMP", 120, 45, 2);
      } else {
        tft.drawString("TEMP OK", 120, 45, 2);
      }

      tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
      if (Volts < 6 || BatPercent > 100) {
        tft.setTextColor(TFT_RED, TFT_DARKGREY);
        //tone(beep, 2340, 70);
        tft.drawString("VOLTAGE ALARM", 120, 65, 2);
      } else {
        tft.drawString("VOLTAGE OK", 120, 65, 2);
      }
      tft.drawString(String(Volts), 120, 100, 7);


      tft.setTextColor(TFT_GOLD, TFT_DARKGREY);
      if (Amps > currentTH) {
        tft.setTextColor(TFT_RED, TFT_DARKGREY);
        //tone(beep, 2000, 70);
        tft.drawString("CURRENT ALARM", 120, 190, 2);
      } else {
        tft.drawString("CURRENT OK", 120, 190, 2);
      }
      tft.drawString(String(Amps), 120, 155, 7);

      /*
            tft.setCursor(0, 195);
            tft.setTextSize(2);
              printTemperature(tempProbe1); tft.print(" ");
              printTemperature(tempProbe2); tft.print(" ");
              printTemperature(tempProbe3); tft.println();
              printTemperature(tempProbe4); tft.print(" ");
              printTemperature(tempProbe5); tft.print(" ");
              printTemperature(tempProbe6); tft.print(" ");
              printTemperature(tempProbe7);
      */
      /*
        if (cycleCount > 550) {                 // simulate powerOFF
        analogWrite(tftPIN, 0);
        // digitalWrite(fan, LOW);
        // digitalWrite(powerOFF, LOW);    // EN pin for buck converter
        //esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);
        rtc_gpio_set_direction(GPIO_NUM_19, RTC_GPIO_MODE_OUTPUT_ONLY);
        rtc_gpio_set_direction(GPIO_NUM_26, RTC_GPIO_MODE_OUTPUT_ONLY);
        rtc_gpio_set_direction(GPIO_NUM_27, RTC_GPIO_MODE_OUTPUT_ONLY);
        esp_sleep_enable_ext0_wakeup(GPIO_NUM_2, 1); // 1 = High, 0 = Low, 2,4,35
        esp_sleep_enable_ext0_wakeup(GPIO_NUM_4, 1);
        esp_sleep_enable_ext0_wakeup(GPIO_NUM_35, 1);
        gpio_hold_en(GPIO_NUM_19); // cutoff power EN pin
        gpio_hold_en(GPIO_NUM_26); // blk
        gpio_hold_en(GPIO_NUM_27); // fan
        btStop();
        esp_bt_controller_disable();
        esp_sleep_enable_timer_wakeup(sleepWakeupTime * uS_TO_S_FACTOR);
        esp_deep_sleep_start();
        }
      */
      tft.setTextSize(1);
      tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
      tft.setCursor(197, 27);
      tft.drawRoundRect(193, 25, 55, 12, 3, TFT_MIDDLEGREY); // (xO, yO, Length, Width, Radius, color)
      loopEndT = millis() - currentTime;
      tft.print(1000 / loopEndT); tft.print("fps ");
    }
    tft.fillScreen(TFT_BLACK);
    cycleCount = 0;
    if (pageCount == 0) page0();
    if (pageCount == 1) page1();
    if (pageCount == 2) page2();
    if (pageCount == 3) page3();
    if (pageCount == 4) page4();
    if (pageCount == 5) page5();
    if (pageCount == 6) page6();
    if (pageCount == 7) page7();
    if (pageCount == 8) page8();
  }
}

void Alarms() {
  {
    Amps = (ina260.readCurrent() / 1000);
    if (Amps < 0) Amps = 0;
    Volts = (ina260.readBusVoltage() / 1000);
    Watts = (ina260.readPower());

    if (ta1 == true ||           // Fan Activation when Temp Alarm or CurrentTH
        ta2 == true ||
        ta3 == true ||
        ta4 == true ||
        ta5 == true ||
        ta6 == true ||
        ta7 == true ||
        Amps > currentTH)
    {
      FanActive = true;
      digitalWrite(fan, HIGH);
    } else {
      FanActive = false;
      digitalWrite(fan, LOW);
    }

    if (Volts < lowVoltAlarm ||
        Volts > highVoltAlarm ||     //   Critical Alarm Enable
        t1 > criticalTemp ||
        t2 > criticalTemp ||
        t3 > criticalTemp ||
        t4 > criticalTemp ||
        t5 > criticalTemp ||
        t6 > criticalTemp ||
        t7 > criticalTemp ||
        Amps < 3 && Amps > 2) {
      criticalAlarm = true;
    } else {
      criticalAlarm = false;
    }

    if (CO2 > CO2TH || TVOC > VOCTH) {
      AirWarning = true;
    } else {
      AirWarning = false;
    }

    if (deepSleepActive && sleepTimer > TimeoutT + TimeoutT2 + deepSleepStart) {
      gotoDeepSleep();
    }

    if (ledB == 250) {  // if you want to trigger ledB fade on, set ledB = 250
      ledB = 0;
      while (ledB < 254) {
        ledB++;
        delay(1);
        ledcWrite(ledChannel1, ledB);
      }
    }

    if (ledB == 1) {  // if you want to trigger ledB fade off, set ledB = 1
      ledB = 255;
      while (ledB > 0) {
        ledB--;
        delay(3);
        ledcWrite(ledChannel1, ledB);
      }
    }

    /*
      if (Volts < 6.6 && !VcheckOnce) { // forces powerSave when under x Volt
        deepSleepActive = true;
        setCpuFrequencyMhz(80);
        myCCS811.setDriveMode(3); // 0=idle, 1=1sec, 2=10sec, 3=60sec, 4=RAW
        MAX30105.shutDown();
        myBME280.settings.runMode = 0;
        VML.begin(false);
        //      TFToff();
        WiFi.disconnect(true);
        WiFi.mode(WIFI_OFF);
        btStop();
        esp_bt_controller_disable();
        ledB = 0;
        ledcWrite(ledChannel1, ledB);
        VcheckOnce = true;
        pageCount = 1;
      }
      if (Volts > 7) VcheckOnce = false;
    */
  }
}

void everyXsec() {
  if (millis() - previousMs > everyXms) {         // Code that runs every X ms ////////////// 1 SEC ////
    previousMs = millis();
    BatPercent = map(Volts, 6, 8.4, 0, 100);
    DTdevicecount = sensors.getDeviceCount();

    WiFistatus = WiFi.status();
    Time(timeinfo); // update Time
    readIMU();      // MPU9250 IMU Readings
    readCCS811();   // CCS811 Function /w error detection
    readUV();       // VEML6075 Combined UV-A, UV-B Readings

    if (loggingActive) Logging(); //         --- LOGGING ---

    if (pageCount == 0 || pageCount == 1 || pageCount == 2 && screenState) {
      printStatusBar();
      if (pageCount == 0 && !criticalAlarm) {
        tft.setTextSize(1);
        tft.setTextPadding(130);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setTextDatum(MC_DATUM);
        tft.drawString(RTCprint, 120, 120, 4);
      }
    }

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

    sensors.requestTemperatures();

    PowerLog = "";
    PowerLog += String(BatPercent);
    PowerLog += ", ";
    PowerLog += String(Volts) + ", ";
    PowerLog += String(Amps) + ", ";
    PowerLog += String(Watts / 1000) + ", ";

    tempProbes = "";
    tempProbes += String(t1) + ", ";
    tempProbes += String(t2) + ", ";
    tempProbes += String(t3) + ", ";
    tempProbes += String(t4) + ", ";
    tempProbes += String(t5) + ", ";
    tempProbes += String(t6) + ", ";
    tempProbes += String(t7) + ", ";
    //tempProbes += "\r\n";
  }
}


void gotoDeepSleep() {
  analogWrite(tftPIN, 0);
  myCCS811.setDriveMode(0); // IDLE
  MAX30105.shutDown();
  myBME280.settings.runMode = 1;
  ina260.setMode(INA260_MODE_SHUTDOWN);
  VML.begin(false);
  //    rtc_gpio_init(GPIO_NUM_27); //initialize the RTC GPIO port
  //    rtc_gpio_init(GPIO_NUM_26); //initialize the RTC GPIO port
  //    rtc_gpio_hold_dis(GPIO_NUM_27); //disable hold before setting the level
  //    rtc_gpio_hold_dis(GPIO_NUM_26); // disable hold before setting the level
  //    rtc_gpio_set_level(GPIO_NUM_27, LOW); //set high/low
  //    rtc_gpio_set_level(GPIO_NUM_26, LOW); //set high/low
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_2, 1); // 1 = High, 0 = Low, 2,4,35
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_4, 1);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_35, 1);
  rtc_gpio_set_direction(GPIO_NUM_17, RTC_GPIO_MODE_INPUT_ONLY);
  rtc_gpio_set_direction(GPIO_NUM_27, RTC_GPIO_MODE_INPUT_ONLY);
  rtc_gpio_set_direction(GPIO_NUM_26, RTC_GPIO_MODE_INPUT_ONLY);
  gpio_hold_en(GPIO_NUM_17); // led
  gpio_hold_en(GPIO_NUM_27); // tftBLK
  gpio_hold_en(GPIO_NUM_26); // fan
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  btStop();
  esp_bt_controller_disable();
  esp_sleep_enable_timer_wakeup(sleepWakeupTime * uS_TO_S_FACTOR);
  esp_deep_sleep_start();
}

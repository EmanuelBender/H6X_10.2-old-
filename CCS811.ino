#include <pgmspace.h>

void printCCS811() {

  if (myCCS811.checkForStatusError() > 0) {                         //// CCS811 Error Check LIVE no beeping
    CCS811Core::status returnCode = myCCS811.begin();
    tft.setTextColor(TFT_RED, TFT_BLACK);
    sensorXY();
    tft.print("Status");
    errXY();
    switch ( returnCode )
    {
      case CCS811Core::SENSOR_ID_ERROR: {
          tft.print("ID");
          break;
        }
      case CCS811Core::SENSOR_I2C_ERROR: {
          tft.print("I2C/PWR");
          break;
        }
      case CCS811Core::SENSOR_INTERNAL_ERROR: {
          uint8_t error = myCCS811.getErrorRegister();
          if ( error == 0xFF ) //comm error
          {
            tft.print("I2C");
          }
          else
          {
            if (error & 1 << 5) tft.print("HeaterSupply");
            if (error & 1 << 4) tft.print("HeaterFault");
            if (error & 1 << 3) tft.print("MaxResistance");
            if (error & 1 << 2) tft.print("MeasModeInvalid");
            if (error & 1 << 1) tft.print("ReadRegInvalid");
            if (error & 1 << 0) tft.print("MsgInvalid");
          }
          break;
        }
      case CCS811Core::SENSOR_GENERIC_ERROR: {
          tft.print("GNRL");
          break;
        }
    }
  } else {
    sensorXY();
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.print("Status             ");
  }

  if (myCCS811.dataAvailable())                    //// CCS811 Data Screen Print /////
  {

    const int temp = myHDC1080.readTemperature() / 1.225;
    const int tempBME = myBME280.readTempC() / 1.225;
    const int RH = myHDC1080.readHumidity();
    const int CO2 = myCCS811.getCO2();
    const int TVOC = myCCS811.getTVOC();
    const int alt = myBME280.readFloatAltitudeMeters();
    String pressure = String(myBME280.readFloatPressure() * 0.000145038 / 714); // in ATM
    pressure.toCharArray(pressure_value, 4);

    tft.setTextSize(3);
    tft.setCursor(14, 53);
    tft.setTextColor(TFT_BLACK, TFT_DARKGREY);

    if (CO2 > CO2TH) {
      tft.setTextColor(TFT_RED, TFT_DARKGREY);
    }
    tft.print("CO");
    tft.setTextSize(2);
    tft.print("2");
    tft.setTextSize(3);

    tft.setTextColor(TFT_BLACK, TFT_DARKGREY);
    tft.setCursor(85, 53);
    if (TVOC > VOCTH) {
      tft.setTextColor(TFT_RED);

    }
    tft.print("tVOC");

    myCCS811.readAlgorithmResults(); //compensating the CCS811 with humidity and temperature readings from the HDC1080
    myCCS811.setEnvironmentalData(RH, temp);

    tft.setCursor(0, 0);
    tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);                 // Print Temp
    tft.setTextSize(2);

    if (tempBME < 0) {
      tft.setTextColor(TFT_BLUE, TFT_BLACK);
    }
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
    tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
    tft.print("o ");

    // Print RH
    tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
    tft.setTextSize(2);
    tft.print(RH);
    tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
    tft.print("%");

    tft.setCursor(75, 0);
    //tft.drawLine(73, 2, 73, 12, TFT_MIDDLEGREY);
    tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);                 // Print Alt
    //if (alt > 999) {
    // tft.print((alt)/ 1000);
    // tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
    // tft.print("km");
    //} else {
    tft.print(alt);
    tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
    tft.print("m");
    //}

    //tft.print("  Atm ");                                      // Print ATM
    //tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
    //tft.print(pressure);
    //tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
    //tft.print("a");

    //tft.setTextColor(TFT_BLACK);   // Box #3
    //tft.setCursor(187, 53);
    //tft.print("RH");

    tft.setTextColor(TFT_WHITE, TFT_BLACK);                            // Print & Alarm Beep CCS811
    tft.setTextSize(3);
    if (CO2 > CO2TH) {    // Air Quality Alarm Beeper Dependent on Sensor Values and Alarm Threshold
      tone(beep, (800 + ((CO2 - 600) / 8)), ((CO2 - 1200) / 200));
      delay(50);
      tone(beep, (800 + ((CO2 - 600) / 8)), ((CO2 - 1200) / 200));
    }

    tft.setCursor(11, 87);
    if (CO2 > 999) {
      tft.setCursor(2, 87);
    }
    tft.fillRect(2, 87, 71, 22, TFT_BLACK);
    tft.print(CO2);


    tft.setCursor(113, 87);
    if (TVOC > 9) {
      tft.setCursor(104, 87);
    }
    if (TVOC > 99) {
      tft.setCursor(94, 87);
    }
    if (TVOC > 999) {
      tft.setCursor(83, 87);
    }

    tft.fillRect(82, 87, 73, 22, TFT_BLACK);
    tft.print(TVOC);
  }
}

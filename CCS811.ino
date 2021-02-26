#include <pgmspace.h>

void readCCS811() {

  //myCCS811.setDriveMode(4); // 0=idle, 1=1sec, 2=10sec, 3=60sec, 4=RAW

  tempHDC = myHDC1080.readTemperature() / 1.1;
  tempBME = (myBME280.readTempC() - 0.5) / 1.12; // 1.225
  tempCCS811 = myCCS811.getTemperature();
  RH = myHDC1080.readHumidity() * 1.05;
  alt = constrain(myBME280.readFloatAltitudeMeters(), -999, 10000) ;
  String pressure = String(myBME280.readFloatPressure() * 0.000145038 / 714); // in ATM
  pressure.toCharArray(pressure_value, 4);


  //if (myCCS811.dataAvailable())
  myCCS811.readAlgorithmResults(); //compensating the CCS811 with humidity and temperature readings from the HDC1080
  myCCS811.setEnvironmentalData(RH, tempHDC);
  CCS811err = myCCS811.checkForStatusError();

  CO2 = myCCS811.getCO2();
  TVOC = myCCS811.getTVOC();
  
  if (CO2 > 9999) {
    CO2 = 0;
  }
  if (TVOC > 9999) {
    TVOC = 0;
  }

  if (sleepTimer < TimeoutT) {
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


    tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);                 // Print Temp
    if (tempBME < 0) {
      tft.setTextColor(TFT_BLUE, TFT_BLACK);
    }
    if (tempBME < 15 && tempBME > 0) {
      tft.setTextColor(TFT_CYAN, TFT_BLACK);
    }
    if (tempBME > 28 && tempBME < 34) {
      tft.setTextColor(TFT_ORANGE, TFT_BLACK);
    }
    if (tempBME > 35) {
      tft.setTextColor(TFT_RED, TFT_BLACK);
    }

    tft.setTextDatum(TL_DATUM);
    tft.setTextSize(1);
    tft.setTextPadding(30);
    tft.drawString(tempBME + String("* "), 3, 1, 2);

    tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
    tft.drawString(RH + String("% "), 55, 1, 2);

    tft.setTextPadding(48);
    tft.drawString(alt + String("m "), 106, 1, 2);


    /*
        if (CO2 > CO2TH) {                          // Air Quality Alarm Beeper
          tone(beep, (800 + ((CO2 - 600) / 8)), ((CO2 - 1200) / 200));
          delay(50);
          tone(beep, (800 + ((CO2 - 600) / 8)), ((CO2 - 1200) / 200));
        } */

    tft.setTextDatum(MC_DATUM);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextPadding(70);
    tft.setTextSize(2);

    tft.drawNumber(CO2, 38, 99, 2); //4
    tft.drawNumber(TVOC, 121, 99, 2);
  }


  if (CCS811err == 0) {

    String envData = "";
    envData += String(CO2) + ", ";
    envData += String(TVOC) + ", ";
    envData += String(tempBME) + ", ";
    envData += String(RH) + ", ";
    envData += String(alt) + ", ";
    //envData += " || ID: ";
    //envData += String(myCCS811.checkForStatusError()) + "\r\n";

    appendFile(SD, LogFile, envData.c_str());

    if (sleepTimer < TimeoutT) {
      sensorXY();
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.print("Status  ");
    }

  } else {             //// CCS811 Error Check

    appendFile(SD, LogFile, "--, --, --, --, --, ");

    if (sleepTimer < TimeoutT) {
      CCS811Core::status returnCode = myCCS811.begin();
      tft.setTextColor(TFT_RED, TFT_BLACK);
      sensorXY();
      //tft.print("Status ");
      //errXY();
      switch ( returnCode )
      {
        case CCS811Core::SENSOR_ID_ERROR: {
            tft.print("ID/LowV");
            break;
          }
        case CCS811Core::SENSOR_I2C_ERROR: {
            tft.print("I");
            tft.setTextSize(1);
            tft.print("2");
            tft.setTextSize(2);
            tft.print("C/LowV");
            break;
          }
        case CCS811Core::SENSOR_INTERNAL_ERROR: {
            uint8_t error = myCCS811.getErrorRegister();
            if ( error == 0xFF ) //comm error
            {
              tft.print("ITRNL");
            }
            else
            {
              if (error & 1 << 5) tft.print("HeaterSupply");
              if (error & 1 << 4) tft.print("HeaterFault");
              if (error & 1 << 3) tft.print("MaxResistance");
              if (error & 1 << 2) tft.print("ModeInvalid");
              if (error & 1 << 1) tft.print("RegInvalid");
              if (error & 1 << 0) tft.print("MsgInvalid");
            }
            break;
          }
        case CCS811Core::SENSOR_GENERIC_ERROR: {
            tft.print("ValueMax");
            break;
          }
      }
    }
  }
}

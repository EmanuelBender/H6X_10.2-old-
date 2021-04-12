#include <pgmspace.h>

void readCCS811() {

  // myCCS811.setDriveMode(4); // 0=idle, 1=1sec, 2=10sec, 3=60sec, 4=RAW
  // myBME280.settings.runMode = 2; // 0=idle, 1=forced, 2=normal
  CCS811err = myCCS811.checkForStatusError();

  if (myCCS811.dataAvailable()) {

    myCCS811.readAlgorithmResults();

    tempBME = (myBME280.readTempC() - 0.4) / 1.12; // 1.225
    alt = constrain(myBME280.readFloatAltitudeMeters(), -999, 10000) ;
    pressure = String(myBME280.readFloatPressure() * 0.000145038 / 714); // in ATM
    pressure.toCharArray(pressure_value, 4);

    CO2 = myCCS811.getCO2();
    TVOC = myCCS811.getTVOC();
    tempCCS811 = myCCS811.getTemperature();

    RH = myHDC1080.readHumidity() * 1.05;
    tempHDC = myHDC1080.readTemperature() / 1.1;

    myCCS811.setEnvironmentalData(RH, tempBME);

    if (CO2 > 9999) {
      CO2 = 0;
    }
    if (TVOC > 9999) {
      TVOC = 0;
    }

    envData = "";
    envData += String(CO2) + ", ";
    envData += String(TVOC) + ", ";
    envData += String(tempBME) + ", ";
    envData += String(RH) + ", ";
    envData += String(alt) + ", ";
  }
}

void printSensorError() {

  CCS811Core::status returnCode = myCCS811.begin();

  switch ( returnCode )
  {
    case CCS811Core::SENSOR_ID_ERROR: {
        tft.println("ID / LowV");
        break;
      }
    case CCS811Core::SENSOR_I2C_ERROR: {
        tft.println("I2C / LowV");
        break;
      }
    case CCS811Core::SENSOR_INTERNAL_ERROR: {
        uint8_t error = myCCS811.getErrorRegister();
        if ( error == 0xFF ) //comm error
        {
          tft.println("ITRNL_COMM");
        }
        else
        {
          if (error & 1 << 5) tft.println("HeaterSupply");
          if (error & 1 << 4) tft.println("HeaterFault");
          if (error & 1 << 3) tft.println("MaxResistance");
          if (error & 1 << 2) tft.println("ModeInvalid");
          if (error & 1 << 1) tft.println("RegInvalid");
          if (error & 1 << 0) tft.println("MsgInvalid");
        }
        break;
      }
    case CCS811Core::SENSOR_GENERIC_ERROR: {
        tft.println("ValueMax/Generic");
        break;
      }
    default:
      tft.println("ok");
      break;
  }
}

void readIMU() {

  tft.setTextDatum(MC_DATUM);
  tft.setTextSize(1);
  tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
  tft.setTextPadding(50);

  if (IMU.accelUpdate() == 0) {
    aX = IMU.accelX();
    aY = IMU.accelY();
    aZ = IMU.accelZ();
    aSqrt = IMU.accelSqrt(); /*
    tft.println("accelX: " + String(aX));
    tft.println("accelY: " + String(aY));
    tft.println("accelZ: " + String(aZ));
    tft.println("accelSqrt: " + String(aSqrt)); */
  }

  if (IMU.gyroUpdate() == 0) {
    gX = IMU.gyroX();
    gY = IMU.gyroY();
    gZ = IMU.gyroZ(); /*
    tft.println("gyroX: " + String(gX));
    tft.println("gyroY: " + String(gY));
    tft.println("gyroZ: " + String(gZ)); */
  }

  if (IMU.magUpdate() == 0) {
    mX = IMU.magX();
    mY = IMU.magY();
    mZ = IMU.magZ();
    mDirection = IMU.magHorizDirection() + 180;
    if (pageCount == 0 && !criticalAlarm) {
      tft.drawNumber(mDirection, 205, 135, 4);
      tft.drawNumber(aSqrt, 205, 155, 4);
    }
  }
}

void readUV() {

  UVI = VML.getUVIndex();
  UVIsd = String(UVI) + ", ";

  if (sleepTimer < TimeoutT + TimeoutT2 && pageCount == 0) {
    switch (UVI) {
      case 1 ... 2:
        tft.setTextColor(TFT_DARKGREEN, TFT_BLACK);
        break;
      case 3 ... 5:
        tft.setTextColor(TFT_YELLOW, TFT_BLACK);
        break;
      case 6 ... 7:
        tft.setTextColor(TFT_ORANGE, TFT_BLACK);
        break;
      case 8 ... 10:
        tft.setTextColor(TFT_INDIA, TFT_BLACK);
        break;
      case 11 ... 15:
        tft.setTextColor(TFT_RED, TFT_BLACK);
        break;
      default:
        tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
        break;
    }

    tft.setTextPadding(28);
    tft.setTextSize(1);
    tft.setTextDatum(MC_DATUM);

    if (!criticalAlarm) {
      if (UVI < 0 || UVI > 99) {             // print UV Index
        tft.drawString("--", 120, 194, 4);
      } else {
        tft.drawNumber(UVI, 120, 194, 4);
      }
    }
  }
}

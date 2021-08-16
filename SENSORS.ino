#include <pgmspace.h>

void readSystemPower() {

  //  if (activeSOC) {
  //  soc.quickStart();
  //  soc.setThreshold(15);
  //  socAlert = soc.getAlert();
  //  socVolts = soc.getVoltage();
  //  SOC      = soc.getSOC();
  //  }


  if (activeINA) {
    if (ina260.conversionReady()) {

      Amps     = ina260.readCurrent();    // in mAh
      Volts    = ina260.readBusVoltage(); // in mV
      Watts    = ina260.readPower();      // in mW

      if (powerAlarm) {
        ina260.setMode(INA260_MODE_CONTINUOUS);
      } else {
        ina260.setMode(INA260_MODE_TRIGGERED);
      }

      if (batIDX >= 120) {
        ampsAvg   = batT / batIDX;
        voltsAvg  = volT / batIDX;
        batT      = 0;
        volT      = 0;
        batIDX    = 0;
      } else {
        batT     += Amps;
        volT     += Volts;
        batIDX++;
      }

      SOC           = constrain(map(voltsAvg, 6400, 8380, 0, 100), 0, 100);
      capacityLeft  = constrain(map(voltsAvg, 6400, 8380, 0, BatteryCapacity), 0, BatteryCapacity);
      batDayLeft    = (capacityLeft / ampsAvg) / 24;
      b1 = batDayLeft;
      batHourLeft   = (batDayLeft - b1) * 24;
      b2 = batHourLeft;
      batMinuteLeft = (batHourLeft - b2) * 60;

      BatteryTime   = String(int(batDayLeft)) + "d" + String(int(batHourLeft)) + "h"; // + String(batMinuteLeft) + "m";

      Volts = Volts / 1000;
      Amps  = Amps / 1000;

      if (loggingActive) {
        PowerLog  = "";
        PowerLog += String(SOC) + ", ";
        PowerLog += String(Volts) + ", ";
        PowerLog += String(Amps) + ", ";
        PowerLog += String(Watts / 1000) + ", ";
      }
    }
  }
}

void readEnvironmentData() {

  if (activeSCD) {
    if (scd30.dataAvailable()) {
      co2SCD   = scd30.getCO2();
      tempSCD  = scd30.getTemperature();
      humidSCD = scd30.getHumidity();
    }

    if (everyXsecFlag) {
      tempAMG = amg.readThermistor();
      myCCS811.setEnvironmentalData(humidSCD, tempSCD); //  humidHDC, tempBME
      doDewPoint(tempSCD, humidSCD);

      //    scd30.beginMeasuring();  // burst reading
      //    scd30.stopMeasurement();  // burst reading
      scd30.setAltitudeCompensation(altBME); // meters
      //    scd30.setAmbientPressure(pressureBME / 100);  // mBar
      //    scd30.setTemperatureOffset(t6 - int(tempSCD)); // adjusting SCD30 with outsideDevice t6 Ambient Temp
    }
  }


  if (activeBME) {
    // myCCS811.setDriveMode(4); // 0=idle, 1=1sec, 2=10sec, 3=60sec, 4=RAW
    // myBME280.settings.runMode = 2; // 0=idle, 1=forced, 2=normal
    if (!myBME280.isMeasuring()) {
      tempBME     = myBME280.readTempC();
      altBME      = constrain(myBME280.readFloatAltitudeMeters(), -999, 9999);
      pressureBME = (myBME280.readFloatPressure() / 101325); // to ATM / 101325  -- Bar
      //    pressureBME.toCharArray(pressure_value, 4); // convert to char array
    }

    //  humidHDC = myHDC1080.readHumidity();
    //  tempHDC  = myHDC1080.readTemperature();

    if (hdcIDX >= 25) {
      humidHDC  = hdcT / hdcIDX;
      tempHDC   = hdcT2 / hdcIDX;
      hdcT      = 0;
      hdcT2     = 0;
      hdcIDX    = 0;
    } else {
      hHDC   =  myHDC1080.readHumidity();
      hdcT  += hHDC;
      tHDC   =  myHDC1080.readTemperature();
      hdcT2 += tHDC;
      hdcIDX++;
    }
  }

  if (activeCCS) {
    if (myCCS811.dataAvailable()) {

      myCCS811.readAlgorithmResults();
      co2CCS  = myCCS811.getCO2();   // ppm 0 - 400, 400 - 1000, 1000 - 1500, 1500 - 2000, 2000 - 5000, >5000
      tvocCCS = myCCS811.getTVOC(); // ppb 0 - 200, 200 - 600, 600 - ...;
      //       resCCS = myCCS811.getResistance();

      if (tvocIDX >= 8) {
        tvocSMPL = tvocT / tvocIDX;
        co2SMPL  = ccsT / tvocIDX;
        tvocT    = 0;
        ccsT     = 0;
        tvocIDX  = 0;
      } else {
        tvocT += tvocCCS;
        ccsT  += co2CCS;
        tvocIDX++;
      }

      //      AirQI = (map(tvocCCS, 0, 1200, 0, 6) + (map(((co2SMPL + co2SCD) / 2000), 0, 5000, 0, 6))) / 2;
      //      AirQI = (map(tvocSMPL, 0, 800, 0, 6) + map(co2SCD, 400, 4000, 0, 6)) / 2;
      if (activeSCD) {
        if (map(tvocSMPL, 0, 800, 0, 6) > map(co2SCD, 400, 4000, 0, 6)) {
          AirQI = map(tvocSMPL, 0, 800, 0, 6);
        } else {
          AirQI = map(co2SCD, 400, 4000, 0, 6);
        }
      } else {
        if (map(tvocSMPL, 0, 800, 0, 6) > map(co2SMPL, 400, 4000, 0, 6)) {
          AirQI = map(tvocSMPL, 0, 800, 0, 6);
        } else {
          AirQI = map(co2SMPL, 400, 4000, 0, 6);
        }
      }

      if (loggingActive) {
        envData  = "";
        envData += String(co2SCD) + ", ";
        envData += String(co2SMPL) + ", ";
        envData += String(tvocSMPL) + ", ";
        envData += String(tempSCD) + ", ";
        envData += String(humidSCD) + ", ";
        envData += String(altBME) + ", ";
        envData += String(pressureBME) + ", ";
      }
    }
  }
}

String printSensorError() {

  CCS811Core::status returnCode = myCCS811.begin();

  switch (returnCode) {
    case CCS811Core::SENSOR_ID_ERROR:
      {
        return "ID / LowC";
        break;
      }
    case CCS811Core::SENSOR_I2C_ERROR:
      {
        return "I2C / LowC";
        break;
      }
    case CCS811Core::SENSOR_INTERNAL_ERROR:
      {
        uint8_t error = myCCS811.getErrorRegister();
        if (error == 0xFF) { //comm error
          return "ITRNL_COMM";
        } else {
          if (error & 1 << 5)
            return "HeaterSupply";
          if (error & 1 << 4)
            return "HeaterFault";
          if (error & 1 << 3)
            return "MaxResistance";
          if (error & 1 << 2)
            return "ModeInvalid";
          if (error & 1 << 1)
            return "RegInvalid";
          if (error & 1 << 0)
            return "MsgInvalid";
        }
        break;
      }
    case CCS811Core::SENSOR_GENERIC_ERROR:
      {
        return "ValueMax";
        break;
      }
    default:
      return "ok";
      break;
  }
}

void readUV() {

  //    VML.powerOn();
  //    VML.shutdown();
  if (activeVML) {
    UVI = VML.index();
    //  UVA = VML.uva();
    //  UVB = VML.uvb();
    VML.trigger();
    if (UVI > 4) uvWarning = true;
    if (loggingActive) UVIsd = String(UVI) + ", ";
  } else if (loggingActive) {
    UVIsd = "--, ";
  }
}

void amg8833() { // Thermal Cam AMG8833

  amg.readPixels(pixels);

  maxTempAMG = pixels[64]; // initialize the maximum as the first element
  for (idx = 1; idx < 64; ++idx) {
    if (pixels[idx] > maxTempAMG)
      maxTempAMG = pixels[idx]; // find biggest value
  }

  minTempAMG = pixels[0]; // initialize the minimum as the first element
  for (idx = 1; idx < 64; ++idx) {
    if (pixels[idx] < minTempAMG)
      minTempAMG = pixels[idx]; // find smallest value
  }

  if (amgSetHiRes) {
    MINTEMP = maxTempAMG - (minTempAMG / 3);
    MAXTEMP = maxTempAMG;

    if (MAXTEMP - MINTEMP < 4) { // 4
      MAXTEMP += 6; // 16
    }
    else if (MAXTEMP - MINTEMP < 2) { // 4
      MINTEMP += 6;
      MAXTEMP += 18;
    }
  }

  everyX = millis(); // how long does the Interpolation take
  interpolate_image(pixels, AMG_ROWS, AMG_COLS, dest_2d, ROWS, COLS);

  drawpixels(dest_2d, ROWS, COLS, boxsize, boxsize);
  everyX = millis() - everyX;
}



/*
  void readIMU() {
  if (IMU.accelUpdate() == 0) {
    //    aX = IMU.accelX();
    //    aY = IMU.accelY();
    //    aZ = IMU.accelZ();
    aSqrt = IMU.accelSqrt();
    tft.println("accelX: " + String(aX));
    tft.println("accelY: " + String(aY));
    tft.println("accelZ: " + String(aZ));
    tft.println("accelSqrt: " + String(aSqrt));
  }

  if (IMU.gyroUpdate() == 0) {
    gX = IMU.gyroX();
    gY = IMU.gyroY();
    gZ = IMU.gyroZ();
    tft.println("gyroX: " + String(gX));
    tft.println("gyroY: " + String(gY));
    tft.println("gyroZ: " + String(gZ));
  }

  if (IMU.magUpdate() == 0) {
    //    mX = IMU.magX();
    //    mY = IMU.magY();
    //    mZ = IMU.magZ();
    mDirection = IMU.magHorizDirection() + 180;
    if (pageCount == 0 && !powerAlarm) {
      tft.setTextDatum(MC_DATUM);
      tft.setTextSize(1);
      tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
      tft.setTextPadding(45);
      //      tft.drawNumber(mDirection, 205, 135, 4);
      tft.drawNumber(steps, TFT_WIDTH / 2 - 40, 97, 4);
      tft.setTextColor(TFT_LIGHTGREY);
      tft.drawString("steps", TFT_WIDTH / 2 - 40, 97, 1);
    }
  }

  if (aSqrt > stepTH && !flag) {
    steps++;  // if it crosses threshold increment step by one and raise the flag
    flag = 1;
  }
  if (aSqrt < stepTH && flag) flag = 0;
  }
*/

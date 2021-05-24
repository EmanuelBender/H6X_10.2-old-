#include <pgmspace.h>

void Time(tm localTime) {
  minElapsed = millisElapsed / 1000 / 60; // time elapsed since boot in min
  secElapsed = millisElapsed / 1000;
  DateTime now = rtc.now();
  tempRTC = rtc.getTemperature();

  yr = now.year();    // RTC time
  mo = now.month();
  da = now.day();
  hr = now.hour();
  mi = now.minute();
  se = now.second();
  dow = now.dayOfTheWeek();
  /*
    yr = localTime.tm_year - 100;  // ESP system Time
    mo = localTime.tm_mon + 1;
    da = localTime.tm_mday;
    hr = localTime.tm_hour;
    mi = localTime.tm_min;
    se = localTime.tm_sec;
    dow = now.dayOfTheWeek();
  */


  RTCdate = "/" + String(da) + "." + String(mo) + "." + String(yr) + ".txt";
  RTCdate.toCharArray(LogFile, 16);

  RTCt = "";
  RTCt += "\n";
  if (hr <= 9) {
    RTCt += "0";
  }
  RTCt += String(hr) + ":";
  if (mi <= 9) {
    RTCt += "0";
  }
  RTCt += String(mi) + ":";
  if (se <= 9) {
    RTCt += "0";
  }
  RTCt += String(se);
  RTCt += ", ";

  RTCt.toCharArray(RTClog, 13);


  RTCprint = "";
  if (hr <= 9) {
    RTCprint += "0";
  }
  RTCprint += String(hr) + ":";
  if (mi <= 9) {
    RTCprint += "0";
  }
  RTCprint += String(mi) + ":";
  if (se <= 9) {
    RTCprint += "0";
  }
  RTCprint += String(se);
}


void Logging() {
  if (loggingActive && SDpresent) {
    //  readLogFile(SD, LogFile);
    // "\nTime, Bat %, Load V, Current, Watts, t1, t2, t3, t4, t5, t6, t7, CO2, tVOC, Temp, RH, Alt, UV, Backlight, Fan, LED, LowPower, deepSleep\n";
    SDdata = "";

    SDdata += RTCt;
    SDdata += PowerLog;
    SDdata += tempProbes;

    if (CCS811err == 0) {
      SDdata += envData;
    } else {
      SDdata += "--, --, --, --, --, ";
    }

    if (activeVML) {
      SDdata += "--, ";
    } else {
      SDdata += UVIsd;
    }

    if (screenState) {
      SDdata += "3, ";
    } else {
      SDdata += "0, ";
    }

    if (fanActive) {
      SDdata += "2, ";
    } else {
      SDdata += "0, ";
    }

    if (ledB > 0) {
      ledBprint = ledB / 10;
      SDdata += ledBprint;
      SDdata +=  ", ";
    } else {
      SDdata +=  "0, ";
    }

    if (lowPowerMode) {
      SDdata += "1, ";
    } else {
      SDdata += "0, ";
    }

    if (deepSleepActive) {
      SDdata += "1";
    } else {
      SDdata += "0";
    }

    appendFile(SD, LogFile, SDdata.c_str());
  }
}




/*
  if ((localTime.tm_hour) <= 9) {
  tft.print("0");
  tft.print(localTime.tm_hour);
  } else {
  tft.print(localTime.tm_hour);
  }
  tft.print(':');

  if ((localTime.tm_min) <= 9) {
  tft.print("0");
  tft.print(localTime.tm_min);
  } else {
  tft.print(localTime.tm_min);
  //tft.print(localTime.tm_sec);
  }
  }

      if ((localTime.tm_mday) <= 9) {
        tft.print(localTime.tm_mday);

            Serial.print('.');
            if ((localTime.tm_mon + 1) <= 9) {
              Serial.print("0");
              Serial.print(localTime.tm_mon + 1);
            } else {
              Serial.print(localTime.tm_mon + 1);
            }

            Serial.print('.');
            Serial.print(localTime.tm_year - 100);
            Serial.print(" ");
            }

  Serial.print(' ');
  switch (localTime.tm_mon + 1) {   //    Month in Words
  case 1:
    Serial.print("January");
    break;
  case 2:
    Serial.print("February");
    break;
  case 3:
    Serial.print("March");
    break;
  case 4:
    Serial.print("April");
    break;
  case 5:
    Serial.print("May");
    break;
  case 6:
    Serial.print("June");
    break;
  case 7:
    Serial.print("July");
    break;
  case 8:
    Serial.print("August");
    break;
  case 9:
    Serial.print("September");
    break;
  case 10:
    Serial.print("October");
    break;
  case 11:
    Serial.print("November");
    break;
  case 12:
    Serial.print("December");
    break;
  }
  Serial.println("");
  //Serial.println("");
*/

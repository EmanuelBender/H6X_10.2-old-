#include <pgmspace.h>

void Time(tm localTime) {          // happens every X sec
  secElapsed = millisElapsed / 1000; // time elapsed since boot in min
  minElapsed = secElapsed / 60;
  time(&now);                        // RTC time
  localtime_r(&now, &timeinfo);      // ESP32 Time format?
  DateTime now = rtc.now();

  yr = now.year() - 208;             // RTC time?
  mo = now.month();
  da = now.day();
  hr = now.hour();
  mi = now.minute();
  se = now.second();
  dow = now.dayOfTheWeek();

  /*
    yr = localTime.tm_year - 100;    // ESP system Time
    mo = localTime.tm_mon + 1;
    da = localTime.tm_mday;
    hr = localTime.tm_hour;
    mi = localTime.tm_min;
    se = localTime.tm_sec;
    dow = now.dayOfTheWeek();
  */

  RTCd = "";
  RTCd += String(da) + "." + String(mo) + "." + String(yr);

  RTClogfile = "";
  RTClogfile = "/" + RTCd + logFileFormat;
  RTClogfile.toCharArray(LogFile, 16);

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


  RTCt = "";
  RTCt += "\n";
  RTCt += RTCprint;
  RTCt += ", ";
  RTCt.toCharArray(RTClog, 13);
}


void Logging() {
  if (loggingActive && SDpresent) {
    //  readLogFile(SD, LogFile);
    SDdata = "";

    SDdata += RTCt;
    SDdata += RTCd + ", ";
    SDdata += PowerLog;
    SDdata += tempProbes;
    SDdata += envData;
    SDdata += UVIsd;

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

    SDdata += String(ledB) + ", ";
    SDdata += String(lowPowerMode) + ", ";
    SDdata += String(deepSleepActive) + ", ";
    SDdata += translate_wl_status(WiFi.status());

    appendFile(SD, LogFile, SDdata.c_str());
  }
}

void panicLog() {  // need Panic Trigger

  panic = "";
  panic += RTCt + RTCd + ", ";
  panic += "Sleep in, " + String(100 - cycleCount) + "\n";
  panic += "Power, " + String(Volts) + "V, " + String(Amps) + "A, " + String(SOC) + "%\n";

  panic += "Probes, ";
  panic += String(t1) + "°, ";
  panic += String(t2) + "°, ";
  panic += String(t3) + "°, ";
  panic += String(t4) + "°, ";
  panic += String(t5) + "°, ";
  panic += String(t6) + "°, ";
  panic += String(t7) + "°, ";
  panic += String(t8) + "°\n";

  panic += "Sensors, " + String(tempBME) + "°, " + String(tempSCD) + "°, " + String(tempHDC) + "°, " + String(tempRTC) + "°, " + String(amg.readThermistor()) + "°\n";

  if (wetAlarm) panic += "Water Ingress Detected!, ";
  panic += String(humidSCD) + "%, " + String(humidHDC) + "%, ";

  if (fanActive) panic += "Fan Active @ " + String(fanPWM); // add in fan Speed

  panic += "\n";

  appendFile(SD, LogFile, panic.c_str());
  if (RTCprint == "00:00:00") print_wakeup_reason();

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

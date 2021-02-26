#include <pgmspace.h>


void printTime(tm localTime) {

  DateTime now = rtc.now();
  yr = now.year();
  mo = now.month();
  da = now.day();
  hr = now.hour() - 1;
  mi = now.minute();
  se = now.second();

  String RTCDate = "/" + String(da) + "." + String(mo) + "." + String(yr) + ".txt";
  RTCDate.toCharArray(LogFile, 16);

  tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
  tft.setTextSize(2);
  if (SD.exists(LogFile)) {
    tft.setCursor(0, 160);
    tft.print(LogFile);
  } else {
    tft.setCursor(0, 160);
    tft.print("No SDcard     ");
  }

  if (Setup2 == true) {         ///////////////////////////////////////// VOID Setup x2

    if (digitalRead(tPAD2) == HIGH && SD.exists(LogFile)) {
      SD.remove(LogFile);
      tone(beep, 3800, 6);
      delay(60);
      tone(beep, 3800, 6);
    }

    preferences.begin("my - app", false);
    unsigned long int counter = preferences.getUInt("counter", 0);


    String SDcounter = "";

    SDcounter += "\nTime, Load V, Bus V, Current, Watts, t1, t2, t3, t4, t5, t6, t7, CO2, tVOC, Temp, RH, Alt, UV, Backlight, Fan, LED\n";
    SDcounter += "RESTART, #";
    SDcounter += String(counter);
    SDcounter += ", v";
    SDcounter += String(Revision);

    if (rtc.lostPower() == true) {                           // RTC setup
      SDcounter += ", Hard Reset\n";
    } else {
      SDcounter += ", Soft Reset\n";
    }
    appendFile(SD, LogFile, SDcounter.c_str());

    Setup2 = false;
  }

  preferences.end();


  String RTCt = "";
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
  appendFile(SD, LogFile, RTClog);


  String RTCprint = "";
  if (hr <= 9) {
    RTCprint += "0";
  }
  RTCprint += String(hr) + ":";
  if (mi <= 9) {
    RTCprint += "0";
  }
  RTCprint += String(mi);

  if (sleepTimer < TimeoutT) {                 // Print to TFT
    tft.setCursor(175, 0);
    tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
    tft.setTextSize(2);
    tft.print(RTCprint);
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
  */





  /*
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
}

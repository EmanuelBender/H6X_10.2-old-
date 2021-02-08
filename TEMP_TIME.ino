#include <pgmspace.h>

void readBodyTEMP() {

  //buttonState2 = digitalRead(tPAD2);
  float BodyTemp = mlx.readObjectTempC();

  tft.setTextSize(3);
  tft.setTextColor(TFT_BLACK, TFT_BLACK);
  tft.setCursor(86, 166);
  tft.print("Body");
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.fillRect(82, 133, 73, 22, TFT_BLACK);

  tft.setCursor(84, 133);
  tft.print(BodyTemp, 0);

}

void readTEMP()
{
  sensors.requestTemperatures();
  /*
    tft.setTextSize(1);
    tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
    tft.setCursor(129, 202);
    printTemperature(tempProbe1);
    tft.print(" ");
    printTemperature(tempProbe2);
    tft.print(" ");
    printTemperature(tempProbe3); tft.println("");
    tft.setCursor(129, 211);
    printTemperature(tempProbe4);
    tft.print(" ");
    printTemperature(tempProbe5);
    tft.print(" ");
    printTemperature(tempProbe6);
    //tft.setCursor(129, 223);
    //printTemperature(tempProbe7);
  */
  if (checkAlarm(tempProbe1) ||
      checkAlarm(tempProbe2) ||
      checkAlarm(tempProbe3) ||
      checkAlarm(tempProbe4) ||
      checkAlarm(tempProbe5) ||
      checkAlarm(tempProbe6) == true)
  {
    digitalWrite(fan, HIGH);
  } else {
    digitalWrite(fan, LOW);
  }

  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setCursor(165, 127);
  if (sensors.hasAlarm(tempProbe1) == true) {
    tft.print("BA1 ");
    printTemperature(tempProbe1);
  } else {
    tft.print("BA1   ");
  }

  tft.setCursor(165, 151);
  if (sensors.hasAlarm(tempProbe2) == true) {
    tft.print("MID ");
    printTemperature(tempProbe2);
  } else {
    tft.print("MID   ");
  }

  tft.setCursor(165, 175);

  if (sensors.hasAlarm(tempProbe3) == true) {
    tft.print("BA2 ");
    printTemperature(tempProbe3);
  } else {
    tft.print("BA2   ");
  }


  tft.setCursor(5, 127);
  if (sensors.hasAlarm(tempProbe4) == true) {
    printTemperature(tempProbe4);
    tft.print(" ESP");
  } else {
    tft.print("   ESP");
  }
  tft.setCursor(5, 151);
  if (sensors.hasAlarm(tempProbe5) == true) {
    printTemperature(tempProbe5);
    tft.print(" BUS");
  } else {
    tft.print("   BUS");
  }
  tft.setCursor(5, 175);
  if (sensors.hasAlarm(tempProbe6) == true) {
    printTemperature(tempProbe6);
    tft.print(" LED");
  } else {
    tft.print("   LED");
  }

}

void printTime(tm localTime) {
  time(&now);
  localtime_r(&now, &timeinfo);
  DateTime now = rtc.now();

  tft.setCursor(178, 0);
  tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
  tft.setTextSize(2);
  /*
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
  }

  //tft.print(':');
  //if ((localTime.tm_sec) <= 9) {
  //  tft.print("0");
  //  tft.print(localTime.tm_sec);
  //} else {
  //  tft.print(localTime.tm_sec);
  //}
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

#include <pgmspace.h>

void readTEMP() {

  bool buttonState2 = (digitalRead(tPAD2));

  if (buttonState2 != lastButtonState2 && ButtonsActive == true) {
    ledcWrite(ledChannel1, 0);
    tft.pushImage(0, 0, 240, 240, TProbes);
    //tft.fillRoundRect(178, 102, 46, 92, 16, TFT_MIDDLEGREY);
    //tft.fillRoundRect(180, 100, 42, 96, 16, TFT_BLACK);
    tft.drawRoundRect(183, 102, 36, 92, 16, TFT_LIGHTGREY);

    while (buttonState2 == HIGH && ButtonsActive == true) {

      sensors.requestTemperatures();
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

      tft.setTextSize(2);
      tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);

      tft.setCursor(167, 20);
      tft.print("AMB ");
      if ((t1 >= 0) && (t1 <= 9)) {
        tft.print(" ");
      }
      printTemperature(tempProbe1);


      tft.setCursor(3, 30);
      printTemperature(tempProbe4);
      if ((t4 >= 0) && (t4 <= 9)) {
        tft.print("  ");
      } if (t4 < -9) {
        tft.print("");
      } if (t4 > 9) {
        tft.print(" ");
      }
      tft.print("ESP");


      tft.setCursor(167, 78);
      tft.print("BAT ");
      if ((t2 >= 0) && (t2 <= 9)) {
        tft.print(" ");
      }
      printTemperature(tempProbe2);


      tft.setCursor(3, 108);
      printTemperature(tempProbe5);
      if ((t5 >= 0) && (t5 <= 9)) {
        tft.print("  ");
      } if (t5 < -9) {
        tft.print("");
      } if (t5 > 9) {
        tft.print(" ");
      }
      tft.print("PWR");


      tft.setCursor(3, 157);
      printTemperature(tempProbe6);
      if ((t6 >= 0) && (t6 <= 9)) {
        tft.print("  ");
      } if (t6 < -9) {
        tft.print("");
      } if (t6 > 9) {
        tft.print(" ");
      }
      tft.print("BAT");


      tft.setCursor(3, 200);
      printTemperature(tempProbe7);
      if ((t7 >= 0) && (t7 <= 9)) {
        tft.print("  ");
      } if (t7 < -9) {
        tft.print("");
      } if (t7 > 9) {
        tft.print(" ");
      }
      tft.print("BUS");


      tft.setCursor(167, 205);
      tft.print("LED ");
      if ((t3 >= 0) && (t3 <= 9)) {
        tft.print(" ");
      }
      printTemperature(tempProbe3);


      if (ta1 == true ||   // Fan Activation
          ta2 == true ||
          ta3 == true ||
          ta4 == true ||
          ta5 == true ||
          ta6 == true ||
          ta7 == true ||
          current_A > current_TH)
      {
        tft.pushImage(192, 114, 18, 18, FAN18);
        digitalWrite(fan, HIGH);
      } else {
        tft.fillRect(192, 114, 18, 18, TFT_BLACK);
        digitalWrite(fan, LOW);
      }

      if (loadvoltage < 7) {
        tft.pushImage(192, 139, 18, 18, LowbatY);
      } if (loadvoltage < 6) {
        tft.pushImage(192, 139, 18, 18, LowbatR);
      } if (loadvoltage > 7) {
        tft.fillRect(192, 139, 18, 18, TFT_BLACK);
      }

      if (digitalRead(tPAD2) == LOW) break;
    }
    tft.fillScreen(TFT_BLACK);
    staticGFX();
  }
}


/*
  bool checkAlarm(DeviceAddress deviceAddress)
  {
  if (sensors.hasAlarm(deviceAddress))
  {
    return true;
  }
  return false;
  } */

void readBodyTEMP() {

  float mlxTemp = mlx.readObjectTempC();

  tft.setTextSize(3);
  tft.setTextColor(TFT_BLACK);
  tft.setCursor(86, 166);
  tft.print("Body");

  tft.setTextDatum(MC_DATUM);
  tft.setTextPadding(60);
  tft.setTextSize(2);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  if (mlxTemp > 39) {
    tft.setTextColor(TFT_INDIA, TFT_BLACK);
  }
  tft.drawNumber(mlxTemp, 120, 144, 2);
}

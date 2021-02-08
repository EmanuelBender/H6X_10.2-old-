#include <pgmspace.h>


void readPOWER() {
  /*
     //ina219.recalibrate();
    //ina219.reconfig();
    unsigned long currentMillis = millis();

    if ((unsigned long)(currentMillis - previousMillisReadData) >= intervalReadData) {
      previousMillisReadData = millis();
      uint32_t count = 0;
      unsigned long newtime;

      // reads busVoltage
      busvoltage = ina219.busVoltage();
      // waits for conversion ready
      while (!ina219.ready() && count < 10) {
        count++;
        delay(1);
        busvoltage = ina219.busVoltage();
      }
      shuntvoltage = ina219.shuntVoltage() * 1000;   // read the other INA219 values
      current_A = ina219.shuntCurrent();
      batvoltage = busvoltage + (shuntvoltage / 1000);
      power = ina219.busPower();
      newtime = millis();
      tick = newtime - lastread;
      Ah += (current_A * tick) / 3600000.0;
      lastread = newtime;

      //Serial.print("tick:   "); Serial.print(tick); Serial.println(" ms");
    }
    if ((unsigned long)(currentMillis - previousMillisDisplay) >= intervalDisplay) {
      previousMillisDisplay = millis();
      tft.setCursor(6, 203);
      tft.setTextSize(2);
      tft.setTextColor(TFT_GOLD, TFT_BLACK);
      //tft.print("Bus:      "); Serial.print(busvoltage,1); Serial.println(" V");
      //Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage,2); Serial.println(" mV");
      //tft.print("Bat:      "); Serial.print(batvoltage,1); Serial.println(" V");
      tft.print(current_A, 2); //tft.print("A");
      //tft.print("Power:         "); Serial.print(power,2); Serial.println(" W");
      tft.setCursor(68, 203);
      tft.setTextColor(TFT_INDIA, TFT_BLACK);
      tft.print(batvoltage, 2); //tft.println("V");
      //tft.print(Ah, 1); tft.print("Ah");
      //tft.println("");
    }
    // prepare for next read -- this is security just in case the ina219 is reset by transient curent
  */

  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  //float power_mW = 0;

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  //power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);

  tft.setTextSize(2);
  tft.setCursor(8, 203);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  tft.print(loadvoltage, 2); //tft.println("V")
  tft.setCursor(68, 203);
  tft.setTextColor(TFT_INDIA, TFT_BLACK);
  tft.print(shuntvoltage, 2);
  tft.setCursor(128, 203);
  tft.setTextColor(TFT_GOLD, TFT_BLACK);

  if (current_mA > 100) {
    tft.setTextColor(TFT_RED, TFT_BLACK);
    digitalWrite(fan, HIGH);
  } else {
    digitalWrite(fan, LOW);
  }

  if (current_mA < 0) {
    tft.print(" -- ");
  } else {
    tft.print(current_mA / 1000, 2);
  }
}

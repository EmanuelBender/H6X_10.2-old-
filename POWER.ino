#include <pgmspace.h>


void readPOWER() {

  shuntvoltage = ina219.getShuntVoltage_mV();
  if (shuntvoltage < 0) shuntvoltage = 0;
  busvoltage = ina219.getBusVoltage_V();
  current_A = ina219.getCurrent_mA() / 1000;
  if (current_A < 0) current_A = 0;
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);

  tft.setTextSize(2);
  tft.setCursor(8, 203);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  tft.print(loadvoltage, 2); //tft.println("V")
  tft.setCursor(68, 203);
  tft.setTextColor(TFT_INDIA, TFT_BLACK);
  tft.print(shuntvoltage, 1);
  tft.setCursor(127, 203);
  tft.setTextColor(TFT_GOLD, TFT_BLACK);
  tft.print(current_A, 2);


  tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
  tft.setCursor(186, 203);
  tft.print(power_mW, 0);
  //tft.setTextSize(1);
  tft.print(" ");

  String PowerLog = "";

  PowerLog += String(loadvoltage) + ", ";
  PowerLog += String(busvoltage) + ", ";
  PowerLog += String(current_A) + ", ";
  PowerLog += String(power_mW / 1000) + ", ";


  appendFile(SD, LogFile, PowerLog.c_str());
  //Serial.print(PowerLog.c_str());


  String tempProbes = "";

  //tempProbes += String(sensors.getDeviceCount());
  //tempProbes += " TempProbes: \r\n";
  tempProbes += String(t1) + ", ";
  tempProbes += String(t2) + ", ";
  tempProbes += String(t3) + ", ";
  tempProbes += String(t4) + ", ";
  tempProbes += String(t5) + ", ";
  tempProbes += String(t6) + ", ";
  tempProbes += String(t7) + ", ";
  //tempProbes += "\r\n";

  appendFile(SD, LogFile, tempProbes.c_str());
  //Serial.print(tempProbes.c_str());


}

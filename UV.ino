#include <pgmspace.h>

void readUV()
{
  float UVI = constrain(VML.getUVIndex(), 0 , 99);

  if (sleepTimer < TimeoutT) {
    tft.setTextSize(3);
    tft.setTextColor(TFT_BLACK, TFT_DARKGREY);
    tft.setCursor(169, 53);
    if (UVI > 5) {
      tft.setTextColor(TFT_RED, TFT_BLACK);
    }
    tft.print(" UV");
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextPadding(60);
    tft.setTextSize(2);

    if (UVI < 0 || UVI > 99) {
      tft.drawString("--", 203, 99, 2);
    } else {
      tft.drawNumber(UVI, 203, 99, 2);
    }
  }
  String UVIsd = String(UVI) + ", ";

  //UVIsd += String(VML.getID()) + "\r\n";

  appendFile(SD, LogFile, UVIsd.c_str());
  //Serial.print(UVIsd.c_str());
}

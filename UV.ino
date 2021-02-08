#include <pgmspace.h>

void readUV()
{
  //ESP_LOGI("MAIN", "UVA: %.2f  UVB: %.2f  UVINDEX: % .2f", VML.getUVA(), VML.getUVB(), VML.getUVIndex());
  //vTaskDelay(1000);

  if (uv.begin() == true) {

    float UVI = uv.readUVI();
    tft.setTextSize(3);
    tft.setTextColor(TFT_BLACK, TFT_DARKGREY);
    tft.setCursor(169, 53);

    if (UVI > 5) {
      tft.setTextColor(TFT_RED, TFT_BLACK);
    }
    tft.print(" UV");
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.setCursor(196, 87);
    if (UVI > 9) {
      tft.setCursor(186, 87);
    }
    if (UVI > 99) {
      tft.setCursor(176, 87);
    }
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.fillRect(167, 87, 72, 22, TFT_BLACK);
    tft.fillRect(186, 24, 23, 14, TFT_BLACK);

    if (UVI < 0 || UVI > 99) {
      tft.print("-");
    } else {
      tft.print(UVI, 0);
    }
  } else {
    tft.setTextSize(3);
    tft.setCursor(196, 87);
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.print("-");
    tft.setTextSize(2);
    tft.setCursor(186, 24);
    tft.print("UV");

  }
}

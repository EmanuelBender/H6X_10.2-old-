#include <pgmspace.h>


void smlPRNT(String val1, const char* message, int x, int x2) { // small 0,94" OLED screen print data funtions
  u8g2.clearBuffer();     // clear the internal memory
  val1.toCharArray(charArr, 9);

  u8g2.setFont(u8g2_font_logisoso20_tf);
  u8g2.drawStr((u8g2.getStrWidth(charArr) / 2) + 32 + x, 24, charArr);

  u8g2.setFont(u8g2_font_chroma48medium8_8r); // choose a suitable font
  u8g2.drawStr((u8g2.getStrWidth(message) / 2) + 32 + x2, 32, message);

  u8g2.sendBuffer();     // transfer internal memory to the display
}

void smlPRNT2(String val1, String val2, int x, int x2) { // small 0,94" OLED screen print data funtions
  u8g2.clearBuffer();     // clear the internal memory
  val1.toCharArray(charArr, 9);

  u8g2.setFont(u8g2_font_logisoso18_tn);
  u8g2.drawStr((u8g2.getUTF8Width(charArr) / 2) + 32 + x, 20, charArr);

  val2.toCharArray(charArr, 9);
  u8g2.setFont(u8g2_font_helvR10_tn);
  u8g2.drawStr((u8g2.getUTF8Width(charArr) / 2) + 32 + x2, 32, charArr);

  u8g2.sendBuffer();     // transfer internal memory to the display
}

void smlCHRG() {    // have never tested this
  u8g2.clearBuffer();     // clear the internal memory
  u8g2.setFont(u8g2_font_battery19_tn); // 8 x 19

  if (count == 1) {
    u8g2.drawStr(37, 6, "0"); count++;
  } else if (count == 2) {
    u8g2.drawStr(37, 6, "1"); count++;
  } else if (count == 3) {
    u8g2.drawStr(37, 6, "2"); count++;
  } else if (count == 4) {
    u8g2.drawStr(37, 6, "3"); count++;
  } else if (count == 5) {
    u8g2.drawStr(37, 6, "4"); count++;
  } else if (count >= 6) {
    u8g2.drawStr(37, 6, "5");
    switch (SOC) {
      case 0 ... 20:   count = 1; break;
      case 21 ... 40:  count = 2; break;
      case 41 ... 60:  count = 3; break;
      case 61 ... 80:  count = 4; break;
      case 81 ... 100: count = 5; break;
    }
  }
  u8g2.sendBuffer();
}

void smlICON(const char *message) {
  u8g2.clearBuffer();     // clear the internal memory

  u8g2.setFont(u8g2_font_open_iconic_embedded_4x_t);
  u8g2.drawStr(u8g2.getUTF8Width(message) / 2 + 32, 0, message);

  u8g2.sendBuffer();
}


void printDirectory(File dir, int numTabs) {

  while (true) {
    File entry =  dir.openNextFile();

    if (!entry) {      // no more files
      break;
    }

    for (uint8_t i = 0; i < numTabs; i++) {
      tft.println('\t');
    }

    filename = entry.name();

    if (filename == LogFile) {
      tft.setTextColor(TFT_MIDDLEGREEN, TFT_BLACK);
    } else {
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
    }

    if (entry.isDirectory()) {       // files have sizes, directories do not
      tft.print("/");
      if (filename.substring(0) == "." || filename.substring(1) == ".") {
        printDirectory(entry, numTabs + 1);
      } else {
        tft.println(filename);
      }
    } else {
      if (filename.substring(1) == "_" || filename.substring(2) == "_" || filename.substring(1) == "." || filename.substring(2) == ".") {
      } else {
        tft.print(filename); tft.print(" ");

        tft.setTextColor(TFT_LIGHTGREY);
        if (entry.size() / 1024 > 1024) {
          tft.print(entry.size() / 1024 / 1024, DEC);
          tft.println("mb");
        } else {
          tft.print(entry.size() / 1024, DEC);
          tft.println("kb");
        }
      }
    }
    entry.close();
    // numTabs = 0;
  }
}

void readFile(fs::FS & fs, const char * path) {
  file = fs.open(path);
  if (!file) {
    return;
  }
  while (file.available()) {
    tft.print(file.read());
  }
  file.close();
}


void appendFile(fs::FS & fs, const char * path, const char * message) {
  //Serial.printf("Appending to file: %s\n", path);

  file = fs.open(path, FILE_APPEND);
  if (!file) {
    SDpresent = false;
    loggingActive = false;
    return;
  }
  file.print(message);//  Message appended
  file.close();
}



void readLogFile(fs::FS & fs, const char * path) {
  file = fs.open(path);
  if (!file) {
    SDpresent = false;
    loggingActive = false;
    putPersistentBool("loggingActive", loggingActive);
    return;
  } else {

    idx0 = 1;
    idx1 = 1;
    idx2 = 1;
    idx3 = 1;
    idx4 = 1;
//    idx5 = 1;
//    idx6 = 1;
//    idx7 = 1;
//    idx8 = 1;
//    idx9 = 1;
//    idx10 = 1;
//    idx11 = 1;
//    idx12 = 1;
//    idx13 = 1;
//    idx14 = 1;
    i = 0;
    x = 0;
    idx = 0;

    while (file.available() /*&& file.peek() != '\n'*/ && idx <= 255) {  // peek returns the next character without incrementing the read index
      recall[idx] = file.read();
      //      Serial.print(recall[idx]);

      if (recall[idx] == ',') {
        i++;
      }

      if (idx == 0) {   // TIME
        if (recall[idx + 1] != '0') {
          recallTIME = recall[idx + 1];
        }
        if (recall[idx + 2] != '0') {
          recallTIME = recall[idx + 2];
        } else {
          recallTIME = '0';
        }
      }

      if (i == 1) {      // SOC
        recallSOC = recall[idx + 3];
        if (!recallSOC < 10) recallSOC += recall[idx + 4];
      }
      if (i == 3) {    // AMPS
        recallAMP = recall[idx + 3];
        recallAMP += recall[idx + 4];
        recallAMP += recall[idx + 5];
        recallAMP += recall[idx + 6];
      }

      if (recall[13] == '.') {
        if (i == 13) {       // SCD
          recallSCD = recall[idx + 3];
          if (recallSCD.toInt() != 0) {
            recallSCD += recall[idx + 4];
            if (recall[idx + 5] != ',') recallSCD += recall[idx + 5];
            if (recall[idx + 6] != ',') recallSCD += recall[idx + 6];
          }
        }
        if (i == 14) {   // Temp1
          recallTemp1 = recall[idx + 3];
          if (recallTemp1.toInt() != 0) {
            recallTemp1 += recall[idx + 4];
            recallTemp1 += recall[idx + 5];
            recallTemp1 += recall[idx + 6];
            recallTemp1 += recall[idx + 7];
          }
        }
        if (i == 15) {    // RH
          recallRH = recall[idx + 3];
          if (recallRH.toInt() != 0) {
            recallRH += recall[idx + 4];
            recallRH += recall[idx + 5];
            recallRH += recall[idx + 6];
            recallRH += recall[idx + 7];
          }
        }
        if (i == 16) {    // TVOCccs
          recallCCSc = recall[idx + 3];
          if (recallCCSc.toInt() != 0) {
            recallCCSc += recall[idx + 4];
            recallCCSc += recall[idx + 5];
            if (recall[idx + 6] != ',') recallCCSc += recall[idx + 6];
            if (recall[idx + 7] != ',') recallCCSc += recall[idx + 7];
          }
        }
        if (i == 17) {   // CO2ccs
          recallCCSt = recall[idx + 3];
          if (recallCCSt.toInt() != 0) {
            recallCCSt += recall[idx + 4];
            recallCCSt += recall[idx + 5];
            if (recall[idx + 6] != ',') recallCCSt += recall[idx + 6];
            if (recall[idx + 7] != ',') recallCCSt += recall[idx + 7];
          }
        }
        if (i == 20) {
          recallUV = recall[idx + 3];
          if (recallUV.toInt() != 0) {
            recallUV += recall[idx + 4];
          }
        }


        recallSampleCollect(recallTIME);

      }

      idx++;
      if (file.peek() == 10) { // Line Ending - 10
        i = 0;
        idx = 0;
        /* if (recall[13] == '.') {

            Serial.println();
            Serial.println("TME: "    + recallTIME);
            Serial.println("SOC: "    + recallSOC  + "%");
            Serial.println("AMP: "    + recallAMP  + "A");
            Serial.println("CO2: "    + recallSCD  + " ppm");
            Serial.println("Tmp: "    + recallTemp1 + "°");
            Serial.println("RH%: "    + recallRH   + "%");
            Serial.println("CO2c: "   + recallCCSc + " ppm");
            Serial.print("TVOC: "     + recallCCSt + " ppb");

          } */
      }
    }

    file.close();

    recallSampleDivide();

    Serial.println();
    Serial.println("TME: 0");
    Serial.println("SOC: "    + String(SOC24array[0]));
    Serial.println("AMP: "    + String(AMP24array[0]));
    Serial.println("CO2: "    + String(SCD24array[0]));
    Serial.println("Tmp: "    + String(TMP124array[0]));
    Serial.println("RH%: "    + String(RH24array[0]));
    Serial.println("CO2c: "   + String(CCSc24array[0]));
    Serial.println("TVOC: "     + String(CCSt24array[0]));
    Serial.println("TME: 1");
    Serial.println("SOC: "    + String(SOC24array[1]));
    Serial.println("AMP: "    + String(AMP24array[1]));
    Serial.println("CO2: "    + String(SCD24array[1]));
    Serial.println("Tmp: "    + String(TMP124array[1]));
    Serial.println("RH%: "    + String(RH24array[1]));
    Serial.println("CO2c: "   + String(CCSc24array[1]));
    Serial.println("TVOC: "     + String(CCSt24array[1]));
  }
}

void recallSampleCollect(String reHour) {
  int temp = reHour.toInt();
  switch (temp) {
    case 0: idx0++;
    case 1: idx1++;
    case 2: idx2++;
    case 3: idx3++;
    case 4: idx4++;
//     case 5: idx5++;
//     case 6: idx6++;
//     case 7: idx7++;
//     case 8: idx8++;
//     case 9: idx9++;
//     case 10: idx10++;
//     case 11: idx11++;
//     case 12: idx12++;
//     case 13: idx13++;
//     case 14: idx14++;
  }
  SOC24array[temp]  += recallSOC.toInt();
  AMP24array[temp]  += recallAMP.toDouble();
  SCD24array[temp]  += recallSCD.toInt();
  TMP124array[temp] += recallTemp1.toDouble();
  RH24array[temp]   += recallRH.toDouble();
  CCSc24array[temp] += recallCCSc.toInt();
  CCSt24array[temp] += recallCCSt.toInt();
}

void recallSampleDivide() {

  SOC24array[0]  /= idx0;
  AMP24array[0]  /= idx0;
  SCD24array[0]  /= idx0;
  TMP124array[0] /= idx0;
  RH24array[0]   /= idx0;
  CCSc24array[0] /= idx0;
  CCSt24array[0] /= idx0;

  SOC24array[1]  /= idx1;
  AMP24array[1]  /= idx1;
  SCD24array[1]  /= idx1;
  TMP124array[1] /= idx1;
  RH24array[1]   /= idx1;
  CCSc24array[1] /= idx1;
  CCSt24array[1] /= idx1;

  SOC24array[2]  /= idx2;
  AMP24array[2]  /= idx2;
  SCD24array[2]  /= idx2;
  TMP124array[2] /= idx2;
  RH24array[2]   /= idx2;
  CCSc24array[2] /= idx2;
  CCSt24array[2] /= idx2;

  SOC24array[3]  /= idx3;
  AMP24array[3]  /= idx3;
  SCD24array[3]  /= idx3;
  TMP124array[3] /= idx3;
  RH24array[3]   /= idx3;
  CCSc24array[3] /= idx3;
  CCSt24array[3] /= idx3;

  SOC24array[4]  /= idx4;
  AMP24array[4]  /= idx4;
  SCD24array[4]  /= idx4;
  TMP124array[4] /= idx4;
  RH24array[4]   /= idx4;
  CCSc24array[4] /= idx4;
  CCSt24array[4] /= idx4;
}

void drawBmp(fs::FS & fs, const char *filename, int16_t x, int16_t y) {

  if ((x >= TFT_WIDTH) || (y >= TFT_WIDTH)) return;

  bmpFS = fs.open(filename, "r");

  if (!bmpFS)
  {
    tft.print("no bmp");
    SDpresent = false;
    loggingActive = false;
    return;
  }

  if (read16(bmpFS) == 0x4D42) {
    read32(bmpFS);
    read32(bmpFS);
    seekOffset = read32(bmpFS);
    read32(bmpFS);
    w = read32(bmpFS);
    h = read32(bmpFS);

    if ((read16(bmpFS) == 1) && (read16(bmpFS) == 24) && (read32(bmpFS) == 0)) {
      y += h - 1;

      tft.setSwapBytes(true);
      bmpFS.seek(seekOffset);

      padding = (4 - ((w * 3) & 3)) & 3;
      uint8_t lineBuffer[w * 3];

      for (row = 0; row < h; row++) {
        bmpFS.read(lineBuffer, sizeof(lineBuffer));
        uint8_t*  bptr = lineBuffer;
        uint16_t* tptr = (uint16_t*)lineBuffer;
        // Convert 24 to 16 bit colours
        for (col = 0; col < w; col++)
        {
          b = *bptr++;
          g = *bptr++;
          r = *bptr++;
          *tptr++ = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
        }
        // Read any line padding
        if (padding) bmpFS.read((uint8_t*)tptr, padding);
        // Push the pixel row to screen, pushImage will crop the line if needed
        tft.pushImage(x, y--, w, 1, (uint16_t*)lineBuffer);
      }
    } else {
      //      tft.println("");
      SDpresent = false;
      loggingActive = false;
    }
  }
  bmpFS.close();
}

void putPersistentBool(const char* path, bool state) {
  //  path.toCharArray(charArr, 12);
  preferences.begin("my - app", false);
  preferences.putBool(path, state); // store to Preferences
  preferences.end();
}

void print_wakeup_reason() {

  tft.setTextColor(TFT_INDIA, TFT_BLACK);
  tft.setTextDatum(TL_DATUM);
  tft.setTextPadding(TFT_WIDTH);
  tft.setTextSize(1);

  SDloghead = "";
  alarmEnable = true;

  if (htmlRestart || deleteLog) {
    SDloghead += SDLOGHEAD;
    SDloghead += RTClog;
    if (deleteLog) SDloghead += "Log Deleted,";
    if (htmlRestart) {
      deepSleepActive = false;
      TFTon();
      SDloghead += "htmlRestart, #";
      SDloghead += String(counter);
      SDloghead += ", ";
      SDloghead += String(Revision);
      htmlRestart = 0;
      putPersistentBool("htmlRestart", htmlRestart);
      tft.drawString("htmlRestart", 0, 0, 1);
    }
  } else {

    esp_sleep_wakeup_cause_t wakeup_reason;
    wakeup_reason = esp_sleep_get_wakeup_cause();
    rtc_gpio_force_hold_dis_all();
    u8g2.sleepOff();

    switch (wakeup_reason)
    {
      case ESP_SLEEP_WAKEUP_EXT0 : tft.drawString("Wakeup by RTC_IO", 0, 0, 1);
        deepSleepActive = false;
        tftBKL = 255;
        TFTon();
        SDloghead += RTClog;
        SDloghead += "RTC_IO, #";
        SDloghead += String(counter);
        SDloghead += ", ";
        SDloghead += String(Revision);
        tft.drawString("RTC_IO", 0, 0, 1);
        break;
      case ESP_SLEEP_WAKEUP_EXT1 : tft.drawString("Wakeup by external signal RTC_CNTL", 0, 0, 1);
        deepSleepActive = true;
        tftBKL = 255;
        TFTon();
        SDloghead += RTClog;
        SDloghead += "RTC_CTRL, #";
        SDloghead += String(counter);
        SDloghead += ", ";
        SDloghead += String(Revision);
        tft.drawString("RTC_CTRL", 0, 0, 1);
        break;
      case ESP_SLEEP_WAKEUP_TIMER : tft.drawString("Wakeup by timer", 0, 0, 1);
        deepSleepActive = true;
        tftBKL = 0;
        TFToff();
        SDloghead += SDLOGHEAD;
        SDloghead += RTClog;
        SDloghead += "RTC_TIMER, #";
        SDloghead += String(counter);
        SDloghead += ", ";
        SDloghead += String(Revision);
        tft.drawString("RTC_TIMER", 0, 0, 1);
        break;
      case ESP_SLEEP_WAKEUP_TOUCHPAD : tft.drawString("Wakeup by touchpad", 0, 0, 1);
        deepSleepActive = true;
        tftBKL = 255;
        TFTon();
        SDloghead += SDLOGHEAD;
        SDloghead += RTClog;
        SDloghead += "RTC_TOUCHPAD, #";
        SDloghead += String(counter);
        SDloghead += ", ";
        SDloghead += String(Revision);
        tft.drawString("RTC_TOUCHPAD", 0, 0, 1);
        break;
      case ESP_SLEEP_WAKEUP_ULP : tft.drawString("Wakeup by ULP program", 0, 0, 1);
        deepSleepActive = true;
        tftBKL = 0;
        TFToff();
        SDloghead += SDLOGHEAD;
        SDloghead += RTClog;
        SDloghead += "RTC_ULP, #";
        SDloghead += String(counter);
        SDloghead += ", ";
        SDloghead += String(Revision);
        tft.drawString("RTC_ULP", 0, 0, 1);
        break;
      default:
        deepSleepActive = false;
        tftBKL = 255;
        TFTon();
        SDloghead += SDLOGHEAD;
        SDloghead += RTClog;
        SDloghead += "RESTART, #";
        SDloghead += String(counter);
        SDloghead += ", ";
        SDloghead += String(Revision);
        if (rtcLostPower) {                           // RTC reset reason
          SDloghead += ", Hard Reset, ";
          tft.drawString("Hard Reset ", 0, 0, 1);
        } else if (!rtcLostPower) {
          SDloghead += ", Soft Reset, ";
          tft.drawString("Soft Reset ", 0, 0, 1);
        }
        break;
    }
  }
  SDloghead += "WiFi: " +   String(WiFi.SSID()) + " - " + String(translate_wl_status(WiFi.status())) + ", ";
  SDloghead += "CPU: "  +   String(getCpuFrequencyMhz()) + "Mhz, ";
  SDloghead += "I2C: "  +   String(Wire.getClock()) + "MHz, ";
  SDloghead += "ESP: "  +   String(esp_get_idf_version());
  SDloghead += "\n";
  if (SDpresent) appendFile(SD, LogFile, SDloghead.c_str());
}


void verbose_print_reset_reason(RESET_REASON reason)
{
  switch (reason)
  {
    case 1  : tft.print ("Vbat power on reset"); break;
    case 3  : tft.print ("Software reset digital core"); break;
    case 4  : tft.print ("Legacy watch dog reset digital core"); break;
    case 5  : tft.print ("Deep Sleep reset digital core"); break;
    case 6  : tft.print ("SLC module, reset digital core"); break;
    case 7  : tft.print ("Group0 Watch dog reset digital core"); break;
    case 8  : tft.print ("Group1 Watch dog reset digital core"); break;
    case 9  : tft.print ("RTC Watch dog Reset digital core"); break;
    case 10 : tft.print ("Instrusion tested to reset CPU"); break;
    case 11 : tft.print ("Time Group reset CPU"); break;
    case 12 : tft.print ("Software Reset / Button"); break;
    case 13 : tft.print ("RTC Watch dog Reset CPU"); break;
    case 14 : tft.print ("for APP CPU, reseted by PRO CPU"); break;
    case 15 : tft.print ("Voltage Brownout caused Reset"); break;
    case 16 : tft.print ("RTC Watch dog reset digital core + rtc module"); break;
    default : tft.print ("NO_IDEA");
  }
}


const char* translateEncryptionType(wifi_auth_mode_t encryptionType) {

  switch (encryptionType) {
    case WIFI_AUTH_OPEN:            return "Open";
    case WIFI_AUTH_WEP:             return "WEP";
    case WIFI_AUTH_WPA_PSK:         return "WPA1";
    case WIFI_AUTH_WPA2_PSK:        return "WPA2";
    case WIFI_AUTH_WPA_WPA2_PSK:    return "WPA1+2";
    case WIFI_AUTH_WPA2_ENTERPRISE: return "WPA2_E";
  }
}

const char* translate_wl_status(wl_status_t status) {
  switch (status) {
    case WL_NO_SHIELD:       return "NO_SHIELD";
    case WL_IDLE_STATUS:     return "IDLE_STATUS";
    case WL_NO_SSID_AVAIL:   return "NO_SSID";
    case WL_SCAN_COMPLETED:  return "SCAN_COMPLETE";
    case WL_CONNECTED:       return "CONNECTED";
    case WL_CONNECT_FAILED:  return "CONNECT_FAILED";
    case WL_CONNECTION_LOST: return "CONNECT_LOST";
    case WL_DISCONNECTED:    return "DISCONNECTED";
  }
}

uint16_t read16(fs::File & f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}


uint32_t read32(fs::File & f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}

double doDewPoint(double celsius, double humidity)  {

  temp = (Da * celsius) / (Db + celsius) + log(humidity * 0.01);
  dewPoint = (Db * temp) / (Da - temp);

  return dewPoint;
}

// Thermal Cam Stuff
void drawpixels(float * p, uint8_t rows, uint8_t cols, uint8_t boxWidth, uint8_t boxHeight) {

  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols; x++) {
      val = get_point(p, rows, cols, x, y);
      if (val >= MAXTEMP) colorTemp = MAXTEMP;
      else if (val <= MINTEMP) colorTemp = MINTEMP;
      else colorTemp = val;

      colorTemp = constrain(map(colorTemp, MINTEMP, MAXTEMP, 0, 255), 0, 255);
      tft.fillRect(boxWidth * x, boxHeight * y, boxWidth, boxHeight, camColors[colorTemp]);  // fast blocky

      //      colorTemp = map(colorTemp, MINTEMP, MAXTEMP, 18447, 63488);          // 18447 , 63488  red blue fast smooth
      //      tft.fillRect(boxWidth * x, boxHeight * y, boxWidth, boxHeight, colorTemp);

      //      colorTemp = constrain(map(colorTemp, MINTEMP, MAXTEMP, 0, 255), 0, 255);
      //      tft.fillRect(boxWidth * x, boxHeight * y, boxWidth, boxHeight, GetColor(colorTemp));  // slow blocky
    }
  }
}

float get_point(float * p, uint8_t rows, uint8_t cols, int8_t x, int8_t y) {
  if (x < 0)
    x = 0;
  if (y < 0)
    y = 0;
  if (x >= cols)
    x = cols - 1;
  if (y >= rows)
    y = rows - 1;
  return p[y * cols + x];
}

void set_point(float * p, uint8_t rows, uint8_t cols, int8_t x, int8_t y, float f) {
  if ((x < 0) || (x >= cols))
    return;
  if ((y < 0) || (y >= rows))
    return;
  p[y * cols + x] = f;
}

// src is a grid src_rows * src_cols
// dest is a pre-allocated grid, dest_rows*dest_cols
void interpolate_image(float * src, uint8_t src_rows, uint8_t src_cols, float * dest, uint8_t dest_rows, uint8_t dest_cols) {
  float mu_x = (src_cols - 1.0) / (dest_cols - 1.0);
  float mu_y = (src_rows - 1.0) / (dest_rows - 1.0);

  for (uint8_t y_idx = 0; y_idx < dest_rows; y_idx++) {
    for (uint8_t x_idx = 0; x_idx < dest_cols; x_idx++) {
      x = x_idx * mu_x;
      y = y_idx * mu_y;
      get_adjacents_2d(src, adj_2d, src_rows, src_cols, x, y);
      frac_x = x - (int)x;   // we only need the ~delta~ between the points
      frac_y = y - (int)y;   // we only need the ~delta~ between the points
      out = bicubicInterpolate(adj_2d, frac_x, frac_y);
      // Serial.print("\tInterp: "); Serial.println(out);
      set_point(dest, dest_rows, dest_cols, x_idx, y_idx, out);
    }
  }
}

// p is a list of 4 points, 2 to the left, 2 to the right
float cubicInterpolate(float p[], float x) {
  float r = p[1] + (0.5 * x *
                    (p[2] - p[0] + x *
                     (2.0 * p[0] - 5.0 * p[1] + 4.0 * p[2] - p[3] + x *
                      (3.0 * (p[1] - p[2]) + p[3] - p[0]))));
  return r;
}

// p is a 16-point 4x4 array of the 2 rows & columns left/right/above/below
float bicubicInterpolate(float p[], float x, float y) {

  arr[0] = cubicInterpolate(p + 0, x);
  arr[1] = cubicInterpolate(p + 4, x);
  arr[2] = cubicInterpolate(p + 8, x);
  arr[3] = cubicInterpolate(p + 12, x);
  return cubicInterpolate(arr, y);
}

// src is rows*cols and dest is a 4-point array passed in already allocated!
void get_adjacents_1d(float * src, float * dest, uint8_t rows, uint8_t cols, int8_t x, int8_t y) {

  dest[0] = get_point(src, rows, cols, x - 1, y);  // pick two items to the left
  dest[1] = get_point(src, rows, cols, x - 2, y);
  dest[2] = get_point(src, rows, cols, x + 1, y);  // pick two items to the right
  dest[3] = get_point(src, rows, cols, x + 2, y);
}

// src is rows*cols and dest is a 16-point array passed in already allocated!
void get_adjacents_2d(float * src, float * dest, uint8_t rows, uint8_t cols, int8_t x, int8_t y) {

  for (int8_t delta_y = -1; delta_y < 3; delta_y++) { // -1, 0, 1, 2
    float *row = dest + 4 * (delta_y + 1); // index into each chunk of 4
    for (int8_t delta_x = -1; delta_x < 3; delta_x++) { // -1, 0, 1, 2
      row[delta_x + 1] = get_point(src, rows, cols, x + delta_x, y + delta_y);
    }
  }
}


// UI Stuff:
void menuIcons() {
  drawBmp(SPIFFS, icon3, carX3, 89);
  drawBmp(SPIFFS, icon2, carX2, 89);
  drawBmp(SPIFFS, icon4, carX4, 89);
  drawBmp(SPIFFS, icon1, carX1, 89);
  drawBmp(SPIFFS, icon5, carX5, 89);
}

void createDialScale(int16_t start_angle, int16_t end_angle, int16_t increment) {
  // Create the dial Sprite
  //  dial.setColorDepth(8);       // Size is odd (i.e. 91) so there is a centre pixel at 45,45
  dial.createSprite(70, 70);   // 8bpp requires 91 * 91 = 8281 bytes
  dial.setPivot(35, 35);       // set pivot in middle of dial Sprite
  dial.fillSprite(TFT_TRANSPARENT);           // Fill with transparent colour
  dial.setTextPadding(30);
  dial.setTextDatum(TC_DATUM);
  needle.setPivot(0, 35);        //  Set pivot point x to the Sprite centre and y to marker radius
}

void plotDial(int16_t x, int16_t y, uint16_t a, int32_t bgcolor) {
  // Push a rotated needle Sprite to the dial Sprite, with black as transparent colour
  needle.pushRotated(&dial, a, bgcolor); // dial is the destination Sprit
  dial.drawNumber(AirQI, 30, 23, 2);
  dial.pushSprite(x, y, TFT_TRANSPARENT);
}

void createNeedle(void) {
  needle.setColorDepth(16);
  needle.createSprite(12, 34); // create the needle Sprite 11 pixels wide by 49 high
  // Define needle pivot point
  uint16_t piv_x = needle.width() / 2;   // x pivot of Sprite (middle)
  uint16_t piv_y = needle.height() - 1; // y pivot of Sprite (10 pixels from bottom)
  needle.setPivot(piv_x, piv_y);         // Set pivot point in this Sprite
  // Keep needle tip 1 pixel inside dial circle to avoid leaving stray pixels
  needle.fillCircle(piv_x, 5, 3, TFT_WHITE); // change y for moving sprite in /out
}

void createDialScale2(int16_t start_angle, int16_t end_angle, int16_t increment) {
  // Create the dial Sprite
  //  dial2.setColorDepth(8);       // Size is odd (i.e. 91) so there is a centre pixel at 45,45
  dial2.createSprite(70, 70);   // 8bpp requires 91 * 91 = 8281 bytes
  dial2.setPivot(35, 35);       // set pivot in middle of dial Sprite
  dial2.fillSprite(TFT_TRANSPARENT);           // Fill with transparent colour
  dial2.setTextPadding(22);
  dial2.setTextDatum(TC_DATUM);
  needle2.setPivot(0, 35);        //  Set pivot point x to the Sprite centre and y to marker radius
}

void plotDial2(int16_t x, int16_t y, uint16_t a, int32_t bgcolor) {
  // Push a rotated needle Sprite to the dial Sprite, with black as transparent colour
  needle2.pushRotated(&dial2, a, bgcolor); // dial is the destination Sprit
  dial2.drawNumber(UVI, 43, 22, 2);
  dial2.pushSprite(x, y, TFT_TRANSPARENT);
}

void createNeedle2(void) {
  needle2.setColorDepth(16);
  needle2.createSprite(12, 34); // create the needle Sprite 11 pixels wide by 49 high
  // Define needle pivot point
  uint16_t piv_x = needle2.width() / 2;   // x pivot of Sprite (middle)
  uint16_t piv_y = needle2.height() - 1; // y pivot of Sprite (10 pixels from bottom)
  needle2.setPivot(piv_x, piv_y);         // Set pivot point in this Sprite
  // Keep needle tip 1 pixel inside dial circle to avoid leaving stray pixels
  needle2.fillCircle(piv_x, 5, 3, TFT_WHITE); // change y for moving sprite in /out
}


void createDialScale3(int16_t start_angle, int16_t end_angle, int16_t increment) {
  // Create the dial Sprite
  //  dial2.setColorDepth(8);       // Size is odd (i.e. 91) so there is a centre pixel at 45,45
  dial3.createSprite(70, 70);   // 8bpp requires 91 * 91 = 8281 bytes
  dial3.setPivot(35, 35);       // set pivot in middle of dial Sprite
  dial3.fillSprite(TFT_TRANSPARENT);           // Fill with transparent colour
  dial3.setTextPadding(22);
  dial3.setTextDatum(TC_DATUM);
  needle3.setPivot(0, 35);        //  Set pivot point x to the Sprite centre and y to marker radius
}

void plotDial3(int16_t x, int16_t y, uint16_t a, int32_t bgcolor) {
  // Push a rotated needle Sprite to the dial Sprite, with black as transparent colour
  needle3.pushRotated(&dial3, a, bgcolor); // dial is the destination Sprit
  dial3.drawString(String(tempBME, 1) + "C", 36, 32, 2);
  dial3.pushSprite(x, y, TFT_TRANSPARENT);
}

void createNeedle3(void) {
  needle3.setColorDepth(16);
  needle3.createSprite(12, 34); // create the needle Sprite 11 pixels wide by 49 high
  // Define needle pivot point
  uint16_t piv_x = needle3.width() / 2;   // x pivot of Sprite (middle)
  uint16_t piv_y = needle3.height() - 1; // y pivot of Sprite (10 pixels from bottom)
  needle3.setPivot(piv_x, piv_y);         // Set pivot point in this Sprite
  // Keep needle tip 1 pixel inside dial circle to avoid leaving stray pixels
  needle3.fillCircle(piv_x, 5, 3, TFT_WHITE); // change y for moving sprite in /out
}


uint16_t uviColor() {
  switch (UVI) {
    case 1:
      return TFT_MIDDLEGREEN;
      break;
    case 2 ... 4:
      return TFT_YELLOW;
      break;
    case 5 ... 7:
      return TFT_ORANGE;
      break;
    case 8 ... 10:
      return TFT_INDIA;
      break;
    case 11 ... 15:
      return TFT_RED;
      break;
    default:
      return TFT_WHITE;
      break;
  }
}

/*    Other Method to display 565 color space for AMG8833
  uint16_t GetColor(float val) {

  //    https://github.com/KrisKasprzak
  //
  //    pass in value and figure out R G B
  //    several published ways to do this I basically graphed R G B and developed simple linear equations
  //    again a 5-6-5 color display will not need accurate temp to R G B color calculation
  //
  //    equations based on
  //    http://web-tech.ga-usa.com/2012/05/creating-a-custom-hot-to-cold-temperature-color-gradient-for-use-with-rrdtool/index.html


  Getabcd();


  redAMG = constrain(255.0 / (cc - bb) * val - ((bb * 255.0) / (cc - bb)), 0, 255);

  if ((val > MINTEMP) & (val < aa)) {
    greenAMG = constrain(255.0 / (aa - MINTEMP) * val - (255.0 * MINTEMP) / (aa - MINTEMP), 0, 255);
  }
  else if ((val >= aa) & (val <= cc)) {
    greenAMG = 255;
  }
  else if (val > cc) {
    greenAMG = constrain(255.0 / (cc - dd) * val - (dd * 255.0) / (cc - dd), 0, 255);
  }
  else if ((val > dd) | (val < aa)) {
    greenAMG = 0;
  }

  if (val <= bb) {
    blueAMG = constrain(255.0 / (aa - bb) * val - (255.0 * bb) / (aa - bb), 0, 255);
  }
  else if ((val > bb) & (val <= dd)) {
    blueAMG = 0;
  }
  else if (val > dd) {
    blueAMG = constrain(240.0 / (MAXTEMP - dd) * val - (dd * 240.0) / (MAXTEMP - dd), 0, 240);
  }

  // use the displays color mapping function to get 5-6-5 color palet (R=5 bits, G=6 bits, B-5 bits)
  return tft.color565(redAMG, greenAMG, blueAMG);
  //  return colorTemp = ((redAMG & 0xF8) << 8) | ((greenAMG & 0xFC) << 3) | (blueAMG >> 3);
  }

  // function to get the cutoff points in the temp vs RGB graph
  void Getabcd() {
  aa = MAXTEMP * 0.2121; // MINTEMP + (MAXTEMP - MINTEMP)
  bb = MAXTEMP * 0.3182;
  cc = MAXTEMP * 0.4242;
  dd = MAXTEMP * 0.8182;
  }
*/

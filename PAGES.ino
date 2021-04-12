#include <pgmspace.h>

void page0() {

  if (pageCount == 0) {
    tft.fillScreen(TFT_BLACK);
    if (SDpresent) {
      drawBmp("/UI/HEX240.bmp", 0, 0);   // 24bit
      //  tft.pushImage(0, 0, 240, 240, HEX240);
    }

    tft.drawLine(0, 17, 89, 17, TFT_MIDDLEGREY);
    tft.drawLine(150, 17, TFTwidth, 17, TFT_MIDDLEGREY);

    tft.drawLine(0, 223, 89, 223, TFT_MIDDLEGREY);
    tft.drawLine(150, 223, TFTwidth, 223, TFT_MIDDLEGREY);

    spr.setTextPadding(70);
    spr.setTextDatum(TL_DATUM);
    spr.setColorDepth(10);      // Create an 8bpp Sprite of 60x30 pixels
    spr.setTextSize(2);

    spr2.setTextPadding(65);
    spr2.setTextDatum(TL_DATUM);
    spr2.setColorDepth(10);
    spr2.setTextSize(2);

    tft.setPivot(69, 230);
    spr.createSprite(45, 18);  // 8bpp requires 64 * 30 = 1920 bytes
    spr.setPivot(32, 35);      //32,55 Set pivot relative to top left corner of Sprite
    spr.fillSprite(TFT_WHITE);
    spr.setTextColor(TFT_DARKGREY);        // Green text
    spr.drawString("CO2", 0, 0, 1); // Plot text, font 4, in Sprite at 30, 15
    spr.pushRotated(30);

    tft.setPivot(203, 235);
    spr.createSprite(45, 22);  // 8bpp requires 64 * 30 = 1920 bytes
    spr.setPivot(32, 55);      //32,55 Set pivot relative to top left corner of Sprite
    spr.fillSprite(TFT_WHITE);
    spr.setTextColor(TFT_DARKGREY);        // Green text
    spr.drawString("tVOC", 0, 0, 1); // Plot text, font 4, in Sprite at 30, 15
    spr.pushRotated(-30);

    tft.setPivot(153, 87);
    spr2.createSprite(45, 22);  // 8bpp requires 64 * 30 = 1920 bytes
    spr2.setPivot(32, 55);      //32,55 Set pivot relative to top left corner of Sprite
    spr2.fillSprite(TFT_WHITE);
    spr2.setTextColor(TFT_DARKGREY);        // Green text
    spr2.drawString("RH%", 0, 0, 1); // Plot text, font 4, in Sprite at 30, 15
    spr2.pushRotated(30);

    tft.setPivot(112, 72);
    spr2.createSprite(45, 22);  // 8bpp requires 64 * 30 = 1920 bytes
    spr2.setPivot(32, 55);     //32,55 Set pivot relative to top left corner of Sprite
    spr2.fillSprite(TFT_WHITE);
    spr2.setTextColor(TFT_DARKGREY);        // Green text
    spr2.drawString("TEMP", 0, 0, 1); // Plot text, font 4, in Sprite at 30, 15
    spr2.pushRotated(-30);

    tft.setTextColor(TFT_CYAN);
    tft.setTextSize(1);
    tft.setTextDatum(BL_DATUM);
    tft.drawString("v" + String(Revision), 210, 240, 2);

    while (pageCount == 0) {
      wifiPrint();
      everyXsec();
      checkforAlarms(); // Alarms and stuff that runs every X sec  - everyXsec();
      checkScreenState();

      if (sleepTimer < TimeoutT + TimeoutT2 && pageCount == 0 && !criticalAlarm) {

        tft.setTextSize(1);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextPadding(20);
        tft.setTextDatum(TC_DATUM);

        tft.drawString(String(alt) + "m", 120, 8, 2);

        spr.setTextSize(1);
        spr2.setTextSize(1);

        tft.setPivot(67, 223);
        spr.createSprite(80, 22);  // 8bpp requires 64 * 30 = 1920 bytes
        spr.setPivot(32, 55);      //32,55 Set pivot relative to top left corner of Sprite
        spr.fillSprite(TFT_BLACK);
        spr.setTextColor(TFT_ORANGE);        // Green text
        spr.drawNumber(CO2, 0, 0, 4); // Plot text, font 4, in Sprite at 30, 15
        spr.pushRotated(30, 8);


        tft.setPivot(193, 208);
        spr.createSprite(55, 22);  // 8bpp requires 64 * 30 = 1920 bytes
        spr.setPivot(32, 55);      //32,55 Set pivot relative to top left corner of Sprite
        spr.fillSprite(TFT_BLACK);
        spr.setTextColor(TFT_RED);        // Green text
        spr.drawNumber(TVOC, 0, 0, 4); // Plot text, font 4, in Sprite at 30, 15
        spr.pushRotated(-30, 12);

        tft.setPivot(122, 89);
        spr2.createSprite(40, 22);  // 8bpp requires 64 * 30 = 1920 bytes
        spr2.setPivot(32, 55);      //32,55 Set pivot relative to top left corner of Sprite
        spr2.fillSprite(TFT_BLACK);
        //    spr2.setTextColor(TFT_BLUE);        // Green text
        if (tempBME < 0) {
          spr.setTextColor(TFT_RED);
        }
        if (tempBME < 15 && tempBME > 0) {
          spr.setTextColor(TFT_PURPLE);
        }
        if (tempBME > 28 && tempBME < 34) {
          spr.setTextColor(TFT_CYAN);
        }
        if (tempBME > 35) {
          spr.setTextColor(TFT_BLUE);
        }
        int BMEHDC = (tempHDC + tempBME) / 2; // combined Temp Readings
        spr2.drawNumber(BMEHDC, 0, 0, 4);
        spr2.pushRotated(-30);

        tft.setPivot(149, 107);
        spr2.createSprite(40, 22);  // 8bpp requires 64 * 30 = 1920 bytes
        spr2.setPivot(32, 55);      //32,55 Set pivot relative to top left corner of Sprite
        spr2.fillSprite(TFT_BLACK);
        spr2.setTextColor(TFT_ORANGE);        // Green text
        spr2.drawNumber(RH, 0, 0, 4); // RH
        spr2.pushRotated(30);
      }

      if (SDpresent) {
        tft.setTextColor(TFT_BLACK);
      } else {
        tft.setTextColor(TFT_MIDDLEGREY);
      }
      tft.setTextDatum(BC_DATUM);
      tft.drawNumber(counter, 120, 232, 2); // print


      if (sleepTimer < TimeoutT + TimeoutT2 && pageCount == 0) {
        tft.setTextSize(1);
        tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
        tft.setCursor(162, 4);
        loopEndT = millis() - currentTime;
        tft.print(1000 / loopEndT); tft.print("fps ");
      }
    }
  }
  if (pageCount == MenuPages); page8();
}

void page1() {

  if (pageCount == 1) {

    tft.fillScreen(TFT_BLACK);
    checkforAlarms();
    printStatusBar();

    if (SDpresent) {
      drawBmp("/UI/tProbes240b.bmp", 0, 0);   // 24bit
      //      tft.pushImage(0, 0, TFTwidth, TFTheight, TProbesB240);
    }
    tft.drawRoundRect(193, 15, 55, 12, 3, TFT_MIDDLEGREY); // (xO, yO, Length, Width, Radius, color)

    tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
    tft.drawRoundRect(167, 102, 64, 93, 5, TFT_LIGHTGREY);
    tft.setTextDatum(TL_DATUM);
    tft.setTextPadding(50);
    tft.setTextSize(2);

    tft.drawLine(134, 31, 161, 52, TFT_WHITE); //t1
    tft.drawLine(161, 48, 161, 57, TFT_WHITE);
    tft.setCursor(170, 46);
    tft.print("AMB");

    tft.drawLine(143, 86, 161, 86, TFT_WHITE);  //t2
    tft.drawLine(161, 81, 161, 91, TFT_WHITE);
    tft.setCursor(170, 78);
    tft.print("BAT");

    tft.drawLine(128, 211, 161, 213, TFT_WHITE); //t3
    tft.drawLine(161, 207, 161, 217, TFT_WHITE);
    tft.setCursor(170, 205);
    tft.print("LED");

    tft.drawLine(112, 40, 78, 51, TFT_WHITE);    //t4
    tft.drawLine(78, 46, 78, 56, TFT_WHITE);
    tft.setCursor(38, 45);
    tft.print("ESP");

    tft.drawLine(111, 116, 78, 115, TFT_WHITE);  //t5
    tft.drawLine(78, 110, 78, 120, TFT_WHITE);
    tft.setCursor(38, 108);
    tft.print("PWR");

    tft.drawLine(96, 163, 78, 163, TFT_WHITE);  //t6
    tft.drawLine(78, 158, 78, 168, TFT_WHITE);
    tft.setCursor(38, 157);
    tft.print("BAT");

    tft.drawLine(78, 207, 101, 207, TFT_WHITE); //t7
    tft.drawLine(78, 202, 78, 212, TFT_WHITE);
    tft.setCursor(38, 200);
    tft.print("BUS");

    while (pageCount == 1) {
      currentTime = millis();
      wifiPrint();
      everyXsec();
      checkforAlarms();
      checkScreenState();

      tft.setTextDatum(TL_DATUM);
      tft.setTextSize(2);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      if (Volts < lowVoltAlarm || Volts > highVoltAlarm) tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.drawString(String(Volts), 176, 110, 1);

      tft.setTextColor(TFT_GOLD, TFT_BLACK);
      if (Amps > currentTH) tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.setCursor(176, 130);
      tft.drawString(String(Amps), 176, 130, 1);


      if (ta1) {
        tft.setTextColor(TFT_RED, TFT_BLACK);
      } else {
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
      }
      tft.setCursor(212, 46);
      tft.print(t1);

      if (ta2) {
        tft.setTextColor(TFT_RED, TFT_BLACK);
      } else {
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
      }
      tft.setCursor(212, 78);
      tft.print(t2);

      if (ta3) {
        tft.setTextColor(TFT_RED, TFT_BLACK);
      } else {
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
      }
      tft.setCursor(212, 205);
      tft.print(t3);

      if (ta4) {
        tft.setTextColor(TFT_RED, TFT_BLACK);
      } else {
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
      }
      tft.setCursor(3, 45);
      tft.print(t4);

      if (ta5) {
        tft.setTextColor(TFT_RED, TFT_BLACK);
      } else {
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
      }
      tft.setCursor(3, 108);
      tft.print(t5);

      if (ta6) {
        tft.setTextColor(TFT_RED, TFT_BLACK);
      } else {
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
      }
      tft.setCursor(3, 157);
      tft.print(t6);

      if (ta7) {
        tft.setTextColor(TFT_RED, TFT_BLACK);
      } else {
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
      }
      tft.setCursor(3, 200);
      tft.print(t7);

      tft.setTextSize(1);
      tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
      tft.setCursor(200, 17);
      loopEndT = millis() - currentTime;
      tft.print(1000 / loopEndT); tft.print("fps ");
    }
    if (pageCount == 0); page0();
  }
}


void page2() { // Body Temp

  if (pageCount == 2) {

    tft.fillScreen(TFT_BLACK);
    tft.drawRoundRect(193, 15, 55, 12, 3, TFT_MIDDLEGREY); // (xO, yO, Length, Width, Radius, color)
    printStatusBar();
    tft.setTextDatum(MC_DATUM);
    tft.setTextSize(1);
    tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
    tft.drawString("Body", 120, 150, 4);
    tft.drawString("Temperature", 120, 174, 4);
    tft.setTextPadding(70);
    tft.drawRoundRect(30, 70, 180, 60, 5, TFT_MIDDLEGREY);
    tft.drawRoundRect(30, 133, 180, 52, 5, TFT_MIDDLEGREY);
    tft.drawRoundRect(28, 68, 184, 119, 6, TFT_MIDDLEGREY);

    tft.pushImage(99, 15, 42, 42, bTemp42);
    //    tft.pushImage(5, 5, 80, 80, bTemp80);

    while (pageCount == 2) {
      currentTime = millis();
      wifiPrint();
      everyXsec();
      checkforAlarms();
      checkScreenState();

      mlxtemp = mlx.readObjectTempC();

      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      if (mlxtemp > 39) {
        tft.setTextColor(TFT_INDIA, TFT_BLACK);
      }
      tft.setTextSize(1);
      tft.setTextDatum(MC_DATUM);
      tft.drawNumber(mlxtemp, 120, 100, 7);
      tft.drawNumber(/*mlx.readAmbientTempC()*/ mlx.readEmissivityReg(), 47, 58, 2);

      tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
      tft.setCursor(200, 17);
      loopEndT = millis() - currentTime;
      tft.print(1000 / loopEndT); tft.print("fps ");
    }
    if (pageCount == 1) page1();
  }
}

void page3()      // MAX30105 particle
{
  if (pageCount == 3) {

    tft.fillScreen(TFT_BLACK);
    tft.drawRoundRect(193, 15, 55, 12, 3, TFT_MIDDLEGREY); // (xO, yO, Length, Width, Radius, color)

    if (screenState) MAX30105.wakeUp();
    edgeL = 5;
    sleepTimer = 0;
    staticGraphGFX();
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.pushImage(15, 194, 18, 18, HR18);
    tft.setTextSize(1);
    tft.setCursor(185, box1Bottom + 4);
    tft.print(ledBrightness / 5.1); tft.print("mAh");

    while (pageCount == 3) {
      currentTime = millis();
      constHRtop = 93 - irOffset;
      constHRbottom = 90 - irOffset;
      wifiPrint();
      checkforAlarms();
      checkScreenState();

      MAX30105.check();                 //Check the sensor, read up to 3 samples
      if (!screenState) MAX30105.shutDown();

      while (MAX30105.available()) {    //do we have new data
        if (ledB > 0) {
          ledB -= 2;
        }
        ledcWrite(ledChannel1, ledB);
        red = MAX30105.getFIFOIR();     // swap inputs for MH-ET LIVE !! red=IR, IR=red
        ir = MAX30105.getFIFORed();     // getFIFORed output IR data by MAX30102 on MH-ET LIVE breakout board
        i++;
        fred = (double)red;
        fir = (double)ir;
        avered = avered * frate + (double)red * (1.0 - frate);   //average red level by low pass filter
        aveir = aveir * frate + (double)ir * (1.0 - frate);     //average IR level by low pass filter
        sumredrms += (fred - avered) * (fred - avered);         //square sum of alternate component of red level
        sumirrms += (fir - aveir) * (fir - aveir);              //square sum of alternate component of IR level
        if ((i % Num) == 0) {
          double R = (sqrt(sumredrms) / avered) / (sqrt(sumirrms) / aveir);
          SpO2 = -23.3 * (R - 0.4) + 100;                   //http://ww1.microchip.com/downloads/jp/AppNotes/00001525B_JP.pdf
          ESpO2 = FSpO2 * ESpO2 + (1.0 - FSpO2) * SpO2;     //low pass filter
          sumredrms = 0.0; sumirrms = 0.0; i = 0;
          break;
        }
        MAX30105.nextSample();                        //We're finished with this sample so move to next sample
      }

      irValue = MAX30105.getIR();
      if (checkForBeat(irValue) == true) { // we sensed a Beat!
        tone(beep, 500, 5);

        ledB = 40;
        delta = millis() - lastBeat;
        lastBeat = millis();
        beatsPerMinute = 60 / (delta / 1000.0);

        if (beatsPerMinute < 200 && beatsPerMinute > 30) // 255, 30
        {
          rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
          rateSpot %= RATE_SIZE; //Wrap variable

          beatAvg = 0;         //Take average of readings
          for (byte x = 0 ; x < RATE_SIZE ; x++)
            beatAvg += rates[x];
          beatAvg /= RATE_SIZE;
        }
      }

      irValue = irValue  / 10;

      tft.setCursor(55, box1Bottom + 4);
      tft.print(irValue); tft.print("       ");
      tft.print(irOffset); tft.print("  ");
      // unadjusted graph
      tft.drawPixel(edgeL + 1, map(constrain(irValue, ledBrightness * constHRbottom, ledBrightness * constHRtop), ledBrightness * constHRbottom, ledBrightness * constHRtop, box1Bottom - 1, box1Top + 2) - 1, TFT_DARKGREEN); // 780 , 1000

      if (irValue > constHRtop * ledBrightness) {
        irValue -= 720; //  720
      }
      if (irValue < constHRbottom * ledBrightness) {
        irValue += 720; //  720
      }
      tft.drawLine(edgeL + 1, map(constrain(irValue, ledBrightness * constHRbottom, ledBrightness * constHRtop), ledBrightness * constHRbottom, ledBrightness * constHRtop, box1Bottom - 1, box1Top + 2) - 1, edgeL + 1, map(constrain(lastIR, ledBrightness * constHRbottom, ledBrightness * constHRtop), ledBrightness * constHRbottom, ledBrightness * constHRtop, box1Bottom - 1, box1Top + 2) - 1, TFT_GREEN); // 780 , 1000
      lastIR = irValue;

      tft.setCursor(8, box2Bottom + 4);
      tft.print(ESpO2); tft.print("  ");
      tft.setCursor(8, box1Bottom + 4);
      tft.print(irValue); tft.print("  ");

      tft.setTextSize(3);
      tft.setCursor(10, 78);
      tft.print(beatAvg); tft.print(" ");


      //      tft.drawPixel(edgeL + 1, map(ESpO2, 85, 105, box2Bottom, box2Top - 1) , TFT_BLUE);
      tft.drawLine(edgeL + 1, map(ESpO2, 85, 105, box2Bottom, box2Top - 1) , edgeL + 1, map(lastO2, 85, 105, box2Bottom, box2Top - 1), TFT_BLUE);
      lastO2 = ESpO2;
      edgeL++;

      if (edgeL > 229) {
        edgeL = 6;
        tft.fillRoundRect(edgeL, box2Top + 1, boxWidth - 3, boxHeight - 2, 3, TFT_BLACK);
        tft.fillRoundRect(edgeL, box1Top + 1, boxWidth - 3, boxHeight - 2, 3, TFT_BLACK);
        staticGraphGFX();
        tft.pushImage(15, 194, 18, 18, HR18);
      }

      tft.setTextSize(1);
      tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
      tft.setCursor(200, 17);
      loopEndT = millis() - currentTime;
      tft.print(1000 / loopEndT); tft.print("fps ");

    }
    tft.fillScreen(TFT_BLACK);
    MAX30105.shutDown();
    ledB = 0;
    if (pageCount == 2) page2();
  }
}


void page4() {  // Graph Page

  if (pageCount == 4) {

    tft.fillScreen(TFT_BLACK);
    tft.drawRoundRect(193, 15, 55, 12, 3, TFT_MIDDLEGREY); // (xO, yO, Length, Width, Radius, color)
    edgeL = 5;
    staticGraphGFX();
    cycleCount = 0;

    prevCO2 = box1Bottom - 2; // graphlines startpoints
    prevTVOC = box1Bottom - 2;
    lastpowMW = box2Bottom - 10;

    while (pageCount == 4) {
      currentTime = millis();
      tft.setTextSize(1);
      wifiPrint();
      everyXsec();
      checkforAlarms();
      checkScreenState();

      if (millis() - cycleCount > 1000) { // print dataPoint every x ms
        cycleCount = millis();

        Lvolt = map(Volts, lowVoltAlarm, highVoltAlarm + 0.4, box2Bottom, box2Top + 1); // value, fromLow, fromHigh, toLow, toHigh
        currA = map(Amps, 0, 3.2, box2Bottom, box2Top + 1);

        if (Watts > 6000) {                            // converts from milliWatts to Watts
          powMW = map(Watts, 200, 32000, box2Bottom, box2Top + 1);
        } else {
          powMW = map(Watts, 200, 6000, box2Bottom, box2Top + 1);
        }

        pCO2 = map(CO2, 0, 8000, box1Bottom, box1Top - 1); // 8000
        pTVOC = map(TVOC, 0, 2250, box1Bottom, box1Top - 1); // 2500
        TempGraph = map(tempBME, 0, 100, box1Bottom, box1Top - 1);
        RHgraph = map(RH, 0, 99, box1Bottom, box1Top - 1);

        tft.drawPixel(edgeL + 1, TempGraph - 2, TFT_PINK);
        tft.drawPixel(edgeL + 1, RHgraph - 2, TFT_OLIVE);

        tft.drawLine(edgeL + 1, prevCO2 - 2, edgeL + 1, pCO2 - 2, TFT_BLUE);
        prevCO2 = pCO2;
        tft.drawLine(edgeL + 1, prevTVOC - 2, edgeL + 1, pTVOC - 2, TFT_CYAN);
        prevTVOC = pTVOC;

        tft.drawPixel(edgeL + 1, Lvolt - 2, TFT_INDIA);
        tft.drawLine(edgeL + 1, lastpowMW - 1, edgeL + 1, powMW - 1, TFT_YELLOW);
        lastpowMW = powMW;

        if (FanActive) tft.drawPixel(edgeL + 1, box2Bottom - 4, TFT_RED);
        if (screenState) tft.drawPixel(edgeL + 1, box2Bottom - 2, TFT_GREEN);

        if (edgeL == 10 || edgeL == 60 || edgeL == 110 || edgeL == 160 || edgeL == 208) {
          tft.setTextColor(TFT_LIGHTGREY);
          tft.setCursor(edgeL - 1, Lvolt + 3);
          tft.print(Volts);
          //          tft.setCursor(edgeL - 1, box2Bottom - 11);
          //          tft.print(RTCprint.substring(0, 5)); // print time on graph
        }

        if (edgeL > 229) {
          edgeL = 6;
          tft.fillRoundRect(edgeL, box2Top + 1, boxWidth - 3, boxHeight - 2, 3, TFT_BLACK);
          tft.fillRoundRect(edgeL, box1Top + 1, boxWidth - 3, boxHeight - 2, 3, TFT_BLACK);
          staticGraphGFX();
        }
        edgeL++;
      }

      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.setCursor(28, box1Bottom + 4);
      tft.print(CO2);
      tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
      tft.print("ppm  ");
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.setCursor(105, box1Bottom + 4);
      tft.print(TVOC);
      tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
      tft.print("ppm ");
      tft.setTextColor(TFT_PINK, TFT_BLACK);
      tft.setCursor(172, box1Bottom + 4);
      tft.print(tempBME, 0);
      tft.setTextColor(TFT_OLIVE, TFT_BLACK);
      tft.setCursor(214, box1Bottom + 4);
      tft.print(RH, 0);

      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.setCursor(51, box2Bottom + 4);
      if (Volts < 7 && Volts > 6.5) tft.setTextColor(TFT_ORANGE, TFT_BLACK);
      if (Volts <= 6.5) tft.setTextColor(TFT_INDIA, TFT_BLACK);
      tft.print(Volts);
      tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
      tft.print("v");
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.setCursor(118, box2Bottom + 4);
      if (Amps > currentTH) tft.setTextColor(TFT_INDIA, TFT_BLACK);
      tft.print(Amps);
      tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
      tft.print("a ");


      tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
      tft.print("LOG:");
      if (loggingActive)
      {
        tft.setTextColor(TFT_DARKGREEN, TFT_BLACK);
        tft.print("ON  ");
      } else {
        tft.print("OFF ");
      }

      tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
      tft.print("FAN:");
      if (FanActive)
      {
        tft.setTextColor(TFT_DARKGREEN, TFT_BLACK);
        tft.print("ON ");
      } else {
        tft.print("OFF");
      }

      tft.setTextSize(1);
      tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);

      tft.setCursor(197, 17);
      loopEndT = millis() - currentTime;
      tft.print(1000 / loopEndT); tft.print("fps ");
    }
    tft.fillScreen(TFT_BLACK);
    if (pageCount == 3) page3();
  }
}

void page5() { // Diagnostics

  if (pageCount == 5) {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    scrollTFT = 0;
    uint32_t chipId = 0;
    cycleCount = 0;

    while (pageCount == 5) {
      currentTime = millis();
      tft.setCursor(0, scrollTFT);
      wifiPrint();
      everyXsec();
      checkforAlarms();
      checkScreenState();

      if (cycleCount > 200 || cycleCount == 0) {
        wifiNetworks = WiFi.scanNetworks();
        cycleCount = 0;
        tft.fillScreen(TFT_BLACK);
      } cycleCount++;

      tft.setTextSize(2);
      tft.print(WiFi.SSID()); tft.print(" "); tft.println(wl_status_to_string(WiFi.status()));
      tft.print(WiFi.localIP()); tft.print(" ");
      tft.print(WiFi.RSSI()); tft.println("dB");

      //tft.print(esp_get_free_internal_heap_size() / 1024); tft.println("kb intRAM ");
      tft.print(esp_get_free_heap_size() / 1024); tft.println("kb RAM ");
      tft.setTextSize(1); tft.println(); tft.setTextSize(2);

      tft.setTextSize(1);
      tft.print(ESP.getSdkVersion()); // tft.println(esp_get_idf_version());
      for (int i = 0; i < 17; i = i + 8) {
        chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
      }
      tft.print(" - ");
      tft.printf("%s Rev%d\n", ESP.getChipModel(), ESP.getChipRevision());
      tft.print("Chip ID: "); tft.print(chipId); tft.print(" - ");
      tft.print(ESP.getChipCores()); tft.print(" x ");
      tft.print(getCpuFrequencyMhz()); tft.println("MHz ");

      tft.print("CPU0: "); verbose_print_reset_reason(rtc_get_reset_reason(0)); tft.println();
      //      tft.print("CPU0: "); print_reset_reason(rtc_get_reset_reason(0)); tft.println();
      tft.print("CPU1: "); verbose_print_reset_reason(rtc_get_reset_reason(1)); tft.println();
      //      tft.print("CPU1: "); print_reset_reason(rtc_get_reset_reason(1)); tft.println();

      tft.println("                     ");

      tft.setTextSize(1);
      tft.print("CCS811/I2C:  ");
      if (CCS811err) {
        printSensorError();
      } else {
        tft.println("ok");
      }

      tft.print("IMU:         ");
      if (IMU.readId(&sensorId) > 0) {
        tft.println("--");
      } else {
        tft.println("ok");
      }

      tft.print("VEML6075:    ");
      if (VML.begin()) {
        tft.println("ok");
      } else {
        tft.println("--");
      }

      tft.print("RTC:         ");
      if (rtc.begin()) {
        tft.println("ok");
      } else {
        tft.println("--");
      }

      tft.print("MAX30105:    ");
      if (MAX30105.begin(Wire, I2C_SPEED_FAST)) {
        tft.println("ok");
      } else {
        tft.println("--");
      }

      tft.print("INA260 Mode: ");
      byte INAmode = ina260.getMode();
      switch (INAmode) {
        case 0x00: tft.println("Shutdown"); break;
        case 0x03: tft.println("Triggered"); break;
        case 0x07: tft.println("Continuous"); break;
        default:  tft.println("--");
      }

      /*
            tft.print("MLXtemp:     ");
            if (mlx.begin()) {   // may need time to recover I2C
              tft.println("ok");
            } else {
              tft.println("--");
            }
      */
      tft.print("TempProbes:  ");
      tft.println(DTdevicecount);

      tft.print("Buttons:      ");
      if (ButtonsActive) {
        tft.println("Active");
      } else {
        tft.println("Inactive");
      }

      tft.print("htmlRestart:  ");
      if (htmlRestart) {
        tft.println("true");
      } else {
        tft.println("false");
      }

      tft.print("SDpresent:    ");
      if (SDpresent) {
        tft.println("true");
      } else {
        tft.println("false");
      }

      tft.print("currentTH:    "); tft.println(currentTH);
      tft.print("deepSleepIn:  "); tft.print(deepSleepStart); tft.println(" cycles");
      tft.print("I2C:          "); tft.print(I2C_SPEED_FAST / 1000); tft.println(" kb/s");
      tft.print("HSPI:         "); tft.print(spiFreq / uS_TO_S_FACTOR); tft.println(" MHz");
      tft.print("VSPI:         "); tft.print(SPI_FREQUENCY / uS_TO_S_FACTOR); tft.println(" MHz");

      tft.print("HR Bright:    "); tft.println(ledBrightness);
      tft.print("HR Offset:    "); tft.println(irOffset);


      tft.println();
      tft.print(wifiNetworks); tft.println(" Networks ");
      tft.println();

      for (int thisNet = 0; thisNet < wifiNetworks; thisNet++) {
        tft.print(thisNet);
        tft.print(") ");
        WiFiName = WiFi.SSID(thisNet);
        tft.print(WiFiName.substring(0, 16));
        tft.print("  ");
        tft.print(WiFi.RSSI(thisNet));
        tft.print("dB, ");
        encryptionTypeDescription = translateEncryptionType(WiFi.encryptionType(thisNet));
        tft.println(encryptionTypeDescription);
      }

      tft.setTextSize(1);
      tft.setTextDatum(MC_DATUM);
      tft.drawRoundRect(193, 35, 55, 12, 3, TFT_MIDDLEGREY); // (xO, yO, Length, Width, Radius, color)
      tft.setCursor(200, 37);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      loopEndT = millis() - currentTime;
      tft.print(1000 / loopEndT); tft.print("fps ");
    }
    tft.fillScreen(TFT_BLACK);
    if (pageCount == 4) page4();
  }
}

void page6() { // SD Directories

  if (pageCount == 6) {

    tft.fillScreen(TFT_BLACK);
    scrollTFT = 0;
    tft.setCursor(0, 60);
    tft.setTextSize(2);

    if (!SDpresent) {
      tft.setTextSize(2);
      tft.print(" --- NO SD Card --- ");
      spiSD.begin(14, 25, 13, 15);
    } else if (SD.begin(15, spiSD, spiFreq)) {
      drawBmp("/UI/ESP32_22.bmp", 210, 5);
      SDpresent = true;
      loggingActive = !loggingActive;
      if (loggingActive) {
        drawBmp("/UI/logging12.bmp", 189, 10);
        print_wakeup_reason();
      }
    } else {
      SDpresent = false;
      loggingActive = false;
    }


    tft.setTextSize(2);
    tft.setTextColor(TFT_BLUE, TFT_BLACK);
    tft.setCursor(0, 0);
    tft.print("Size: ");
    if (SDpresent) {
      if (SD.cardSize() == 0) {
        tft.print("---");
        loggingActive = false;
      } else {
        tft.print(SD.cardSize() / 1000000000ULL);
      }
      tft.println(" Gb ");
    } else {
      tft.println("no sd");
    }
    tft.print("Used: ");
    if (SDpresent) {
      if (SD.usedBytes() == 0) {
        tft.print("---");
      } else {
        tft.print(SD.usedBytes() / uS_TO_S_FACTOR);
      }
      tft.println(" Mb ");
    } else {
      tft.println("no sd");
    }

    tft.setCursor(0, 38);
    tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
    tft.print(LogFile);

    //    File root = SD.open("/");

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setCursor(0, scrollTFT + 55);
    while (pageCount == 6) {
      tft.setCursor(0, scrollTFT + 55);
      File root = SD.open("/");
      wifiPrint();
      everyXsec();
      checkforAlarms();
      checkScreenState();

      tft.setTextSize(1);
      printDirectory(root, 0);

    }
  }
  tft.fillScreen(TFT_BLACK);
  if (pageCount == 5) page5();
}



void page7() { // Info Page 1

  if (pageCount == 7) {
    tft.fillScreen(TFT_BLACK);
    if (SDpresent) drawBmp("/UI/MoonEarth240.bmp", 0, 0);
    int txtL = 5;
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE);
    tft.setTextDatum(TL_DATUM);
    tft.drawString("High Exposure to CO2 can produce", txtL, 55, 2);
    tft.drawString("a variety of health effects. These", txtL, 70, 2);
    tft.drawString("may include headaches, dizziness, ", txtL, 85, 2);
    tft.drawString("restlessness, tiredness, increased" , txtL, 100, 2);
    tft.drawString("heartrate & decreased cognitive " , txtL, 115, 2);
    tft.drawString("capacity. Prolonged CO2 levels as " , txtL, 130, 2);
    tft.drawString("low as 1,000ppm (parts per Million)" , txtL, 145, 2);
    tft.drawString("can cause health problems." , txtL, 160, 2);

    while (pageCount == 7) {
      currentTime = millis();
      wifiPrint();
      everyXsec();
      checkforAlarms();
      checkScreenState();
      tft.setTextSize(2);
      tft.setCursor(10, 10);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.print("CO2 ");
      if (CO2 > 1000 && CO2 < 2000) tft.setTextColor(TFT_ORANGE, TFT_BLACK);
      if (CO2 > 2000 && CO2 < 3000) tft.setTextColor(TFT_INDIA, TFT_BLACK);
      if (CO2 > 3000) tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.print(CO2); tft.print("ppm ");

      tft.setTextSize(1);
      tft.setTextDatum(TL_DATUM);
      tft.drawRoundRect(193, 35, 55, 12, 3, TFT_MIDDLEGREY); // (xO, yO, Length, Width, Radius, color)
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      loopEndT = millis() - currentTime;
      tft.drawString(String(1000 / loopEndT) + "fps ", 200, 37, 1);
    }
    tft.fillScreen(TFT_BLACK);
    if (pageCount == 6) page6();
  }
}

void page8() {

  if (pageCount == 8) {
    tft.fillScreen(TFT_BLACK);
    if (SDpresent) drawBmp("/UI/MoonEarth240.bmp", 0, 0);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE);
    tft.setTextDatum(TL_DATUM);
    int txtL = 5;
    tft.drawString("Natural sources are decomposition, ", txtL, 55, 2);
    tft.drawString("ocean release and respiration.", txtL, 70, 2);
    tft.drawString("Human sources come from activities ", txtL, 85, 2);
    tft.drawString("like cement production, deforestation" , txtL, 100, 2);
    tft.drawString("as well as the burning of fossil fuels" , txtL, 115, 2);
    tft.drawString("like coal, oil, natural gas and high" , txtL, 130, 2);
    tft.drawString("density Traffic & Industrial areas." , txtL, 145, 2);

    while (pageCount == 8) {
      currentTime = millis();
      wifiPrint();
      everyXsec();
      checkforAlarms();
      checkScreenState();

      tft.setTextSize(2);
      tft.setCursor(10, 10);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.print("tVOC "); tft.print(TVOC); tft.println("ppm ");

      tft.setTextSize(1);
      tft.setTextDatum(TL_DATUM);
      tft.drawRoundRect(193, 35, 55, 12, 3, TFT_MIDDLEGREY); // (xO, yO, Length, Width, Radius, color)
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      loopEndT = millis() - currentTime;
      tft.drawString(String(1000 / loopEndT) + "fps ", 200, 37, 1);
    }
    tft.fillScreen(TFT_BLACK);
    if (pageCount == 7) page7();
    if (pageCount == 0) page0();
  }
}


void staticGraphGFX() {

  byte GraphMulti = boxHeight / 10;   // graph line spacing multiplier

  edgeL = 5;
  tft.drawRoundRect(edgeL, box1Top, boxWidth, boxHeight, 3, TFT_LIGHTGREY);
  tft.drawRoundRect(edgeL, box2Top, boxWidth, boxHeight, 3, TFT_LIGHTGREY);

  edgeL = 7;
  tft.drawFastHLine(edgeL, box1Bottom - GraphMulti, boxWidth - 3, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, box1Bottom - GraphMulti * 2 , boxWidth - 3, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, box1Bottom - GraphMulti * 3 , boxWidth - 3, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, box1Bottom - GraphMulti * 4 , boxWidth - 3, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, box1Bottom - GraphMulti * 5 , boxWidth - 3, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, box1Bottom - GraphMulti * 6 , boxWidth - 3, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, box1Bottom - GraphMulti * 7 , boxWidth - 3, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, box1Bottom - GraphMulti * 8 , boxWidth - 3, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, box1Bottom - GraphMulti * 9 , boxWidth - 3, TFT_DARKGREY);

  tft.drawFastHLine(edgeL, box2Bottom - GraphMulti, boxWidth - 3, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, box2Bottom - GraphMulti * 2 , boxWidth - 3, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, box2Bottom - GraphMulti * 3 , boxWidth - 3, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, box2Bottom - GraphMulti * 4 , boxWidth - 3, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, box2Bottom - GraphMulti * 5 , boxWidth - 3, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, box2Bottom - GraphMulti * 6 , boxWidth - 3, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, box2Bottom - GraphMulti * 7 , boxWidth - 3, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, box2Bottom - GraphMulti * 8 , boxWidth - 3, TFT_DARKGREY);
  tft.drawFastHLine(edgeL, box2Bottom - GraphMulti * 9 , boxWidth - 3, TFT_DARKGREY);

  edgeL = 5;
  if (pageCount == 4) {
    tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
    tft.setTextSize(1);
    tft.setCursor(edgeL, box1Bottom + 4);
    tft.print("CO2");
    tft.print("         ");
    tft.print("tVOC         ");
    tft.print(" T   ");
    tft.print("* ");
    tft.print("RH   ");
    tft.print("% ");

    tft.setCursor(edgeL, box2Bottom + 4);
    tft.print("Voltage");
    tft.print("       ");
    tft.print("Amps");
  }
}

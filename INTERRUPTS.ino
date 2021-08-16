#include <pgmspace.h>

void IRAM_ATTR buttonInterrupt1() {
  TFTon();
  if (pageCount == 0) {
    menuCar--;
  } else {
    pageCount--;
    if (pageCount > menuPages) pageCount = 0;
  }
}

void IRAM_ATTR buttonInterrupt2() {
  TFTon();
  if (pageCount == 0) {
    menuCar++;
  } else {
    pageCount++;
    if (pageCount > menuPages) pageCount = 0;
  }
}

/*
  void IRAM_ATTR buttonInterrupt3() {
  amgSetHiRes = !amgSetHiRes;
  //  burstReading = 1;
  TFTon();
  if (pageCount == 3) irOffset += 5;
  if (pageCount == 5 || pageCount == 6) {
    scrollTFT += 30;
    cycleCount = 0;
  } /* else if (ledB == 0) {
    ledB = 250; // commands for dimming logic
  } else {
    ledB = 1;   // commands for dimming logic

  } */

/*
   page 0: Menu
   page 1: Settings
   page 2: SD
   page 3: System/Diagnostics
   page 4: Charts & Graphs
   page 5: Home
   page 6: CO2 Info
   page 7: VOC info
   page 8: Thermal Cam
   page 9: Heartrate
*/



void sinlgeClick() { // Single Click


  TFTon();

  switch ( pageCount ) {
    case 0:
      switch ( menuCar ) {
        case 1: tft.drawRoundRect(mX, 84, 40, 40, 7, TFT_GREEN); delay(80); pageCount = 1; break;
        case 2: tft.drawRoundRect(mX, 84, 40, 40, 7, TFT_GREEN); delay(80); pageCount = 3; break;
        case 3: tft.drawRoundRect(mX, 84, 40, 40, 7, TFT_GREEN); delay(80); pageCount = 5; break;
        case 4: tft.drawRoundRect(mX, 84, 40, 40, 7, TFT_GREEN); delay(80); pageCount = 8; break;
        case 5: tft.drawRoundRect(mX, 84, 40, 40, 7, TFT_GREEN); delay(80); pageCount = 9; break;
      }
      break;
    case 1:  ledBon = !ledBon; break;
    case 2:  ledBon = !ledBon; break;
    case 3:  ledBon = !ledBon; break;
    case 4:  ledBon = !ledBon; break;
    case 5:  ledBon = !ledBon; break;
    case 6:  ledBon = !ledBon; break;
    case 7:  ledBon = !ledBon; break;
    case 8:  burstReading = true; break;
    case 9:  break;
  }
}


void onPressedForDuration() {       // long press
}

void doubleClick() {    // double Click

  switch ( pageCount ) {
    case 0: break;
    case 1: {
        tft.fillScreen(TFT_BLACK);
        scrollTFT += 30;
        tft.fillRoundRect(-12, 171 - scrollTFT, 188, 32, 15, TFT_DARKGREY); // wifi box
        tft.fillRoundRect(-12, 181 - scrollTFT, 188, 32, 15, TFT_BLACK); // wifi box
        tft.drawFastHLine(0, 51 - scrollTFT, TFT_WIDTH, TFT_MIDDLEGREY);
        tft.drawFastHLine(0, 93 - scrollTFT, TFT_WIDTH, TFT_MIDDLEGREY);
        tft.drawFastHLine(0, 132 - scrollTFT, TFT_WIDTH, TFT_DARKGREY);
        tft.drawFastVLine(175, 94 - scrollTFT, 250, TFT_DARKGREY);
        tft.drawFastVLine(122, 94 - scrollTFT, 75, TFT_DARKGREY);
        tft.drawFastVLine(55, 94 - scrollTFT, 75, TFT_DARKGREY);
        break;
      }
    case 2: scrollTFT += 30; break;
    case 3: loggingActive = !loggingActive; if (!SDpresent) loggingActive = false; putPersistentBool("loggingActive", loggingActive); break;
    case 4: loggingActive = !loggingActive; if (!SDpresent) loggingActive = false; putPersistentBool("loggingActive", loggingActive); break;
    case 5: loggingActive = !loggingActive; if (!SDpresent) loggingActive = false; putPersistentBool("loggingActive", loggingActive); break;
    case 6: loggingActive = !loggingActive; if (!SDpresent) loggingActive = false; putPersistentBool("loggingActive", loggingActive); break;
    case 7: loggingActive = !loggingActive; if (!SDpresent) loggingActive = false; putPersistentBool("loggingActive", loggingActive); break;
    case 8: measurePoint = !measurePoint; amgSetHiRes = !amgSetHiRes; break;
    case 9: {
        irOffset += 5;
        constHRtop = 93 - irOffset;
        constHRbottom = 90 - irOffset;
        break;
      }
  }
}


void IRAM_ATTR buttonISR() {
  button.read(); // When button is being used through external interrupts,  parameter INTERRUPT must be passed to read() function
}

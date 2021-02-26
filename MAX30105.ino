#include <pgmspace.h>

void readHRO2()
{

  bool buttonState1 = (digitalRead(tPAD1));

  if (buttonState1 != lastButtonState1 && ButtonsActive == true) {
    if (buttonState1 == 1) {

      
      if (ta1 == true ||   // Fan Activation
          ta2 == true ||
          ta3 == true ||
          ta4 == true ||
          ta5 == true ||
          ta6 == true ||
          ta7 == true ||
          current_A > current_TH)
      {
        digitalWrite(fan, HIGH);
      } else {
        digitalWrite(fan, LOW);
      }

      particleSensor.wakeUp();
      tft.fillScreen(TFT_BLACK);
      //tft.drawRoundRect(10, 10, 220, 220, 10, TFT_MIDDLEGREY);
      //tft.fillRoundRect(11, 11, 218, 218, 10, TFT_BLACK);

      int i = 0;  //                                 ======= HR + SpO2 Settings =======
      int Num = 35;             //  calculate SpO2 by this sampling interval

      const byte RATE_SIZE = 6; //  Increase this for more HR averaging. 4 is good.
      byte rates[RATE_SIZE];
      byte rateSpot = 0;
      long lastBeat = 0;
      float beatsPerMinute;
      int beatAvg;

      double ESpO2 = 90.0;     //initial value of estimated SpO2
      double FSpO2 = 0.7;      //filter factor for estimated SpO2
      double frate = 0.95;     // 0.95 low pass filter for IR/red LED value to eliminate AC component
      double avered = 0;
      double aveir = 0;
      double sumirrms = 0;
      double sumredrms = 0;

      while ((digitalRead(tPAD1)) == HIGH && ButtonsActive == true) {

        uint32_t ir, red;
        double fred, fir;
        double SpO2 = 0;          //raw SpO2 before low pass filtered

        particleSensor.check();                 //Check the sensor, read up to 3 samples
        tft.pushImage(65, 122, 18, 18, HR18);
        while (particleSensor.available()) {    //do we have new data
          red = particleSensor.getFIFOIR();     // swap inputs for MH-ET LIVE !! red=IR, IR=red
          ir = particleSensor.getFIFORed();     // getFIFORed output IR data by MAX30102 on MH-ET LIVE breakout board
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
          particleSensor.nextSample();                        //We're finished with this sample so move to next sample
        }

        long irValue = particleSensor.getIR();

        if (checkForBeat(irValue) == true)
        {
          //We sensed a beat!
          tft.pushImage(65, 122, 18, 18, HRgreen18);
          tone(beep, 500, 5);
          ledcWrite(ledChannel1, 255);
          long delta = millis() - lastBeat;
          lastBeat = millis();

          beatsPerMinute = 60 / (delta / 1000.0);

          if (beatsPerMinute < 255 && beatsPerMinute > 20)
          {
            rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
            rateSpot %= RATE_SIZE; //Wrap variable

            beatAvg = 0;         //Take average of readings
            for (byte x = 0 ; x < RATE_SIZE ; x++)
              beatAvg += rates[x];
            beatAvg /= RATE_SIZE;
          }
        }

        tft.setTextDatum(MC_DATUM);
        tft.setTextPadding(190);

        tft.setTextSize(2);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.drawNumber(constrain(beatAvg, 40, 199), 120, 72, 7);
        tft.setTextSize(1);
        tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
        tft.setTextPadding(0);
        tft.drawString("bpm", 120, 133, 4);

        tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
        tft.setTextPadding(120);
        tft.drawNumber((ESpO2), 120, 175, 7);
        tft.setTextColor(TFT_MIDDLEGREY, TFT_BLACK);
        tft.drawString("SpO2%", 120, 215, 4);

        //int HRtemp = particleSensor.readTemperature();
        //tft.setTextSize(3);
        //tft.setCursor(150, 20);
        //tft.print(HRtemp);

        ledcWrite(ledChannel1, 0);
      }
    }
    particleSensor.shutDown();       // this runs Once after button is released
    tft.fillScreen(TFT_BLACK);
    staticGFX();
  }

  //if (irValue < 50000)    // for triggering proximity

  //Serial.print("IR=");
  //Serial.print(irValue);
  //Serial.print(", BPM=");
  //Serial.print(beatsPerMinute);

}

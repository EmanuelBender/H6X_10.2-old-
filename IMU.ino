#include <pgmspace.h>

void readIMU() {

if (sleepTimer < TimeoutT) {
  tft.setTextDatum(MC_DATUM);
  tft.setTextSize(1);
  tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
  tft.setTextPadding(30);

  if (IMU.accelUpdate() == 0) {
    aX = IMU.accelX();
    aY = IMU.accelY();
    aZ = IMU.accelZ();
    aSqrt = IMU.accelSqrt(); /*
    tft.println("accelX: " + String(aX));
    tft.println("accelY: " + String(aY));
    tft.println("accelZ: " + String(aZ));
    tft.println("accelSqrt: " + String(aSqrt)); */
  }

  if (IMU.gyroUpdate() == 0) {
    gX = IMU.gyroX();
    gY = IMU.gyroY();
    gZ = IMU.gyroZ(); /*
    tft.println("gyroX: " + String(gX));
    tft.println("gyroY: " + String(gY));
    tft.println("gyroZ: " + String(gZ)); */
  }

  if (IMU.magUpdate() == 0) {
    mX = IMU.magX();
    mY = IMU.magY();
    mZ = IMU.magZ();
    mDirection = IMU.magHorizDirection() + 180;
    tft.drawNumber(mDirection, 160, 9, 2);

    /*
      tft.println("magX: " + String(mX));
      tft.println("maxY: " + String(mY));
      tft.println("magZ: " + String(mZ));
      tft.println("Heading: " + String(mDirection)); */
  }
}

  /*
    uint8_t sensorId;
    String Compass = "";

    Compass += "Compass: ";
    Compass += String(mDirection) + "  Accel: " + String(aSqrt) + "  || ID: " + String(IMU.readId(&sensorId));
    Compass += "\r\n";
    Compass += " |- acc: x" + String(aX) + " y" + String(aY) + " z" + String(aZ) + "\r\n";
    Compass += " |- gyr: x" + String(gX) + " y" + String(gY) + " z" + String(gZ) + "\r\n";
    Compass += " |- mag: x" + String(mX) + " y" + String(mY) + " z" + String(mZ) + "\r\n";

    appendFile(SD, LogFile, Compass.c_str());
    //Serial.print(Compass.c_str());
  */
}

#include <pgmspace.h>

/*
  void readFile(fs::FS &fs, const char * path) {
  //Serial.printf("Reading file: %s\n", path);
  //File dataFile = SD.open("/ESP32_Test.txt", FILE_WRITE);

  File file = fs.open(path);
  if (!file) {
    //Serial.println("Failed to open file for reading");
    return;
  }

  //Serial.print("Read from file: ");
  while (file.available()) {
    Serial.write(file.read());
  }
  file.close();
  }


  void writeFile(fs::FS &fs, const char * path, const char * message) {
  //Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    //Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    //Serial.println("File written");
  } else {
    //Serial.println("Write failed");
  }
  file.close();
  }
*/


void appendFile(fs::FS &fs, const char * path, const char * message) {
  //Serial.printf("Appending to file: %s\n", path);

  if (LoggingActive = true) {
    File file = fs.open(path, FILE_APPEND);
    if (!file) {
      return;
    }
    file.print(message);//  Message appended
    file.close();
  }
}

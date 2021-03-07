#include<DDBv8SA.h>
#include <SoftwareSerial.h>
char message;


SoftwareSerial mySerial(RXPIN, RXPIN); // RX, TX

void setup() {
  mySerial.begin(38400);
}

void loop() {
  onBoardLED(1);
  while (mySerial.available()) {
    message = mySerial.read();
    mySerial.write(message);
  }
}

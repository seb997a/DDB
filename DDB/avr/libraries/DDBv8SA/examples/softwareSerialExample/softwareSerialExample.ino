/*
  The sketch demonstrates how to use the serial monitor on the DBDV8.
  To upload, click upload (cmd u) and wait for the terminal window to say uploading.
  When it says uploading, connect a MINI-USB to the "MINI-USB-Flash" USB port.
  Once the sketch has been uploaded, connect the USB to the "MINI-USB-FLASH" port.
  Once connected, select the correct COM port in the IDE and wait until the onboard LED illuminates.
  Once illuminated, open the serial monitor and make sure the baud rate is set to 38400.
  To test that the serial monitor is working, type anything into the serial monitor and then "test" should be returned.
*/

#include<DDBv8SA.h>
#include <SoftwareSerial.h>

volatile char message;

SoftwareSerial mySerial(RXPIN, TXPIN); // RX, TX

void setup() {
  mySerial.begin(38400);
}

void loop() {
  onBoardLED(1);
  if (mySerial.available()) {
    mySerial.println("test");
    while (mySerial.available())
      mySerial.read();
  }
}

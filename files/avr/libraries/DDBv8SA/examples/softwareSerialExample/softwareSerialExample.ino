/*
The sketch demonstrates how to use the serial monitor on the DBDV8. 
To upload, click upload (cmd u) and wait for the terminal window to say uploading.
When it says uploading, connect a MINI-USB to the "MINI-USB-Flash" USB port.
Once the sketch has been uploaded, connect the USB to the "MINI-USB-FLASH" port.
Once connected, select the correct COM port in the IDE and wait until the onboard LED illuminates.
Once illuminated, open the serial monitor and make sure the baud rate is set to "38400".
To test the sketch, type something into the serial monitor, and it should print it back out.
*/

#include<DDBv8SA.h>
#include <SoftwareSerial.h>

char message;

SoftwareSerial mySerial(RXPIN, TXPIN); // RX, TX

void setup() {
  mySerial.begin(38400);
}

void loop() {
  onBoardLED(1);                      //Turns LED on informing the user that the sketch is running.
  while (mySerial.available()) {
    message = mySerial.read();
    mySerial.write(message);
  }
}

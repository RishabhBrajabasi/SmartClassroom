/* Input-side (button) Arduino code */
#include "SoftwareSerial.h"
// RX: Arduino pin 2, XBee pin DOUT.  TX:  Arduino pin 3, XBee pin DIN
SoftwareSerial XBee(2, 3);
int BUTTON = 8;

void setup()
{
  // Baud rate MUST match XBee settings (as set in XCTU)
  pinMode(BUTTON, INPUT);
  XBee.begin(9600);
  Serial.begin(9600);
}

void loop()
{
  if (digitalRead(BUTTON) == HIGH)
  {
    Serial.println("Xbee Write: H");
    XBee.write('H');
    delay(50);
  }

  if(XBee.available()){
    char rendOne;
    rendOne = XBee.read();
    Serial.println(rendOne);
  }

  
}

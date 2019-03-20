/* Output-side (LED) Arduino code */
#include "SoftwareSerial.h"
// RX: Arduino pin 2, XBee pin DOUT.  TX:  Arduino pin 3, XBee pin DIN
SoftwareSerial XBee(2, 3);
int LED = 13;
int button = 8;
byte rx = 0x55;

void setup()
{
  // Baud rate MUST match XBee settings (as set in XCTU)
  XBee.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
}

void loop()
{
  

  if(digitalRead(button) == HIGH){
    Serial.println("Coordinator to EndNodes : Sending 85");
    XBee.write(rx);
    delay(50);
  }

  
  if (XBee.available())  
  { 
    byte tx = XBee.read();
    Serial.print("EndNodes to Coordinator : Recieving ");
    Serial.print(tx);
    Serial.println();
  }
  
}

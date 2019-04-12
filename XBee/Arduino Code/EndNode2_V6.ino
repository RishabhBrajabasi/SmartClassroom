/*
 Wireless Sensor Networks - 18748
 Author: Rishabh Brajabasi
 Date: 10/04/2019
 Version: 5.2

 Current configuration works with the soldered setting. 
 TODO: 
  Test the IR. 

 Read status of 5 buttons and 1 IR sensor.
 Send data to Coordinator node via Xbee.
 Four buttons to select four choices, which can be toggled. A submit button which can 
 be used to serially send the status of the four buttons when pressed. 
 IR sensor to detect occupancy. Time based.
*/

#include "SoftwareSerial.h"
SoftwareSerial XBee(9, 8);

const int button1 = 10;  // Option A  
const int button2 = 11;  // Option B  
const int button3 = 12;  // Option C
const int button4 = 13;  // Option D
const int button5 = A2;  // Submit

const int redLed = A3;  // Red LED
const int greenLed = A4;  // Green LED
const int blueLed = A5;  // Blue LED
const int irSensor = A1; // Occupancy

#define COMMON_ANODE

// HIGH when button pressed and LOW when button released:
int optionAc = 0;         
int optionBc = 0;         
int optionCc = 0;         
int optionDc = 0;         
int submit = 0;

int wrong = 0;
int right = 0;

int occupied = 0;

// Timers to keep track of occupancy
int sitting = 0;  // Only increments when triggered
int otherwise = 0;  // Increments irrespective

//  Variables to keep track of toggling of buttons
bool a = false;
bool b = false;
bool c = false;
bool d = false;
bool s = false;

// Variables to detect state of options
int aSelected = 0;
int bSelected = 0;
int cSelected = 0;
int dSelected = 0;

byte answer = 0x00;
byte seat = 0xc4;   // Will change for every node
bool dataReady = false;

bool d1 = false;
bool d2 = false;
bool d3 = false;
bool d4 = false;
bool d5 = false;
bool d6 = false;

void setup() {
  // initialize the button pin as a input:
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(button5, INPUT);
  pinMode(irSensor, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
//  digitalWrite(redLed, LOW);
//  digitalWrite(greenLed, LOW);
  setColor(0, 0, 0);  // red
  
  // initialize serial communication:
  Serial.begin(9600);
  XBee.begin(9600);
}


void loop() {
  // read the pushbutton input pin:
  optionAc = digitalRead(button1);
  optionBc = digitalRead(button2);
  optionCc = digitalRead(button3);
  optionDc = digitalRead(button4);
  submit = digitalRead(button5);
  occupied = digitalRead(irSensor);

// Stop accepting changes once dataReady has been set
  if(!dataReady){
    if(!d1){
      Serial.println("Select Answer");
      d1 = true;
    }

    // Button for option A pressed
    if (optionAc == HIGH && a == false) {
      a = true;
    }
    if (optionAc == LOW && a == true){
      a = false;
        // Option A selected
        if(aSelected == 0 ){
          Serial.println("A Selected");
          answer = answer | 0x08;
            aSelected = 1;
        }
        // Option A unselected
        else{
          Serial.println("A Unselected");
          answer = answer & 0xf7;        
            aSelected = 0;
        }
    }
    
    // Button for option B pressed
    if (optionBc == HIGH && b == false) {
      b = true;
    }
    if (optionBc == LOW && b == true){
        b = false;
        // Option B selected
        if(bSelected == 0 ){
          Serial.println("B Selected");
          answer = answer | 0x04;        
          bSelected = 1;
        }
        // Option B unselected    
        else{
          Serial.println("B Unselected");
          answer = answer & 0xfb;        
          bSelected = 0;
        }
    }

    // Button for option C pressed
    if (optionCc == HIGH && c == false) {
      c = true;
    }
    if (optionCc == LOW && c == true){
      c = false;
      // Option C selected
      if(cSelected == 0 ){
        Serial.println("C Selected");
        answer = answer | 0x02;      
        cSelected = 1;
      }
      // Option C unselected
      else{
        Serial.println("C Unselected");
        answer = answer & 0xfd;      
        cSelected = 0;
      }
    }

    // Button for option D pressed
    if (optionDc == HIGH && d == false) {
      d = true;
    }
    if (optionDc == LOW && d == true){
      d = false;
      // Option D selected
      if(dSelected == 0 ){
        Serial.println("D Selected");
        answer = answer | 0x01;      
        dSelected = 1;
      }
      // Option D unselected
      else{
        Serial.println("D Unselected");
        answer = answer & 0xfe;      
        dSelected = 0;
      }
    }
  }

  // On click of submit, set dataReady flag to true
  if( submit == HIGH && s == false){
    s = true;
  }
  if( submit == LOW && s == true){
    s = false;
    dataReady = true;
    if(!d2){
      Serial.println("Answer Submitted. Cannot change answer anymore");
      d2 = true;
    }

  }

// Increment counters to check occupancy
  if( occupied == LOW ){
    sitting = sitting + 1;
  }
  otherwise = otherwise + 1;

// Check occupancy  
  if(sitting == otherwise && sitting == 100){
    seat = seat | 0x01;
    XBee.write(seat);
  }
  else if(sitting != otherwise && otherwise == 100){
    seat = seat & 0xfe;
    XBee.write(seat);
  }

// Reset Counters
  if(otherwise == 100){
    otherwise = 0;
    sitting = 0;
  }

  delay(50);

// Processing the response of the Coordinator
  if (XBee.available())  
  { 
    byte rx = XBee.read();
//    Serial.println(rx);

    // Polling for data Specific address 0x01
    if(rx == 0x02){     // Change for every node
      if(!d3){
        Serial.println("Device 2 being queried by Coordinator");
        d3 = true;
      }
      
      if(dataReady){
        if(!d4){
          XBee.write(answer);
          delay(50);

        Serial.println("Answer submitted by user. Device 2 Tx data to Coordinator");
        d4 = true;
          }
          // Send the data
      }
       // Can add an else, saying waiting for user. 
       // Or a structure, saying waiting for coordinator.
      
    }
  
    // Correct answer from coordinator
    else if(((rx)&(0x40)) == (0x40)){
        if(!d6){
          Serial.println("Correct Answer recieved from Coordinator");
          d6 = true;
        
// Check if answer matches, set LED's appropriately
        if( ( ( (answer)&(0x0f) ) == ( (rx)&(0x0f) ) ) ){
            Serial.println("Correct Answer");
             setColor(0, 255, 0);  // green
//            digitalWrite(greenLed, HIGH);
//            digitalWrite(redLed, LOW);
        }
        else{
          Serial.print("Incorrect Answer");
           setColor(0, 0, 255);  // red
//          digitalWrite(greenLed, LOW);
//          digitalWrite(redLed, HIGH);
        }
     }
    // Reset dataReady variable
    dataReady = false;
    }
  
      if(d3 && d4 ){
      if(!d5){
        Serial.println("Device 2 waiting for correct answer from coordinator"); 
        d5 = true; 
      }
      
    }
  
  }
}


// TODO: Common Anode changes. 

void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redLed, red);
  analogWrite(greenLed, green);
  analogWrite(blueLed, blue);  
}

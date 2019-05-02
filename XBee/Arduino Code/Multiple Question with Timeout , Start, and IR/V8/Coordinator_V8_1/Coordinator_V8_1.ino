#include "SoftwareSerial.h"
// RX: Arduino pin 2, XBee pin DOUT.  TX:  Arduino pin 3, XBee pin DIN
SoftwareSerial XBee(2, 3);

const int button1 = 8;  // 

byte answer1; // Answer recieved from D1
byte answer2; // Answerrecieved from D2

byte node1 = 0x01;  // Address to use when communicating with D1
byte node2 = 0x02;  // Address to use when communicating with D2
byte answer = 0x45; // The correct answer to the question (Ans: BD)
byte occupancy = 0x00;  
byte seat;

bool answerRecieved1 = false; // Status of whether answer was recieved from D1
bool answerRecieved2 = false; // Status of whether answer was recieved from D2
String nodeTalk = "1";

bool d1 = false;
bool d2 = false;
bool d3 = false;
bool d4 = false;
bool d5 = false;
bool d6 = false;
bool d8 = false;
bool d9 = false;
bool s = false;

bool seat1 = false;
bool seat2 = false;
int submit = 0;
bool startQuiz = false;

bool ds = false;
bool db = false;

byte debug = 0x00;

void setup()
{
  // Baud rate MUST match XBee settings (as set in XCTU)
  pinMode(button1, INPUT);
  XBee.begin(9600);
  Serial.begin(9600);
}

void loop()
{
  if(!startQuiz){
      Serial.flush();

      // Check for start of quiz signal from coordinator
      if(Serial.available())
      {
        int stByte = Serial.parseInt();
        if(stByte == 0xFF){
          startQuiz = true;
          XBee.write(stByte);
          Serial.println(0xFF);
          delay(500);
          while(Serial.available()){
            Serial.read();
          }
        }
      }
  }
  else{
    if(!answerRecieved1){
      XBee.write(node1);
      nodeTalk = "1";
    }
    //Step2: If D1 gave an answer, Query D2 for answer
    if(answerRecieved1 && !answerRecieved2){
      XBee.write(node2);
      nodeTalk = "2";
    }
    
    //Step3: If all Devices have answered, Broadcast the correct answer
    if(answerRecieved1 && answerRecieved2){
      Serial.flush();
      
      while(!Serial.available());
      XBee.write(Serial.parseInt());
      
      // Reset variable
      answerRecieved1 = false;
      answerRecieved2 = false;
      startQuiz = false;
      nodeTalk = "1";
      
      d1 = false;
      d2 = false;
      d3 = false;
      d4 = false;
      d5 = false;
      d6 = false;
      d8 = false;
      d9 = false;
      s = false;
      
      seat1 = false;
      seat2 = false;
    }
    delay(50);
    
    // Read Incoming Data 
    if(XBee.available()){
      byte rx = XBee.read();
      if(((rx)&(0xC0)) == (0x00)){
        if(nodeTalk=="1"){
          answer1 = ((0x0F)&(rx));
          if(!d4){
            byte pi = 0x90;
            if( ((answer1) & (0x08)) == (0x08) ){
              pi = (pi)|(0x08); 
            }
            if( ((answer1) & (0x04)) == (0x04) ){
              pi = (pi)|(0x04);
            }
            if( ((answer1) & (0x02)) == (0x02) ){
              pi = (pi)|(0x02);
            }
            if( ((answer1) & (0x01)) == (0x01) ){
              pi = (pi)|(0x01);
            }
            answerRecieved1 = true;
            d4 = true;  
            Serial.println(pi);
          }
        }
        if(nodeTalk=="2"){
          answer2 = ((0x0F)&(rx));
          if(!d5){
            byte pi = 0xA0;
            if( ((answer2) & (0x08)) == (0x08) ){
                pi = (pi)|(0x08); 
            }
            if( ((answer2)&(0x04)) == (0x04) ){
                pi = (pi)|(0x04); 
            }
            if( ((answer2)&(0x02)) == (0x02) ){
                pi = (pi)|(0x02); 
            }
            if( ((answer2)&(0x01)) == (0x01) ){
                pi = (pi)|(0x01); 
            }
            answerRecieved2 = true;
            Serial.println(pi);
            d5 = true;
          }
        }
      }
      
        
        else{
          //Serial.print("Recieveing information of non existing chairs: Check ANDing");
        }
      }
    }  

//  Serial.print("H1");
  
  if(XBee.available()){
    byte rx = XBee.read();
//    Serial.print("H2");
    if(((rx)&(0xC0)) == (0xC0)){
      // REMOVE
//      Serial.println("IR Data Recieved");
      
      byte occupy;
      seat = ((rx)&(0x3E));
      occupancy = ((rx)&(0x01));
        
      if(seat == 0x02){
        if(occupancy == (0x01)){
          occupy = 0x11;
          Serial.println(occupy);
          seat1 = true;
        }
        else{
          occupy = 0x10;
          Serial.println(occupy);
          seat1 = false;
        }
      }
        
      else if(seat == 0x04){
        if(occupancy == (0x01)){
          seat2 = true;
          occupy = 0x21;
          Serial.println(occupy);
        }
        else{
          seat2 = false;
          occupy = 0x20;
          Serial.println(occupy);
        }
      }
    }
  }

}

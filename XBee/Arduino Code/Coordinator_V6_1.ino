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
void setup()
{
  // Baud rate MUST match XBee settings (as set in XCTU)
  pinMode(button1, INPUT);
  XBee.begin(9600);
  Serial.begin(9600);
}

void loop()
{
  
  
submit = digitalRead(button1);
// Transmit Data 

  // Step1: Query D1 for answer
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
    int dataPi = Serial.parseInt();
    Serial.print(dataPi);
    answer = dataPi;
    
      XBee.write(dataPi);

    
    nodeTalk = "all";
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
//          Serial.print("Answer recieved from D1: ");
          if( ((answer1) & (0x08)) == (0x08) ){
//            Serial.print("A");
            pi = (pi)|(0x08); 
          }
          if( ((answer1) & (0x04)) == (0x04) ){
//            Serial.print("B");
            pi = (pi)|(0x04);
          }
          if( ((answer1) & (0x02)) == (0x02) ){
//            Serial.print("C");
            pi = (pi)|(0x02);
          }
          if( ((answer1) & (0x01)) == (0x01) ){
//            Serial.print("D");
            pi = (pi)|(0x01);
          }
//          Serial.println();
          answerRecieved1 = true;
          d4 = true;  
          
          Serial.print(pi);
        }
      }
      if(nodeTalk=="2"){
        answer2 = ((0x0F)&(rx));
        if(!d5){
          byte pi = 0xA0;
//          Serial.print("Answer recieved from D2: ");
          if( ((answer2) & (0x08)) == (0x08) ){
//            Serial.print("A");
              pi = (pi)|(0x08); 
          }
          if( ((answer2)&(0x04)) == (0x04) ){
//            Serial.print("B");
              pi = (pi)|(0x04); 
          }
          if( ((answer2)&(0x02)) == (0x02) ){
//            Serial.print("C");
              pi = (pi)|(0x02); 
          }
          if( ((answer2)&(0x01)) == (0x01) ){
//            Serial.print("D");
              pi = (pi)|(0x01); 
          }
//          Serial.println();
          answerRecieved2 = true;
          Serial.print(pi);
          d5 = true;
        }
      }
    }
    
    else if(((rx)&(0xC0)) == (0xC0)){
      byte occupy;
//      Serial.print("Recieved Occupancy Data");
      seat = ((rx)&(0x3E));
      occupancy = ((rx)&(0x01));


      
      if(seat == 0x02){
        if(occupancy == (0x01)){
          occupy = 0x11;
          Serial.print(occupy);
          seat1 = true;
        }
        else{
          occupy = 0x10;
          Serial.print(occupy);
          seat1 = false;
        }
        }
   


      else if(seat == 0x04){
        if(occupancy == (0x01)){
           seat2 = true;
           occupy = 0x21;
           Serial.print(occupy);
        }
        else{
          seat2 = false;
          occupy = 0x20;
          Serial.print(occupy);
        }
      }

      else{
//        Serial.print("Recieveing information of non existing chairs: Check ANDing");
      }
      
    }

    // Continuous input being recieved
//    else{
//      Serial.print("DP478");
//    }

  } 

  if( submit == HIGH && s == false){
    s = true;
  }
  if( submit == LOW && s == true){
    s = false;
    Serial.println("Chair Occupancy:");
    if(seat1){
      Serial.println("Chair 1 occupied");    
    }
    else{
      Serial.println("Chair 1 empty");    
    }
    if(seat2){
      Serial.println("Chair 2 occupied");
    }
    else{
      Serial.println("Chair 2 empty");
    }
  }


}

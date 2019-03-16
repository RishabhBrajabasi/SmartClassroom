/*
 Wireless Sensor Networks - 18748
 Author: Rishabh Brajabasi
 Date: 16/03/2019
 Version: 1.2

 Read status of 5 buttons and 1 IR sensor.
 Four buttons to select four choices, which can be toggled. A submit button which can 
 be used to serially send the status of the four buttons when pressed. 
 IR sensor to detect occupancy. Time based.
*/

const int button1 = 2;  // Option A  
const int button2 = 3;  // Option B  
const int button3 = 4;  // Option C
const int button4 = 5;  // Option D
const int button5 = 6;  // Submit

const int irSensor = 8; // Occupancy

// HIGH when button pressed and LOW when button released:
int optionAc = 0;         
int optionBc = 0;         
int optionCc = 0;         
int optionDc = 0;         
int submit = 0;

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


void setup() {
  // initialize the button pin as a input:
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(button5, INPUT);
  pinMode(irSensor, INPUT);
  
  // initialize serial communication:
  Serial.begin(9600);
}


void loop() {
  // read the pushbutton input pin:
  optionAc = digitalRead(button1);
  optionBc = digitalRead(button2);
  optionCc = digitalRead(button3);
  optionDc = digitalRead(button4);
  submit = digitalRead(button5);
  occupied = digitalRead(irSensor);

  if (optionAc == HIGH && a == false) {
    a = true;
  }
  if (optionAc == LOW && a == true){
    a = false;
      if(aSelected == 0 ){
        Serial.println("A Selected");
          aSelected = 1;
        }
      else{
        Serial.println("A Unselected");
          aSelected = 0;
      }
  }

  if (optionBc == HIGH && b == false) {
    b = true;
  }
  if (optionBc == LOW && b == true){
    b = false;
      if(bSelected == 0 ){
        Serial.println("B Selected");
        bSelected = 1;
      }
      else{
        Serial.println("B Unselected");
        bSelected = 0;
      }
  }

  if (optionCc == HIGH && c == false) {
    c = true;
  }
  if (optionCc == LOW && c == true){
    c = false;
    if(cSelected == 0 ){
      Serial.println("C Selected");
      cSelected = 1;
    }
    else{
      Serial.println("C Unselected");
      cSelected = 0;
    }
  }

  if (optionDc == HIGH && d == false) {
    d = true;
  }
  if (optionDc == LOW && d == true){
    d = false;
    if(dSelected == 0 ){
      Serial.println("D Selected");
      dSelected = 1;
    }
    else{
      Serial.println("D Unselected");
      dSelected = 0;
    }
  }

  if( submit == HIGH && s == false){
    s = true;
  }
  if( submit == LOW && s == true){
    s = false;
    Serial.print(aSelected); 
    Serial.print("|"); 
    Serial.print(bSelected); 
    Serial.print("|"); 
    Serial.print(cSelected); 
    Serial.print("|"); 
    Serial.print(dSelected); 
    Serial.print("|"); 
    Serial.println();  
  }

  if( occupied == LOW ){
    sitting = sitting + 1;
  }
  
  otherwise = otherwise + 1;
  
  if(sitting == otherwise && sitting == 100){
    Serial.println("Chair is occupied");
  }
  else if(sitting != otherwise && otherwise == 100){
    Serial.println("Chair is not occupied");
  }

  if(otherwise == 100){
    otherwise = 0;
    sitting = 0;
  }

    // A reset variable that should be recieved by the arduino from the Pi. 
    // This will set all the options to 0.
  delay(50);
}

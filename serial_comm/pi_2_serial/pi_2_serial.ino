void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
//  Serial.println("From arduino");
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()){Serial.read();} //clear the input buffer
  Serial.println("From arduino");
  Serial.flush(); //wait for outgoing transmission to complete
  while(!Serial.available());
  flash(Serial.parseInt());
   

  delay(1000);
}

void flash(int n){
  if(n <= 0) return; 
  Serial.print("Flash times:");
  Serial.flush();
  Serial.println(n);
  Serial.flush();
  for(int i = 0; i < n; i++){
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
    Serial.println(i+1);
    Serial.flush();
  }
  Serial.println("Complete");
  Serial.flush();
}

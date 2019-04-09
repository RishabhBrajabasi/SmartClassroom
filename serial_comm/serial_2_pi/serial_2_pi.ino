void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(byte n = 0; n < 255; n++){
    Serial.println("WSN class project");
  }
}

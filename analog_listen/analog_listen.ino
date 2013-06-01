void setup() {
  // initialize the serial port:
  Serial.begin(28800);
}

void loop() {
 int line1 = 0;
 int line2 = 0;
 int line3 = 0;
 int line4 = 0;
 
 line1 = analogRead(8);
 line2 = analogRead(9);
 line3 = analogRead(10);
 line4 = analogRead(11); 
 
 Serial.println(line1);
 Serial.println(line2);
 Serial.println(line3);
 Serial.println(line4);
 Serial.println("----");
}

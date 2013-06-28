void setup() {
  // initialize the serial port:
  Serial.begin(115200);
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
 
 Serial.print(line1);
  Serial.print(" ");
 Serial.print(line2);
  Serial.print(" ");
 Serial.print(line3);
   Serial.print(" ");
 Serial.print(line4);
   Serial.print("\n");
}

// See SoftwareSerial example 
// https://www.arduino.cc/en/tutorial/SoftwareSerialExample


void setup() {
  Serial.begin(1200);
}

void loop() { // run over and over
  Serial.println("Hello world");
  delay(2000);
}

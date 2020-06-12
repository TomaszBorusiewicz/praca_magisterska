// See SoftwareSerial example 
// https://www.arduino.cc/en/tutorial/SoftwareSerialExample



void setup() {
  Serial.begin(9600);
  Serial1.begin(1200);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() { // run over and over
  if (Serial1.available() > 0){
    Serial.println(Serial1.readString());
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(500);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(500);
  }
  
}

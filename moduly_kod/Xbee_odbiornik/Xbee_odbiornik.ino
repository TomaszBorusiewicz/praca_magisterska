void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
   if (Serial1.available() > 0){ // Jeżeli interfejs serialowy jest dostępny
     String data = Serial1.readString(); // Zczytaj dane otrzymane od nadajnik
     Serial1.println(data); // Wyślij dane do Arduino mega 2560
     Serial.println(data); // Wyślij dane do Arduino mega 2560
     digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
     delay(1000);                       // wait for a second
     digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
   }
}

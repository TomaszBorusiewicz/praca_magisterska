void setup() {
  // Otwarcie portu do komunikacji
  Serial.begin(9600);
}
 
void loop() {
  Serial.print("Hello, world?");
  delay(2000);
}

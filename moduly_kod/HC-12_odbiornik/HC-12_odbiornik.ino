void setup() {
    // Otwarcie portu do komunikacji    
    Serial.begin(9600);
}
   
void loop() {
    if (Serial.available() > 0) {
    String input = Serial.readString();
    Serial.println(input);
    }
}

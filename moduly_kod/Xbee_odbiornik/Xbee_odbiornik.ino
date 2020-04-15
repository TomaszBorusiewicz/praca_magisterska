void setup() {
	Serial.begin(9600); // Zainicjalizuj serial z baudrate = 9600
}

void loop() {
 	if (Serial.available() > 0){ // Jeżeli serial jest dostępny
     Serial.write(Serial.read()); // Wyświetl na interfejsie serialowym to co odbiornik otrzymał od nadajnika
   }
}
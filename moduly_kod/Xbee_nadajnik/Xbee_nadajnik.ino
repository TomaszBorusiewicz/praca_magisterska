void setup() {
	Serial.begin(9600); // Zainicjalizuj serial z baudrate = 9600
}

void loop() {
 	Serial.println("Hello, world!"); // Wyślij na interfejs serialowy wiadomośc
	delay(2000); // poczekaj 2 sekundy
}
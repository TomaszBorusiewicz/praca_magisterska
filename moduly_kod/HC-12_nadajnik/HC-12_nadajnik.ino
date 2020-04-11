void setup() {
  Serial.begin(9600); // Inicjalizacja portu serialowego 
}
 
void loop() {
  Serial.print("Hello, world?"); // Wysyłanie w pętli wiadomości na port serialowy
  delay(2000); // przerwa 2s pomiędzy każdą iteracją w pętli
}

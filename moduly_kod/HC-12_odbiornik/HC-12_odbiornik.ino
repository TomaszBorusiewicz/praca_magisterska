void setup() {
    Serial.begin(9600); // Inicjalizacja portu serialowego 
}
   
void loop() {
    if (Serial.available() > 0) { // Warunek jeśli port serialowy jest dostępny ( ==1 )
    String input = Serial.readString(); // Przypisz zczytaną wartość z portu serialowego do zmiennej input
    Serial.println(input); // wyślij wartość zmiennej input na port serialowy
    }
}

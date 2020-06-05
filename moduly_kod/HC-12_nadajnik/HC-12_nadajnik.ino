#include "DHT.h"
#define DHTPIN 2 // Pin do którego podpięty jest DHT22
#define DHTTYPE DHT22 // Określenie typu czujnika DHT
DHT dht(DHTPIN, DHTTYPE); // Inicjalizacja instancji klasy DHT z numerem portu Arduino oraz typem czujnika
void setup() {
    Serial.begin(9600); // Inicjalizacja komunikacji serialowej
    dht.begin(); // Inicjalizacja komunikacji z DHT22
}
 
void loop() {
//  float t = dht.readTemperature(); // Zczytanie wartość temperatury z czujnika
//  if (not (isnan(t))){ // Jeżeli dane są poprawne
//    String t_string = String(t); // Konwersja zmiennej float na string
//    char data[6]; // Stworzenie zmiennej char
//    t_string.toCharArray(data, 6); // Przypisanie każdego znaku w zmiennej string to tablicy char
    Serial.println("NRF24L01: 25.60"); // Wysłanie danych do odbiornika HC-12
//  }
  delay(6000); // Pauza na 10 min
}

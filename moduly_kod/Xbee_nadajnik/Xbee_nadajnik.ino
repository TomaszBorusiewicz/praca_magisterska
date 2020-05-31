#include "DHT.h"
#define DHTPIN 2 // Pin do którego podpięty jest DHT22
#define DHTTYPE DHT22 // Określenie typu czujnika DHT
DHT dht(DHTPIN, DHTTYPE); // Inicjalizacja instancji klasy DHT
void setup() {
  Serial.begin(9600); // Inicjalizacja komunikacji serialowej
  Serial1.begin(9600);
  dht.begin(); // Inicjalizacja komunikacji z DHT22
}
void loop() {
  float t = dht.readTemperature(); // Zczytanie wartość temperatury z czujnika
  Serial.println(t);
  if (not (isnan(t))){ // Jeżeli dane są poprawne
    String t_string = String(t);
    Serial1.println(t_string); // Wysłanie danych
  }
  delay(5000); // Pauza na 30 min
}

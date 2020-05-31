#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "DHT.h"
#define DHTPIN 2 // Pin do którego podpięty jest DHT22
#define DHTTYPE DHT22 // Określenie typu czujnika DHT
RF24 radio(7, 8); // Inicjalizacja instancji klasy RF24 z numerami pinów CNS oraz CE
const byte address[6] = "00005"; // Inicjalizacja zmiennej address dzięki której urządzenia NRF24L01 będą mogły komunikować się między sobą
DHT dht(DHTPIN, DHTTYPE); // Inicjalizacja instancji klasy DHT
void setup() {
  Serial.begin(9600);
  dht.begin(); // Inicjalizacja komunikacji z DHT22
  radio.begin(); // Inicjalizacja obiektu radia RF24
  radio.openWritingPipe(address); // Przypisane adresu przez który wysyłana będzie wiadomość
  radio.setPALevel(RF24_PA_MIN); // Ograniczenie mocy nadajnika do minimum
  radio.stopListening(); // Wyłączenie nasłuchiwania
}
void loop() {
  float t = dht.readTemperature(); // Zczytanie wartość temperatury z czujnika
  if (not (isnan(t))){ // Jeżeli dane są poprawne
  String t_string = String(t);
  Serial.println(t_string);
  char data[6]; // Stworzenie zmiennej char i przypisane jej wartości temperatury
  t_string.toCharArray(data, 6);
  radio.write(&data, sizeof(data)); // Wysłanie danych
  }
  delay(6000); // Pauza na 10 min
}

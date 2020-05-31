#include <SPI.h>
#include <RH_RF95.h> 
#include "DHT.h"
#define DHTPIN 12 // Pin do którego podpięty jest DHT22
#define DHTTYPE DHT22 // Określenie typu czujnika DHT
#define RFM95_CS 8 // Określenie numery pinu CS
#define RFM95_RST 4 // Określenie numery pinu RST
#define RFM95_INT 3 // Określenie numery pinu INT
#define RF95_FREQ 434.0 // Częstotliwość pracy modułu LoRa
RH_RF95 rf95(RFM95_CS, RFM95_INT); // Inicjalizacja instancji klasy RH_RF95
DHT dht(DHTPIN, DHTTYPE); // Inicjalizacja instancji klasy DHT
void setup() 
{
  pinMode(RFM95_RST, OUTPUT); // Konfiguracja pinu RST jako wychodzący
  digitalWrite(RFM95_RST, HIGH); // Ustawienie stanu wysokiego dla pinu RST
  dht.begin(); // Inicjalizacja komunikacji z DHT22
  Serial.begin(9600); // Inicjalizacja komunikacji serialowej
  delay(100);
  Serial.println("Feather LoRa TX Test!");
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    while (1);
  }
  Serial.println("LoRa radio init OK!");
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
  rf95.setTxPower(5, false);
}
void loop()
{
  float t = dht.readTemperature(); // Pobranie wartości temperatury z czujnika DHT22
  if (not (isnan(t))){ // Jeżeli wartośc jest poprawna
    delay(1000);
    Serial.println("Transmitting...");
    String t_string = String(t); // Konwersja zmiennej typu float na String
    Serial.println(t_string); // Wyświetlenie temperatury na interfejsie serialowym
    char data[6]; // Tablica typu char do wysłania danych przez interfejs radiowy
    t_string.toCharArray(data, 6); // Przypisanie każdego znaku zmiennej string do osobnej komórki w tablicy char
    delay(10);
    rf95.send((uint8_t *)data, 6); // Wysłanie danych przez interfejs radiowy LoRa
    Serial.println("Waiting for packet to complete..."); 
    delay(10);
    rf95.waitPacketSent(); // Weryfikacja poprawnego wysłania danych
  }
 delay(6000); // delay 10 minutowy
}

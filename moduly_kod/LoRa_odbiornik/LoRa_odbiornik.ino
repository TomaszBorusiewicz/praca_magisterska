#include <SPI.h>
#include <RH_RF95.h>
 
// Inicjalizacja pinów dla radia LoRa RFM9X
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3

// Inicjalizacja częstotliwości dla radia LoRa RFM9X
#define RF95_FREQ 434.0

// Utworzenie instancji klasy RH_RF95 z wcześniej zdefiniowanymi zmiennymi
RH_RF95 rf95(RFM95_CS, RFM95_INT);
 
// Inicjalizacja LED do powiadomienia o otrzymaniu wiadomości
#define LED 13
 
void setup() 
{
  pinMode(LED, OUTPUT); // Ustawienie pinu LED jako wyjście
  pinMode(RFM95_RST, OUTPUT); // Ustawienie pinu do resetowania radia jako wyjście
  digitalWrite(RFM95_RST, HIGH); // Wysłanie na pin RFM95_RST stanu wysokiego (HIGH)
 
  Serial.begin(115200); // Inicjalizacja serialu
  while (!Serial){ // Oczekiwanie dopóki serial będzie dostępny
  delay(1); // Opóźnienie 100ms w celu poprawnej inicjalizacji serialu
  }

  // Czekaj aż radio zostanie zainicjalizowane
  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    while (1);
  }
  Serial.println("LoRa radio init OK!");
  
  // Warunek jeśli nie udało się ustawić częstotliwości na jakiej ma pracować radio wyświetl komunikat "setFrequency failed"
  // oraz czekaj aż częstotliwość zostanie ustawiona
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);

  // Ustawienie mocy nadajnika. Domyślna wartośc to 13 dBm. Możliwy przedział 5 - 23 dBm
  rf95.setTxPower(23, false);
}
 
void loop()
{
  if (rf95.available()) // Jeżeli radio jest dostępne / zainicjalizowane
  {
    // Stwórz zmienne do odbioru wiadomości i spradź czy wiadomośc nadeszła
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf); 
    if (rf95.recv(buf, &len)) // Jeżeli nadeszła wiadomośc
    {
      digitalWrite(LED, HIGH); // zapal diodę LED
      RH_RF95::printBuffer("Received: ", buf, len); // wyświetl zawartość bufora buf
      
      // Wyświetl dane pochodzące od nadajnika
      Serial.print("Got: ");
      Serial.println((char*)buf);
      Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC);
      
      // Utwórz wiadomość zwrotną i ją wyślij
      uint8_t data[] = "And hello back to you";
      rf95.send(data, sizeof(data));
      rf95.waitPacketSent();
      Serial.println("Sent a reply");
      digitalWrite(LED, LOW); // Zgaś diodę LED
    }
    // Jeżeli wiadomość nie nadeszła wyświetl komunikat o jej braku
    else
    {
      Serial.println("Receive failed");
    }
  }
}
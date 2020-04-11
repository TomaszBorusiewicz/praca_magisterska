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
 
void setup() 
{
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
  char radiopacket[20] = "Hello World?"; // Stworzenie wiadomości do wysłania
  Serial.print("Sending..."); Serial.println(radiopacket); // Wyświetlenie wiadomości do wysłania na interfejsie serialowym
  delay(10);
  rf95.send((uint8_t *)radiopacket, 20); // Wysłanie wiadomości poprzez radio LoRa
  Serial.println("Waiting for packet to complete..."); delay(10); // Wyświetlenie wiadomości "Waiting for packet to complete..." na interfejsie serialowym
  rf95.waitPacketSent(); // Czekaj aż wiadomości zostanie wysłana
  
  // Czekaj na wiadomość zwrotną od drugiego urządzenia
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN]; // Utwórz tablicę z maksymalnym rozmiarem wiadomości
  uint8_t len = sizeof(buf); // Pobierz wielkość zmiennej buf

  // Sprawdź czy nadajnik otrzymał odpowiedź od nadajnika
  if (rf95.waitAvailableTimeout(1000))
  { 
    if (rf95.recv(buf, &len))
   {
      Serial.print("Got reply: ");
      Serial.println((char*)buf);
      Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC);    
    }
    else
    {
      Serial.println("Receive failed");
    }
  }
  else
  {
    Serial.println("No reply, is there a listener around?");
  }
  delay(1000);
}
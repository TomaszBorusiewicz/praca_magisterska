#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Inicjalizacja instancji klasy RF24 z numerami pinów CNS oraz CE
RF24 radio(7, 8);
// Inicjalizacja zmiennej address dzięki której urządzenia NRF24L01 będą
// mogły komunikować się między sobą
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600); // Inicjalizacja interfejsu serialowego
  radio.begin(); // Inicjalizacja obiektu radia RF24
  radio.openReadingPipe(0, address);  // Przypisane adresu przez który odbierana będzie wiadomość
  radio.setPALevel(RF24_PA_MIN); // Ograniczenie mocy nadajnika do minimum
  radio.startListening(); // Uruchomienie nasłuchiwania
}

void loop() {
  // Jeżeli radio jest dostępne zczytaj wiadomość z interfejsu radiowego
  // i wyświetl go na interfejsie serialowym
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
}

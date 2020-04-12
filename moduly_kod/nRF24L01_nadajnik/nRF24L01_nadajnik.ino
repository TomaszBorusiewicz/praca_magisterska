#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Inicjalizacja instancji klasy RF24 z numerami pinów CNS oraz CE
RF24 radio(7, 8);
// Inicjalizacja zmiennej address dzięki której urządzenia NRF24L01 będą
// mogły komunikować się między sobą
const byte address[6] = "00001";

void setup() {
  radio.begin(); // Inicjalizacja obiektu radia RF24
  radio.openWritingPipe(address); // Przypisane adresu przez który wysyłana będzie wiadomość
  radio.setPALevel(RF24_PA_MIN); // Ograniczenie mocy nadajnika do minimum
  radio.stopListening(); // Wyłączenie nasłuchiwania
}

void loop() {
  // Utwórz wiadomość i wyślij ją poprzez interfejs radiowy
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  delay(1000);
}

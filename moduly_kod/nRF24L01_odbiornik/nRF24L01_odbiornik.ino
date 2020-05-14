#include <SoftwareSerial.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// ###################### HC-12 ################################
SoftwareSerial HC12(10, 11);
// ###################### HC-12 ################################

// ###################### LORA ################################
SoftwareSerial LORA(12, 13);
// ###################### LORA ################################

// ###################### NRF24L01 #############################
// Inicjalizacja instancji klasy RF24 z numerami pinów CNS oraz CE
RF24 radio(7, 8);
// Inicjalizacja zmiennej address dzięki której urządzenia NRF24L01 będą
// mogły komunikować się między sobą
const byte address[6] = "00001";
// ##################### NRF24L01 ##############################


void setup() {
  Serial.begin(9600); // Inicjalizacja interfejsu serialowego
  HC12.begin(9600);
  LORA.begin(9600);
  radio.begin(); // Inicjalizacja obiektu radia RF24
  radio.openReadingPipe(0, address);  // Przypisane adresu przez który odbierana będzie wiadomość
  radio.setPALevel(RF24_PA_MIN); // Ograniczenie mocy nadajnika do minimum
  radio.startListening(); // Uruchomienie nasłuchiwania
}

void loop() {
  if (HC12.available()) { // Jeżeli interfejs HC12 jest dostępny
    String hc12_output = HC12.readString(); // Zczytaj dane przesłane od nadajnika
    Serial.println(hc12_output); // Wyświetl dane na interfejsie serialowym
  }
  if (LORA.available()) { // Jeżeli interfejs HC12 jest dostępny
    String LORA_output = LORA.readString(); // Zczytaj dane przesłane od nadajnika
    Serial.println(LORA_output); // Wyświetl dane na interfejsie serialowym
  }
  // Jeżeli radio jest dostępne zczytaj wiadomość z interfejsu radiowego
  // i wyświetl go na interfejsie serialowym
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
}

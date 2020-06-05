#include <SoftwareSerial.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // Inicjalizacja instancji klasy nRF24L01 z numerami pinów CNS oraz CE
const byte address[6] = "00005"; // Inicjalizacja zmiennej address dzięki której urządzenia NRF24L01 będą mogły komunikować się między sobą
void setup() {
  Serial.begin(9600); // Inicjalizacja komunikacji serialowej do Raspberry pi
  Serial1.begin(9600); // Inicjalizacja komunikacji serialowej do LoRa
  Serial2.begin(9600); // Inicjalizacja komunikacji serialowej do XBee
  Serial3.begin(9600); // Inicjalizacja komunikacji serialowej do HC-12
  radio.begin(); // Inicjalizacja obiektu radia RF24
  radio.openReadingPipe(0, address);  // Przypisane adresu przez który odbierana będzie wiadomość
  radio.setPALevel(RF24_PA_MIN); // Ograniczenie mocy nadajnika do minimum
  radio.startListening(); // Uruchomienie nasłuchiwania
}
void loop() {
  if (Serial3.available() > 0) { // Jeżeli interfejs HC12 jest dostępny
    String HC12_output = Serial3.readString(); // Zczytanie danych przesłanych od nadajnika HC-12
    if (HC12_output.length() > 0){
      Serial.println("HC-12: " + HC12_output);
    }
  }
  if (Serial1.available() > 0) { // Jeżeli interfejs LoRa jest dostępny
    String LORA_output = Serial1.readString(); // Zczytanie danych przesłanych od nadajnika LoRa
    if (LORA_output.length() > 0){ // Jeżeli długość stringa jest większa niż 0 
      Serial.println("LoRa: " + LORA_output); // Wypisz wartośc na porcie serialowym
    }
  }
  if (Serial.available() > 0) { // Jeżeli interfejs nRF24L01 jest dostępny
//    char data[6]; // Utworzenie zmiennej do której zapisywane są dane z nRF24L01
//    radio.read(&data, sizeof(data));// Zczytanie danych przesłanych od nadajnika nRF24L01
//    String NRF24L01_output = String(data);
//    if (NRF24L01_output.length() > 0){ // Jeżeli długość stringa jest większa niż 0
//      Serial.println("NRF24L01: " + NRF24L01_output); // Wypisz wartośc na porcie serialowym
     Serial.println(Serial.readString());
//     delay(6000);
    }
//  }
 if (Serial2.available() > 0){ // Jeżeli interfejs Xbee jest dostępny
   String Xbee_output = Serial2.readString(); // Zczytanie danych przesłanych od nadajnika Xbee
   if (Xbee_output.length() > 0){ // Jeżeli długość stringa jest większa niż 0
     Serial.println("XBee: " + Xbee_output); // Wypisz wartośc na porcie serialowym
   }
 }
}

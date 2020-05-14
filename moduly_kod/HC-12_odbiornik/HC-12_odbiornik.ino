#include <SoftwareSerial.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

SoftwareSerial HC12(10, 11);

RF24 radio(7, 8);
const byte address[6] = "00001";

void setup() {
    Serial.begin(9600); // Inicjalizacja portu serialowego
    HC12.begin(9600);
    radio.begin(); // Inicjalizacja obiektu radia RF24
    radio.openReadingPipe(0, address);  // Przypisane adresu przez który odbierana będzie wiadomość
    radio.setPALevel(RF24_PA_MIN); // Ograniczenie mocy nadajnika do minimum
    radio.startListening(); // Uruchomienie nasłuchiwania
}
   
void loop() {
    if (Serial.available() > 0) { // Warunek jeśli port serialowy jest dostępny ( ==1 )
      String input = Serial.readString(); // Przypisz zczytaną wartość z portu serialowego do zmiennej input
      if (radio.available()) {
        char text[32] = "";
        radio.read(&text, sizeof(text));
        Serial.println(text);
      }
      Serial.println(input); // wyślij wartość zmiennej input na port serialowy
    }
    //else {
    //  Serial.println("Nie udało się");
    //}

//    while (HC12.available()) {        // If HC-12 has data
//      Serial.println(HC12.read());      // Send the data to Serial monitor
//      Serial.println("HC12 dostępny");
//    }
//    if (Serial.available()) {      // If Serial monitor has data
//    int myarray[] = {2, 5, 10, 14, 11};
//    int array_length = sizeof(myarray);
//    int i;
//    for (i=0;i<array_length;i++){
//      Serial.print(myarray[i]);      // Send that data to HC-12    
//    }
    
//    delay(2000);
//      Serial.println("Serial dostępny");
//    }
}

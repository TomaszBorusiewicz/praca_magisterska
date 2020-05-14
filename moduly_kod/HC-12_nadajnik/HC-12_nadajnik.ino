#include <SoftwareSerial.h>

SoftwareSerial HC12(10, 11);

void setup() {
    Serial.begin(9600); // Inicjalizacja portu serialowego
    HC12.begin(9600);
}
 
void loop() {
  //Serial.print("Hello, world?"); // Wysyłanie w pętli wiadomości na port serialowy
  //delay(2000); // przerwa 2s pomiędzy każdą iteracją w pętli

//  while (HC12.available()) {        // If HC-12 has data
//      Serial.println(HC12.read()); // Send the data to Serial monitor
//      Serial.println("HC12 Dostępny");
//    }
//  while (Serial.available()) {      // If Serial monitor has data
    HC12.print("HC-12");      // Send that data to HC-12
    Serial.print("HC-12");
    delay(5000);
//      Serial.println("Serial dostępny");
//    }
  
}

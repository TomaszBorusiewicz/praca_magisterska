//#include <SPI.h>
//#include <RH_RF95.h>
//#define RFM95_CS 8 // Numer pinu CS
//#define RFM95_RST 4 // Numer pinu RST
//#define RFM95_INT 3 // Numer pinu INT
//#define RF95_FREQ 434.0 // Określenie częstotliwości na której pracuje radio Lor
//RH_RF95 rf95(RFM95_CS, RFM95_INT); // Inicjalizacja instancji klasy rf95
//void setup()
//{
//  pinMode(RFM95_RST, OUTPUT); // Ustawienie pinu RST jako wyjściowy
//  digitalWrite(RFM95_RST, HIGH); // Przypisane stanu wysokiego pinowi RST
//  Serial.begin(9600); // Inicjalizacja komunikacji serialowej do Arduino mega 2560
//}
// 
//void loop()
//{
//  if (rf95.available()) // Jeżeli interfejs radiowy jest dostępny
//  {
//    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN]; // Utworzenie zmiennej na otrzymane dane
//    uint8_t len = sizeof(buf); // Obliczenie długości zmiennej na dane
//    if (rf95.recv(buf, &len)) // Jeżeli odbiornik otrzymał dane
//    {
//      Serial.println((char*)buf); // Wyślij dane do urządzenia Arduino mega 2560
//    }
//  }
//}

#include <SPI.h>
#include <RH_RF95.h>

#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3
 
// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 434.0
 
// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);
 
// Blinky on receipt
#define LED 13

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  Serial1.begin(9600);
  Serial.begin(9600);
  while (!Serial) {
    delay(1);
  }
  delay(100);
 
  Serial.println("Feather LoRa RX Test!");
 
  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
 
  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    Serial.println("Uncomment '#define SERIAL_DEBUG' in RH_RF95.cpp for detailed debug info");
    while (1);
  }
  Serial.println("LoRa radio init OK!");
 
  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
 
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
 
  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then
  // you can set transmitter powers from 5 to 23 dBm:
  rf95.setTxPower(5, false);
}
 
void loop()
{
  if (rf95.available())
  {
    // Should be a message for us now
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf95.recv(buf, &len))
    {
      digitalWrite(LED, HIGH);
      RH_RF95::printBuffer("Received: ", buf, len);
      Serial.print("Got: ");
      Serial.println((char*)buf);
      Serial1.println((char*)buf);
      Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC);
    }
  }
}

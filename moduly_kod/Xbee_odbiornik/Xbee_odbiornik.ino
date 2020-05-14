#include <XBee.h>

XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
// create reusable response objects for responses we expect to handle 
Rx16Response rx16 = Rx16Response();
Rx64Response rx64 = Rx64Response();

uint8_t option = 0;
uint8_t data = 0;

void setup() {
//  Serial.begin(9600); // Zainicjalizuj serial z baudrate = 9600
   // start serial
  Serial.begin(9600);
  xbee.setSerial(Serial);
}

void loop() {
   xbee.readPacket();
    
    if (xbee.getResponse().isAvailable()) {
      // got something
      
      if (xbee.getResponse().getApiId() == RX_16_RESPONSE || xbee.getResponse().getApiId() == RX_64_RESPONSE) {
        // got a rx packet
        
        if (xbee.getResponse().getApiId() == RX_16_RESPONSE) {
                xbee.getResponse().getRx16Response(rx16);
          option = rx16.getOption();
          data = rx16.getData(0);
        } else {
                xbee.getResponse().getRx64Response(rx64);
          option = rx64.getOption();
          data = rx64.getData(0);
          Serial.println(data);
        }
}
    }
}

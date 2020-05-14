#include <XBee.h>

XBee xbee = XBee();
unsigned long start = millis();
//Tx16Request tx = Tx16Request(0x1874, "hello world", sizeof("hello world"));

// 64-bit addressing: This is the SH + SL address of remote XBee
XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, 0x417C481E);
// unless you have MY on the receiving radio set to FFFF, this will be received as a RX16 packet
Tx64Request tx = Tx64Request(addr64, "hello world", sizeof("hello world"));

TxStatusResponse txStatus = TxStatusResponse();

void setup() {
  Serial.begin(9600);
  xbee.setSerial(Serial); 
}
void loop() {
  if (millis() - start > 15000) {
      xbee.send(tx);
    }
  if (xbee.readPacket(5000)) {
        // got a response!

        // should be a znet tx status              
      if (xbee.getResponse().getApiId() == TX_STATUS_RESPONSE) {
         xbee.getResponse().getTxStatusResponse(txStatus);

  delay(2000);
}
}
}

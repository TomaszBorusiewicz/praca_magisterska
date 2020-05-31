void setup() {
  Serial1.begin(9600);
}

void loop() {
   if (Serial1.available() > 0){ // Jeżeli interfejs serialowy jest dostępny
     String data = Serial1.readString(); // Zczytaj dane otrzymane od nadajnik
     Serial1.println(data); // Wyślij dane do Arduino mega 2560
   }
}

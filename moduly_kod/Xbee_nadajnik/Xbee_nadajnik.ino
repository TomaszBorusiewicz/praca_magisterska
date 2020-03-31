const int potPin = A0;
int value ;

void setup() {
	Serial.begin(9600);
}

void loop() {
  	value = analogRead(A0);
  	value = map (value, 0, 1023, 0, 255);
	Serial.print('<');
 	Serial.print(value);
	Serial.println('>');
}
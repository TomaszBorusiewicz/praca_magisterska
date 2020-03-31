bool started= false;
bool ended 	= false;
char incomingByte ; 
char msg[3];		
byte index;			

void setup() {

	Serial.begin(9600);
}

void loop() {
	
  while (Serial.available()>0){
    incomingByte = Serial.read();
    if(incomingByte == '<')
    {
     started = true;
     index = 0;
     msg[index] = '\0';
   }
   else if(incomingByte == '>')
   {
     ended = true;
     break;
   }
   else
   {
     if(index < 4)
     {
       msg[index] = incomingByte;
       index++;
       msg[index] = '\0';
     }
   }
  }
}
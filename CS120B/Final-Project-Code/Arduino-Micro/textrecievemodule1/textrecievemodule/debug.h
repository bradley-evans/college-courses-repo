void blink(int h, int l) {
	digitalWrite(11, HIGH);  
	delay(h);              
	digitalWrite(11, LOW);   
	delay(l);             
}

void errorblink() {
  unsigned char counter = 0;
  while (counter < 4 ) {
    digitalWrite(12, HIGH);  
    delay(50);              
    digitalWrite(12, LOW);   
    delay(50);    
    digitalWrite(12, HIGH);  
    delay(50);              
    digitalWrite(12, LOW);   
    delay(50);    
    digitalWrite(12, HIGH);  
    delay(50);              
    digitalWrite(12, LOW);   
    delay(1000);    
    counter++;
  }
}

void goodblink() {
  unsigned char counter = 0;
  while (counter < 4 ) {
    digitalWrite(11, HIGH);  
    delay(50);              
    digitalWrite(11, LOW);   
    delay(50);    
    digitalWrite(11, HIGH);  
    delay(50);              
    digitalWrite(11, LOW);   
    delay(50);    
    digitalWrite(11, HIGH);  
    delay(50);              
    digitalWrite(11, LOW);   
    delay(1000);    
    counter++;
  }
}
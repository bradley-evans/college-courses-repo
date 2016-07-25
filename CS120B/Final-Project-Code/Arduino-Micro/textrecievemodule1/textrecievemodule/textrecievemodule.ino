// include the SD library:
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
// Software Serial library: 
#include <SoftwareSerial.h>
// personal debugging routines
#include "debug.h"
/* 
 *  
 *  THIS IS THE SLAVE RECEIVING MODULE
 *  IT WILL WRITE DATA TO AN SD CARD
 */

// GLOBAL VARIABLES
const int chipSelect = 10; // 10 because this is an Adafruit SD module.
File data;
int buttonA; // the button
char c;

void sd_readstart() {
  unsigned char i = 0;
  // Open serial communications and wait for port to open:
  Serial.print("\nInitializing SD card...");
  if (!SD.begin(10)) {
    Serial.println("Card initialization failed.");
    errorblink();
    return;
  }
  Serial.println("Initialization successful.");
  
}
void recievedata() {
 
}



void setup() {
  pinMode(11, OUTPUT); // setup for blink
  pinMode(12, OUTPUT); // setup for blink
  pinMode(10, INPUT); // button
  Wire.begin(8); // intitalize this device as a slave on addr 8.
  Wire.onReceive(receiveEvent); // when data is recieved, run recieveEvent(int).
  Serial.begin(9600);
  sd_readstart();

  


}

void loop(void) {
  // short blink to confirm this is going down correctly 
//  buttonA = digitalRead(10);
//  if (buttonA == HIGH) {
//    // button open
//    blink(100,1000);
//  } else {
//    // button pressed
//  
//  }
  
}


void receiveEvent(int howMany) {
  //data = SD.open("testoutput.txt");
  digitalWrite(12,HIGH);
  while (Wire.available() > 0) { // loop through all but the last
    c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
    //data.print(c);
  }
  //data.close();
  digitalWrite(12,LOW);
}

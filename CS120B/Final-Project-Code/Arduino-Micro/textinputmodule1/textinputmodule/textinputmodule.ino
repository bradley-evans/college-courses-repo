// include the SD library:
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
// Software Serial library: 
#include <SoftwareSerial.h>
// personal debugging routines
#include "debug.h"

#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

// GLOBAL VARIABLES
const int chipSelect = 10;  // 10 because this is an Adafruit SD module.
int buttonA, card_detect, engage, recieve;   // inputs
File data;
char pt_data, ct_data;
int i;
char longkey[20] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t'};
float filesize, currentsizetxfr, percentdone;
Adafruit_7segment matrix = Adafruit_7segment();


void sd_readstart() {
  unsigned char i = 0;
  // Open serial communications and wait for port to open:
  Serial.print("\nInitializing SD card...");
  if (!SD.begin(10)) {
    Serial.println("Card initialization failed.");
    //errorblink();
    return;
  }
  Serial.println("Initialization successful.");
}

char encrypt(char c, int i) {
   // xor algorithm -- just a bitwise xor against the key
   // this constitutes a simple substitution cipher
   // and is easily reversible
   return (c ^ longkey[i]);
//   char simplekey = 'A';
//   return (c ^ simplekey);
}

void getdatasize() {
  filesize = 0;
  data = SD.open("test.txt");
  while (data.available()) {
    pt_data = data.read();
    filesize++;
  }
  data.close();
}

void senddata() {
  currentsizetxfr = 0;
  data = SD.open("test.txt");
  digitalWrite(12, HIGH);
    matrix.print(9999);
    matrix.writeDisplay();
  
  while (data.available()) {
      Wire.beginTransmission(8); // transmit to device #8
      while (data.available() && i < 20) {
        pt_data = data.read();
        ct_data = encrypt(pt_data,i);
        Wire.write(ct_data);
        currentsizetxfr++;
        i++;
      }
      i=0;
      Wire.endTransmission();
      percentdone = (currentsizetxfr/filesize)*100;
      matrix.print((int)percentdone, DEC);
      matrix.writeDisplay();
  }
  data.close();
  digitalWrite(12,LOW);
}

void getkey() {
  byte key_recieved = 0;
  for (int i = 0; i<8; i++) {
    if (digitalRead(i+4) == 0) {
      bitWrite(key_recieved, i, 0);
    } else {
      bitWrite(key_recieved, i, 1);
    }
  }
  longkey[0] = (char)key_recieved;
  digitalWrite(A2, HIGH);
  digitalWrite(A4, HIGH);   // acknowledge reciept of key-byte
}

void setup() {
  pinMode(12, OUTPUT);  // setup for blink
  pinMode(A0, INPUT);   // EN   engage cryptomodule
  // digitalWrite(A0, HIGH); // set pullup
  pinMode(A1, INPUT);   // REC  recieve
  // digitalWrite(A0, HIGH); // set pullup
  pinMode(A2, OUTPUT);  // ACK  acknowledge
  pinMode(A4, OUTPUT);  // ACK-indicator
  // the keybyte receiver
  pinMode(4,INPUT);     // 0
  pinMode(5,INPUT);     // 1
  pinMode(6,INPUT);     // 2
  pinMode(7,INPUT);     // 3
  pinMode(8,INPUT);     // 4
  pinMode(9,INPUT);     // 5
  pinMode(10,INPUT);    // 6
  pinMode(11,INPUT);    // 7
  
  sd_readstart();
  Serial.begin(9600);
  Wire.begin(9);
  matrix.begin(0x70);
  matrix.print(1010,DEC);
  matrix.writeDisplay();
}

void loop(void) {
  // short blink to confirm this is going down correctly 
  

  digitalWrite(12,LOW);
  engage = digitalRead(A0); 
  recieve = digitalRead(A1);

  if (engage == HIGH && recieve == LOW) {
    // engage = 1; recieve = 0
    matrix.print(1111);
    matrix.writeDisplay();
    getdatasize();
    senddata();
    digitalWrite(A2, LOW);   // disable ack signal
    digitalWrite(A4, LOW);   // disable ack indicator
    goodblink();
    while (engage == HIGH) {
      engage = digitalRead(A0);
      digitalWrite(A2, LOW);   // disable ack signal
      delay(200);
      digitalWrite(A2,HIGH);
      delay(200);
      matrix.print(4444);
      matrix.writeDisplay();
    }
    digitalWrite(A2, LOW); 
    matrix.print(1010,DEC);
    matrix.writeDisplay();
  } else if (recieve == HIGH && engage == LOW) {
    // receive = 1; engage = 0
    matrix.print(8888,DEC);
    matrix.writeDisplay();
    getkey();
  } else {
    blink(50,450);
  }

}

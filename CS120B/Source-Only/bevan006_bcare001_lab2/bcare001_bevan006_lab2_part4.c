/*
 * bcare001_lab2_part4.c - 3/30/2016
 *
 *
 * Author : Bradd Carey - bcare001@ucr.edu
            bcare001
 * Partner: Brad Evans - bevan006@ucr.edu
 *
 * Lab Section: 21 
 *
 * Assignment: Lab 2 - Exercise 4
 *
 * I acknowledge all content contained herein, excluding template
 * or example code, is my own original work unless otherwise
 * stated.
 */ 
 
 #include <avr/io.h>
// Bit-access function
unsigned char setBit(unsigned char x, unsigned char k, unsigned char b) {
    return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}

unsigned char getBit(unsigned char x, unsigned char k) {
    return ((x & (0x01 << k)) != 0);
}
int main(void) {
	//Assign and initialize Ports
	DDRA = 0x00; 
	DDRB = 0xFF; 
	DDRC = 0xFF;
	PORTA = 0x00; //Initialize inputs to 0
	PORTB = 0x00; //Initialize outputs to 0
	PORTC = 0x00; //Initialize outputs to 0
	unsigned char tempC = 0x00;
	unsigned char tempB = 0x00;
	
    while(1) {
		tempC = 0x00;
		tempB = 0x00;
		
        for(unsigned int i = 0; i<8; i++){
			if(i < 4){
				tempC = setBit(tempC,i+4,getBit(PINA,i));
			}else{
				tempB = setBit(tempB,i-4,getBit(PINA,i));
			}
		}
		PORTB = tempB;
		PORTC = tempC;
	}
}


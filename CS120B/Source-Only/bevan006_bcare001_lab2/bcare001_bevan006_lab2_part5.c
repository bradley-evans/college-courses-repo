/*
 * bcare001_lab2_part5.c - 3/30/2016
 *
 *
 * Author : Bradd Carey - bcare001@ucr.edu
            bcare001
 * Partner: Brad Evans - bevan006@ucr.edu
 *
 * Lab Section: 21 
 *
 * Assignment: Lab 2 - Exercise 5
 *
 * I acknowledge all content contained herein, excluding template
 * or example code, is my own original work unless otherwise
 * stated.
 */ 
 
 #include <avr/io.h>
// Bit-access functions
unsigned char setBit(unsigned char x, unsigned char k, unsigned char b) {
    return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char getBit(unsigned char x, unsigned char k) {
    return ((x & (0x01 << k)) != 0);
}

int main(void) {
	//Assign and initialize Ports
	DDRB = 0xFE; //Output, PB1 Input
	DDRD = 0x00; //Inputs
	PORTB = 0x01; //Initialize inputs to 0
	PORTD = 0x00; //Initialize outputs to 0
	unsigned char airbag;
	unsigned int total_weight;
	unsigned char temp;
	
    while(1) {
		temp = 0x01 & PINB;
		airbag = 0;
		total_weight = (PIND * 2) + getBit(PINB,0);
		//If weight is greater than 70, enable airbag/disable led
		if(total_weight>=70){
			airbag = setBit(airbag,1,1);
			airbag = setBit(airbag,2,0);
		//If weight is between 5 and 70 disable airbag/enable led
		}else if(total_weight>5){
			airbag = setBit(airbag,1,0);	
			airbag = setBit(airbag,2,1);
		}else{
			airbag = setBit(airbag,1,0);
			airbag = setBit(airbag,2,0);
		}
		PORTB = airbag | temp;
	}
}




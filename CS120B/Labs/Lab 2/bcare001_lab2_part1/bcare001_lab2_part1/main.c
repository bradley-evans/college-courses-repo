/*
 * bcarey_lab2_part1.c - 3/30/2016
 *
 * Author : Braddley Carey - bcare001@ucr.edu
 *			bcare001
 *
 * Partner:	Brad Evans - bevan006@ucr.edu
 *
 * Lab Section: 21 
 *
 * Assignment: Lab 2 - Exercise 1
 *
 * I acknowledge all content contained herein, excluding template
 * or example code, is my own original work unless otherwise
 * stated.
 */ 

#include <avr/io.h>

//Function Definitions
unsigned char setBit(unsigned char x, unsigned char k, unsigned char b){
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char getBit(unsigned char x, unsigned char k){
	return ((x & (0x01 << k)) != 0);
}

int main(void)
{
	//Assign and initialize Ports
	DDRA = 0x00; //Configure port A as inputs
	DDRB = 0x00;
	DDRC = 0xFF; //Configure port C as output
	PORTA = 0x00; //Initialize inputs to 0
	PORTA = 0x00; //Initialize inputs to 0
	PORTC = 0x00; //Initialize outputs to 0
	
	//Define Variables
	unsigned char count = 0x00;
	
    while (1){
		count = 0x00;
		for (unsigned int i=0; i<8; i++){
			if(getBit(PINA,i)){
				count++;
			}
			if(getBit(PINB,i)){
				count++;
			}
		}
		PORTC = count;
    }
}







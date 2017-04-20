/*
 * bcarey_lab1_part2.c - 3/30/2016
 *
 * Author : Braddley Carey - bcare001@ucr.edu
 *			bcare001
 *
 * Partner:	Brad Evans - bevan006@ucr.edu
 *
 * Lab Section: 21 
 *
 * Assignment: Lab 1 - Exercise 2
 *
 * I acknowledge all content contained herein, excluding template
 * or example code, is my own original work unless otherwise
 * stated.
 */ 

#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; //Configure port A as inputs
	DDRC = 0xFF; //Configure port C as output
	PORTA = 0xFF; //Initialize outputs to 0
	PORTC = 0x00; //Initialize inputs to 0
	
    while (1){
		unsigned char cntavail = 0x04;
		//If PA0==1 then PA1==1
		if(PINA & 0x01){
			cntavail--;
		}
		//If PA0==1 then PA1==1
		if(PINA & 0x02){
			cntavail--;
		}
		//If PA0==1 then PA1==1
		if(PINA & 0x04){
			cntavail--;
		}
		//If PA0==1 then PA1==1
		if(PINA & 0x08){
			cntavail--;
		}
		PORTC = cntavail;
    }
}




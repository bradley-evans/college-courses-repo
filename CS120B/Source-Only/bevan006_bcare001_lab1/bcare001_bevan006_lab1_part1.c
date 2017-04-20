/*
 * bcarey_lab1_part1.c - 3/30/2016
 *
 * Author : Braddley Carey - bcare001@ucr.edu
 *			bcare001
 *
 * Partner:	Brad Evans
 *
 * Lab Section: 21 
 *
 * Assignment: Lab 1 - Exercise 1
 *
 * I acknowledge all content contained herein, excluding template
 * or example code, is my own original work unless otherwise
 * stated.
 */ 

#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; //Configure port A as inputs
	DDRB = 0xFF; //Configure port B as output
	PORTA = 0xFF; //Initialize outputs to 0
	PORTB = 0x00; //Initialize inputs to 0
	unsigned char temp = 0x00;
	
    while (1){
		//If PA0==1 then PA1==1
		if(PINA == 0x01){
			temp =  0x01;
		//If PA0==0 then PA0==0
		}else{
			temp = 0x00;	
		}
		PORTB = temp;
    }
}


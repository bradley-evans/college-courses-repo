/*
 * bcarey_lab8_part1.c - 4/20/2016
 *
 * Author : Braddley Carey - bcare001@ucr.edu
 *			bcare001
 *
 * Partner:	Brad Evans - bevan006@ucr.edu
 *
 * Lab Section: 21 
 *
 * Assignment: Lab 8 - Exercise 1
 *
 * I acknowledge all content contained herein, excluding template
 * or example code, is my own original work unless otherwise
 * stated.
 */ 

#include <avr/io.h>

void ADC_init(){
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}
int main(){
	
	//Initialize Registers
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0x03; PORTD = 0x00;
	
	ADC_init();
	unsigned short tempADC;
	
	while(1){
		tempADC = ADC;
		PORTB = (char)tempADC;
		PORTD = (char)( tempADC >> 8 );
	}
}

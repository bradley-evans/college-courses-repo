/*
 * bcarey_lab8_part4.c - 4/20/2016
 *
 * Author : Braddley Carey - bcare001@ucr.edu
 *			bcare001
 *
 * Partner:	Brad Evans - bevan006@ucr.edu
 *
 * Lab Section: 21 
 *
 * Assignment: Lab 8 - Exercise 4
 *
 * I acknowledge all content contained herein, excluding template
 * or example code, is my own original work unless otherwise
 * stated.
 */ 

#include <avr/io.h>

void ADC_init(){
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

const unsigned short MAX_LIGHT = 0x0180;

void lightlevel(){
	unsigned short current_ADC = ADC;
	unsigned char leds = current_ADC/(MAX_LIGHT>>3);
	unsigned char tempB;
	switch(leds){
		case 8:
			tempB = 0xFF; break;
		case 7:
			tempB = 0x7F; break;
		case 6:
			tempB = 0x3F; break;
		case 5:
			tempB = 0x1F; break;
		case 4:
			tempB = 0x0F; break;
		case 3:
			tempB = 0x07; break;
		case 2:
			tempB = 0x03; break;
		case 1:
			tempB = 0x01; break;
		case 0:
			tempB = 0x00; break;
	}
	PORTB = tempB;
}
int main(){
	
	//Initialize Registers
	DDRB = 0xFF; PORTB = 0x00;
	
	ADC_init();
	
	while(1){
		lightlevel();
	}
}

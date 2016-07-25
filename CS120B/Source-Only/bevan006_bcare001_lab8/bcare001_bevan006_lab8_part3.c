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
	unsigned char leds = current_ADC/(MAX_LIGHT>>1);
	unsigned char tempB;
	if(leds){
		tempB = 0x01;
	}else{
		tempB = 0x00;
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

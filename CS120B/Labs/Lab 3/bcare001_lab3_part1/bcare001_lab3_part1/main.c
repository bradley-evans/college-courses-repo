/*
 * bcarey_lab3_part1.c - 3/30/2016
 *
 * Author : Braddley Carey - bcare001@ucr.edu
 *			bcare001
 *
 * Partner:	Brad Evans - bevan006@ucr.edu
 *
 * Lab Section: 21 
 *
 * Assignment: Lab 3 - Exercise 1
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
unsigned char tempB;

enum LED_States { LED_init, LED_wait1, LED_led2_on, LED_wait2, LED_led1_on } LED_State;

void TickFct_led_latch() {
	switch(LED_State) { // Transitions
		case LED_init:
			if (1) {
				LED_State = LED_wait1;
			}
			break;
		case LED_wait1:
			if (getBit(PINA,0)) {
				LED_State = LED_led2_on;
			}
			else if (!getBit(PINA,0)) {
				LED_State = LED_wait1;
			}
			break;
		case LED_led2_on:
			if (!getBit(PINA,0)) {
				LED_State = LED_wait2;
			}
			else if (getBit(PINA,0)) {
				LED_State = LED_led2_on;
			}
			break;
		case LED_wait2:
			if (getBit(PINA,0)) {
				LED_State = LED_led1_on;
			}
			else if (!getBit(PINA,0)) {
				LED_State = LED_wait2;
			}
			break;
		case LED_led1_on:
			if (getBit(PINA,0)) {
				LED_State = LED_led1_on;
			}
			else if (!getBit(PINA,0)) {
				LED_State = LED_wait1;
			}
			break;
		default:
			LED_State = LED_init;
	} // Transitions

	switch(LED_State) { // State actions
		case LED_init:
			tempB = setBit(tempB,0,1);
			tempB = setBit(tempB,1,0);
			break;
		case LED_wait1:
			break;
		case LED_led2_on:
			tempB = setBit(tempB,0,0);
			tempB = setBit(tempB,1,1);
			break;
		case LED_wait2:
			break;
		case LED_led1_on:
			tempB = setBit(tempB,0,1);
			tempB = setBit(tempB,1,0);
			break;
		default:
			break;
	} // State actions

}

int main() {
	DDRA = 0x00;
	DDRB = 0xFF;
	PORTA = 0x00;
	PORTB = 0x00;
	LED_State = LED_init; // Initial state
	tempB = 0x01; // Initial outputs
	while(1) {
		TickFct_led_latch();
		PORTB = tempB;
	}
}
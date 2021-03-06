/*
 * bcarey_lab4_part3.c - 4/10/2016
 *
 * Author : Braddley Carey - bcare001@ucr.edu
 *			bcare001
 *
 * Partner:	Brad Evans - bevan006@ucr.edu
 *
 * Lab Section: 21 
 *
 * Assignment: Lab 4 - Exercise 3
 *
 * I acknowledge all content contained herein, excluding template
 * or example code, is my own original work unless otherwise
 * stated.
 */ 

#include <avr/io.h>

//Global Variables
unsigned char tempC = 0x00;
unsigned char tempB = 0x00;
enum LED_States { start, LED_init, LED_wait1, LED_wait2, 
				  LED_1, LED_2, LED_3, LED_4, LED_5, 
				  LED_6, LED_7, LED_8, LED_9, LED_10
				} LED_State;

//Functions
unsigned char setBit(unsigned char x, unsigned char k, unsigned char b) {
    return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char getBit(unsigned char x, unsigned char k) {
    return ((x & (0x01 << k)) != 0);
}	

void led() {
	switch(LED_State) {
		case start:
			LED_State = LED_init;
			break;
		case LED_init:
			LED_State = LED_1;
		case LED_wait1:
			if(~PINA & 0x01){
				LED_State = LED_wait1;
			}else{
				LED_State = LED_wait2;
			}
			break;
		case LED_wait2:
			if(!(~PINA & 0x01)){
				LED_State= LED_wait2;
			}else{
				switch(tempB){
					case 0:
						LED_State = LED_1; tempB++; break;
					case 1:
						LED_State = LED_2; tempB++; break;
					case 2:
						LED_State = LED_3; tempB++; break;
					case 3:
						LED_State = LED_4; tempB++; break;
					case 4:
						LED_State = LED_5; tempB++; break;
					case 5:
						LED_State = LED_6; tempB++; break;
					case 6:
						LED_State = LED_7; tempB++; break;
					case 7:
						LED_State = LED_8; tempB++; break;
					case 8:
						LED_State = LED_9; tempB++; break;
					case 9:
						LED_State = LED_10; tempB++; break;
					case 10:
						LED_State = LED_1; tempB = 0x01; break;
				}
			}
			break;
		//State transition for ALL LED_# states
		default:
			LED_State = LED_wait1;
			break;
	} // Transitions

	switch(LED_State) { // State actions
		case start:
			break;
		case LED_init:
			tempB = 0x00;
			tempC = 0x00;
			break;
		case LED_wait1: 
			break;
		case LED_wait2: 
			break;
		case LED_1:
			tempC = 0x24; break;
		case LED_2:
			tempC = 0x12; break;
		case LED_3:
			tempC = 0x09; break;
		case LED_4:
			tempC = 0x3F; break;
		case LED_5:
			tempC = 0x00; break;
		case LED_6:
			tempC = 0x3F; break;
		case LED_7:
			tempC = 0x00; break;
		case LED_8:
			tempC = 0x0C; break;
		case LED_9:
			tempC = 0x12; break;
		case LED_10:
			tempC = 0x21; break;
		default:
			break;
	} // State actions
	PORTB = tempB;
	PORTC = tempC;
	
}
int main() {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	LED_State = start; // Initial state
	while(1) {
		led();
	} 
}

/*
 * bcarey_lab3_part2.c - 3/30/2016
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

//Global Variables
unsigned char tempB;
unsigned char tempC;

//Functions
unsigned char setBit(unsigned char x, unsigned char k, unsigned char b) {
    return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char getBit(unsigned char x, unsigned char k) {
    return ((x & (0x01 << k)) != 0);
}	
enum LOCK_States { LOCK_init_0, LOCK_wait_1, LOCK_input1_2, LOCK_wait_3, LOCK_wait_4, LOCK_input2_5, LOCK_unlock_6 } LOCK_State;

void lock() {
	switch(LOCK_State) {
		case LOCK_init_0:
			LOCK_State = LOCK_wait_1;
			break;
		case LOCK_wait_1:
			if ((getBit(PINA,0)||getBit(PINA,1)||getBit(PINA,2)||getBit(PINA,7))) {
				LOCK_State = LOCK_input1_2;
			}
			else if (!(getBit(PINA,0)||getBit(PINA,1)||getBit(PINA,2)||getBit(PINA,7))) {
				LOCK_State = LOCK_wait_1;
			}
			break;
		case LOCK_input1_2:
			if (getBit(PINA,0)||getBit(PINA,1)||!getBit(PINA,2)||getBit(PINA,7)) {
				LOCK_State = LOCK_init_0;
			}
			else if (!(getBit(PINA,0)||getBit(PINA,1)||!getBit(PINA,2)||getBit(PINA,7))) {
				LOCK_State = LOCK_wait_3;
			}
			break;
		case LOCK_wait_3:
			if (getBit(PINA,0)||getBit(PINA,1)||getBit(PINA,2)||getBit(PINA,7)) {
				LOCK_State = LOCK_wait_3;
			}
			else if (!(getBit(PINA,0)||getBit(PINA,1)||getBit(PINA,2)||getBit(PINA,7))) {
				LOCK_State = LOCK_wait_4;
			}
		break;
		case LOCK_wait_4:
			if ((getBit(PINA,0)||getBit(PINA,1)||getBit(PINA,2)||getBit(PINA,7))) {
				LOCK_State = LOCK_input2_5;
			}
			else if (!(getBit(PINA,0)||getBit(PINA,1)||getBit(PINA,2)||getBit(PINA,7))) {
				LOCK_State = LOCK_wait_4;
			}
			break;
		case LOCK_input2_5:
			if (!(getBit(PINA,0)||!getBit(PINA,1)||getBit(PINA,2)||getBit(PINA,7))) {
				
				LOCK_State = LOCK_unlock_6;
			}
			else if ((getBit(PINA,0)||!getBit(PINA,1)||getBit(PINA,2)||getBit(PINA,7))) {
				LOCK_State = LOCK_init_0;
			}
			break;
		case LOCK_unlock_6:
			if (getBit(PINA,7)) {
				LOCK_State = LOCK_init_0;
			}
			else if (!getBit(PINA,7)) {
				LOCK_State = LOCK_unlock_6;
			}
			break;
		default:
			LOCK_State = LOCK_init_0;
	} // Transitions

	switch(LOCK_State) { // State actions
		case LOCK_init_0:
			tempB=setBit(tempB,0,0);
			tempC=setBit(tempC,2,0);
			tempC=setBit(tempC,3,0);
			tempC=setBit(tempC,4,0);
			break;
		case LOCK_wait_1:
			tempC=setBit(tempC,0,1);
			tempC=setBit(tempC,1,0);
			tempC=setBit(tempC,2,0);
			break;
		case LOCK_input1_2:
			tempC=setBit(tempC,0,0);
			tempC=setBit(tempC,1,1);
			tempC=setBit(tempC,2,0);
			break;
		case LOCK_wait_3:
			tempC=setBit(tempC,0,1);
			tempC=setBit(tempC,1,1);
			tempC=setBit(tempC,2,0);
			break;
		case LOCK_wait_4:
			tempC=setBit(tempC,0,0);
			tempC=setBit(tempC,1,0);
			tempC=setBit(tempC,2,1);
			break;
		case LOCK_input2_5:
			tempC=setBit(tempC,0,1);
			tempC=setBit(tempC,1,0);
			tempC=setBit(tempC,2,1);
			break;
		case LOCK_unlock_6:
			tempB=setBit(tempB,0,1);
			tempC=setBit(tempC,0,0);
			tempC=setBit(tempC,1,1);
			tempC=setBit(tempC,2,1);
			break;
		
		default: // ADD default behaviour below
		break;
	} // State actions

}
int main() {
	DDRA = 0x00;
	DDRB = 0xFF;
	DDRC = 0xFF;
	PORTA = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
	LOCK_State = -1; // Initial state
	tempB = 0x00; // Init outputs

	while(1) {
		lock();
		PORTB = tempB;
		PORTC = tempC;
	} 
}


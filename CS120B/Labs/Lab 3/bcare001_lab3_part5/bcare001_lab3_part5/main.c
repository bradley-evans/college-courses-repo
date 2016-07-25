/*
 * bcarey_lab3_part5.c - 3/30/2016
 *
 * Author : Braddley Carey - bcare001@ucr.edu
 *			bcare001
 *
 * Partner:	Brad Evans - bevan006@ucr.edu
 *
 * Lab Section: 21 
 *
 * Assignment: Lab 3 - Exercise 5
 *
 * I acknowledge all content contained herein, excluding template
 * or example code, is my own original work unless otherwise
 * stated.
 */ 

#include <avr/io.h>

//Global Variables
unsigned char tempB;
unsigned char tempC;
unsigned char passcode[4] = {0x04, 0x01, 0x02, 0x01};
enum LOCK_States { start, LOCK_init, LOCK_waitCode, LOCK_valiCode, LOCK_release, LOCK_toggle, LOCK_inside } LOCK_State;

//Functions
unsigned char setBit(unsigned char x, unsigned char k, unsigned char b) {
    return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char getBit(unsigned char x, unsigned char k) {
    return ((x & (0x01 << k)) != 0);
}	

void lock() {
	switch(LOCK_State) {
		case start:
			tempB = 0x00;
			LOCK_State = LOCK_init;
			break;
		case LOCK_init:
			LOCK_State = LOCK_waitCode;
			break;
		case LOCK_waitCode:
			LOCK_State = (getBit(PINA,0)||getBit(PINA,1)||getBit(PINA,2)) ? LOCK_valiCode : LOCK_waitCode;
			break;
		case LOCK_valiCode:
			if(PINA==passcode[PINC]){
				LOCK_State = LOCK_release;
				tempC++;
			}else{
				LOCK_State = LOCK_init;
			}	
			break;
		case LOCK_release:
			LOCK_State = (getBit(PINA,0)||getBit(PINA,1)||getBit(PINA,2)) ? LOCK_release : LOCK_toggle;
			break;
		case LOCK_toggle:
			if(PINC <  0x04 && (!(getBit(PINA,0)||getBit(PINA,1)||getBit(PINA,2)))){
				LOCK_State = LOCK_waitCode;
			}
			if(PINC >= 0x04 && (!(getBit(PINA,0)||getBit(PINA,1)||getBit(PINA,2)))){
				if(getBit(PINB,0)){
					tempB = setBit(tempB,0,0);
				}else{
					tempB = setBit(tempB,0,1);
				}
				LOCK_State = LOCK_init;
			}
			if(getBit(PINA,0)||getBit(PINA,1)||getBit(PINA,2)){
				LOCK_State = LOCK_toggle;
			}			
			break;
		case LOCK_inside:
			LOCK_State = LOCK_init;
			break;
		default:
			break;
	}
	switch(LOCK_State) {
		case start:
			break;
		case LOCK_init:
			tempC = 0x00;
			break;
		case LOCK_waitCode:
			break;
		case LOCK_valiCode:
			break;
		case LOCK_release:
			break;
		case LOCK_toggle:
			break;
		case LOCK_inside:
			tempB=1;
			LOCK_State = LOCK_init;
		default:
			break;
	} //State Actions

}
int main() {
	DDRA = 0x00;
	DDRB = 0xFF;
	DDRC = 0xFF;
	PORTA = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
	LOCK_State = start; // Initial state
	while(1) {
		lock();
		PORTB = tempB;
		PORTC = tempC;
	} 
}

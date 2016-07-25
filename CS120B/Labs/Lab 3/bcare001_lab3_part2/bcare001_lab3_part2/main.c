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
enum {CNT_init, CNT_inc, CNT_dec, CNT_rst, CNT_wait} CNT_State;
unsigned char tempC;

//Functions
unsigned char setBit(unsigned char x, unsigned char k, unsigned char b) {
    return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}

unsigned char getBit(unsigned char x, unsigned char k) {
    return ((x & (0x01 << k)) != 0);
}	
void counter(){
	switch(CNT_State){
		case CNT_init:
			CNT_State = CNT_wait;
			break;
		case CNT_rst:
			CNT_State = CNT_wait;
			break;
		case CNT_inc:
			CNT_State = CNT_wait;
			break;
		case CNT_dec:
			CNT_State = CNT_wait;
			break;
		case CNT_wait:
			if(getBit(PINA,0)&&getBit(PINA,1)){
				CNT_State = CNT_rst;
			}
			if(getBit(PINA,0)&&!getBit(PINA,1)){
				CNT_State = CNT_inc;
			}
			if(!getBit(PINA,0)&&getBit(PINA,1)){
				CNT_State = CNT_dec;
			}
			break;
	}
	switch(CNT_State){
		case CNT_wait:
			break;
		case CNT_rst:
			tempC = 0x00;
			break;
		case CNT_inc:
			if(tempC<9){
				tempC++;
			}
			break;
		case CNT_dec:
			if(tempC>0){
				tempC--;
			}
			break;
		default:
			break;
	}
}

int main(void)
{
	//Initialize
	DDRA = 0x00; //Configure port A as inputs
	DDRC = 0xFF; //Configure port C as outputs
	PORTA = 0xFF;
	PORTC = 0x00;
	CNT_State = CNT_init;
	tempC = 0x00; 

	//Loop
	while (1){
		counter();
		PORTC = tempC;
    }
}


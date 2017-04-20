/*
 * bcarey_lab4_part2.c - 4/12/2016
 *
 * Author : Braddley Carey - bcare001@ucr.edu
 *			bcare001
 *
 * Partner:	Brad Evans - bevan006@ucr.edu
 *
 * Lab Section: 21 
 *
 * Assignment: Lab 4 - Exercise 2
 *
 * I acknowledge all content contained herein, excluding template
 * or example code, is my own original work unless otherwise
 * stated.
 */ 

#include <avr/io.h>


//Variable Declarations
enum CNT_States{start, init, A0_press, A1_press} CNT_State;
unsigned tempC;

//Function Definitions
unsigned char setBit(unsigned char x, unsigned char k, unsigned char b){
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char getBit(unsigned char x, unsigned char k){
	return ((x & (0x01 << k)) != 0);
}
void counter(){
	unsigned char a = ~PINA;
	switch(CNT_State){
		case start:
			tempC = 0x00;
			CNT_State = init;
			break;
		case init:
			if(getBit(a,0)==getBit(a,1)){
				CNT_State = init;
			}else if(getBit(a,0) && !getBit(a,1)){
				CNT_State = A0_press;
				if(tempC < 9){
					tempC++;
				}
			}else if(!getBit(a,0) && getBit(a,1)){
				CNT_State = A1_press;
				if(tempC > 0){
					tempC--;
				}
			}
			break;
		case A0_press:
			if(getBit(a,0) && !getBit(a,1)){
				CNT_State = A0_press;
			}else if(getBit(a,0) && getBit(a,1)){
				tempC = 0x00;
				CNT_State = init;
			}else{
				CNT_State = init;
			}
			break;
		case A1_press:
			if(!getBit(a,0) && getBit(a,1)){
				CNT_State = A1_press;
			}else if(getBit(a,0) && getBit(a,1)){
				tempC = 0x00;
				CNT_State = init;
			}else{
				CNT_State = init;
			}
			break;
	}
	switch(CNT_State){
		default:
			break;
	}
	PORTC = tempC;
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; 
	DDRC = 0xFF; PORTC = 0x00; 
	CNT_State = start;
		
    while (1){
		counter();
	}
}
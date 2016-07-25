/*
 * bcarey_lab5_part3.c - 4/13/2016
 *
 * Author : Braddley Carey - bcare001@ucr.edu
 *			bcare001
 *
 * Partner:	Brad Evans - bevan006@ucr.edu
 *
 * Lab Section: 21 
 *
 * Assignment: Lab 5 - Exercise 3
 *
 * I acknowledge all content contained herein, excluding template
 * or example code, is my own original work unless otherwise
 * stated.
 */ 

#include <avr/interrupt.h>
#include "io.c"
#include "timer.h"

//Variable Declarations
enum CNT_States{start, init} CNT_State;
unsigned char tempB, tempC;
void counter(){
	unsigned char a0 = (~PINA & 0x01);
	unsigned char a1 = (~PINA & 0x02);
	
	switch(CNT_State){
		case start:
			tempC = 0x00;
			CNT_State = init;
			break;
		case init:
			if( a0 && a1 ){
				tempC = 0;
			}else if( a0 && !a1 ){
				if( tempC < 9 ){
					tempC++;
				}
			}else if( !a0 && a1 ){
				if(tempC > 0){
					tempC--;
				}
			}
			CNT_State = init;
			break;
	}
	switch(CNT_State){
		default:
			break;
	}
	//Update registers
	LCD_Cursor(1);
	LCD_WriteData(tempC+'0');
	if(PINB==0x00||PINB==0x02){
		tempB = 0x01;
	}else{
		tempB = 0x02;
	}
	PORTB = tempB;
}

int main(){
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	TimerSet(1000);
	TimerOn();
	LCD_init();
	while(1) {
		while (!TimerFlag);
		TimerFlag = 0;
		counter();
	}
}


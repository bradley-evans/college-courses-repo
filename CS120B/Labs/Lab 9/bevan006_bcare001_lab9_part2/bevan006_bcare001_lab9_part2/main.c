/*
 * bevan006_bcare001_lab9_part1.c - 5/4/2016
 *
 * Author : Braddley Carey - bcare001@ucr.edu
 *			bcare001
 *
 * Partner:	Brad Evans - bevan006@ucr.edu
 *
 * Lab Section: 21 
 *
 * Assignment: Lab 9 - Exercise 1
 *
 * I acknowledge all content contained herein, excluding template
 * or example code, is my own original work unless otherwise
 * stated.
 */ 

#include <avr/interrupt.h>

//Timer functions
volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
void TimerISR() {
	TimerFlag = 1;
}
void TimerOn() {
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1=0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}
void TimerOff() {
	TCCR1B = 0x00;
}
ISR(TIMER1_COMPA_vect) {
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0) {
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}



//My Code
static unsigned char threeLEDs=0;
static unsigned char blinkingLED=0;
static unsigned char count1=0, count2=0;

enum states1{start1, s1, s2, s3} state1;
enum states2{start2, blink} state2;
enum states3{start3, write} state3;
	
void tick(){
	// Transition statements
	switch(state1){
		case start1:
			threeLEDs = 0;
			state1 = s1;
			break;
		case s1:
			if (count1 < 3) {
				count1++;
				state1 = s1;
			} else {
				count1 = 0;
				state1 = s2;
			}
			break;
		case s2:
			if (count1 < 3) {
				count1++;
				state1 = s2;
			} else {
				count1 = 0;
				state1 = s3;
			}
			break;
		case s3:
			if (count1 < 3) {
				count1++;
				state1 = s3;
			} else {
				count1 = 0;
				state1 = s1;
			}
			break;
		default:
			state1 = start1; break;
	}
	switch(state2){
		case start2:
			blinkingLED=0x08;
			state2 = blink;
			break;
		case blink:
			if (count2 < 10 ) {
				count2++;
				state2 = blink;
			} else {
				count2 = 0;
				blinkingLED = ~blinkingLED;
				state2 = blink;
			}
			break;
		default:
			state2 = start2; break;
	}
	switch(state3){
		case start3:
			PORTB = 0xFF;
			state3 = write;
			break;
		case write:
			state3 = write;
			break;
		default:
			state3 = start3; 
			break;
	}
	// State actions
		// Transition statements
	switch(state1){
		case start1:
			break;
		case s1:
			threeLEDs=0x01;
			break;
		case s2:
			threeLEDs=0x02;
			break;
		case s3:
			threeLEDs=0x04;
			break;
		default:
			break;
	}	
	switch(state2){
		case start2:
			break;
		case blink:
			break;
		default:
			break;
	}
	switch(state3){
		case start3:
			break;
		case write:
			PORTB = ~(( threeLEDs & 0x07) | (blinkingLED & 0x08));
			break;
		default:
			break;
	}
}
int main(){
	//Initialize Registers
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	
	//Set Timers
	TimerSet(100);
	TimerOn();
	
	
	
	//Variables
	state1 = start1;
	state2 = start2;
	state3 = start3;
	PINB = 0;
	while(1) {
		while (!TimerFlag);
		TimerFlag = 0;
		tick();
	}
	
}

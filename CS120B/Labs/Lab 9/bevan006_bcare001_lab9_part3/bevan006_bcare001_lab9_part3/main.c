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
 * Assignment: Lab 9 - Exercise 3
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
unsigned char num=0;
unsigned char pulseA=0, pulseB=0, countA=0, countB=0;

enum states1{start1, waitA, pulseA_sec, pulseA_fast} state1;
enum states2{start2, waitB, pulseB_sec, pulseB_fast} state2;
enum states3{start3, update_count} state3;
	
void tick_pulseA(){
	// Transition statements
	unsigned char a = (~PINA & 0x03);
	a = (~PINA & 0x03);
	switch(state1) {
		case start1:
			state1 = waitA;
			break;
		case waitA:
			pulseA = 0;
			if (a == 0x01) {
				state1 = pulseA_sec;
				countA = 0;
			} else {
				state1 = waitA;
			}
			break;
		case pulseA_sec:
			if (a == 0x01) {
				if (countA < 15) {
					state1 = pulseA_sec;
					countA++;
				} else {
					state1 = pulseA_fast;
					countA = 0;
				}
			} else {
				state1 = waitA;
			}
			break;
		case pulseA_fast:
			if (a == 0x01) {
				countA++;
			} else {
				state1 = waitA;
			}
			break;
		default:
			state1 = start1;
			break;
	}
	switch(state1) {
		case start1:
			break;
		case waitA:
			pulseA = 0;
			break;
		case pulseA_sec:
			pulseA = 0;
			if ( (countA % 5) == 0 ) {
				pulseA = 1;
			}
			break;
		case pulseA_fast:
			pulseA = 0;
			if ( (countA % 2) == 0 ) {
				pulseA = 1;
			}
			break;
		default:
			break;
	}	
}

void tick_pulseB(){
	// Transition statements
	unsigned char a = (~PINA & 0x07);
	a = (~PINA & 0x07);
	switch(state2) {
		case start2:
			pulseB = 0;
			state2 = waitB;
			break;
		case waitB:
			pulseB = 0;
			if (a == 0x02) {
				state2 = pulseB_sec;
				countB = 0;
			} else {
				state2 = waitB;
			}
			break;
		case pulseB_sec:
			if (a == 0x02) {
				if (countB < 15) {
					state2 = pulseB_sec;
					countB++;
				} else {
					state2 = pulseB_fast;
					countB = 0;
				}
			} else {
				state2 = waitB;
			}
			break;
		case pulseB_fast:
			if (a == 0x02) {
				countB++;
			} else {
				state2 = waitB;
			}
			break;
		default:
			state2 = start2;
			break;
	}
	switch(state2) {
		case start2:
			break;
		case waitB:
			pulseB = 0;
			if (a == 0x02) {
				state2 = pulseB_sec;
				countB = 0;
			} else {
				state2 = waitB;
			}
			break;
		case pulseB_sec:
			pulseB = 0;
			if ( (countB % 5) == 0 ) {
				pulseB = 1;
			}
			break;
		case pulseB_fast:
			pulseB = 0;
			if ( (countB % 2) == 0 ) {
				pulseB = 1;
			}
			break;
		default:
			break;
	}
}

void tick_counter() {
	unsigned char a = (~PINA & 0x07);
	switch (state3) {
		case start3:
			num = 0x00;
			state3 = update_count;
			break;
		case update_count:
			if (pulseA == 1 && pulseB == 1) {
				num = 0; 
			} else if (pulseA == 1 && pulseB == 0 && num < 9) {
				num++; 
			} else if (pulseA == 0 && pulseB == 1 && num > 0) {
				num--; 
			}
			
	}
	if (a == 0x03) {
		num = 0x00;
	}
	PORTB = num;
}

int main(){
	//Initialize Registers
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	
	//Set Timers
	TimerSet(200);
	TimerOn();
	
	//Variables
	state1 = start1;
	state2 = start2;
	state3 = start3;
	while(1) {
		while (!TimerFlag);
		TimerFlag = 0;
		tick_pulseA();
		tick_pulseB();
		tick_counter();
	}
	
}

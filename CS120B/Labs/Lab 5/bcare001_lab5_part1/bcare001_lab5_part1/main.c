/*
 * bcarey_lab5_part1.c - 4/12/2016
 *
 * Author : Braddley Carey - bcare001@ucr.edu
 *			bcare001
 *
 * Partner:	Brad Evans - bevan006@ucr.edu
 *
 * Lab Section: 21 
 *
 * Assignment: Lab 5 - Exercise 1
 *
 * I acknowledge all content contained herein, excluding template
 * or example code, is my own original work unless otherwise
 * stated.
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0; 
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
void TimerISR() {
	TimerFlag = 1;
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

unsigned char tempB = 0x00;
void led(){
	if(tempB == 0x00){
		tempB = 0x01;
	}
	else if(tempB == 0x01){
		tempB = 0x02;
	}
	else if(tempB == 0x02){
		tempB = 0x04;
	}
	else if(tempB == 0x04){
		tempB = 0x01;
	}
	PORTB = tempB;	
}

int main(){
	DDRB = 0xFF; PORTB = 0x00;
	TimerSet(1000);
	TimerOn();
	tempB = 0x00;
	while(1) {
		while (!TimerFlag);
			TimerFlag = 0;
		led();
	}
}

/*
 * bcarey_lab6_part1.c - 4/20/2016
 *
 * Author : Braddley Carey - bcare001@ucr.edu
 *			bcare001
 *
 * Partner:	Brad Evans - bevan006@ucr.edu
 *
 * Lab Section: 21 
 *
 * Assignment: Lab 6 - Exercise 1
 *
 * I acknowledge all content contained herein, excluding template
 * or example code, is my own original work unless otherwise
 * stated.
 */ 

#include <avr/interrupt.h>
#include <avr/io.h>
#include "io.c"

//Timer Variables
volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

//Timer Functions
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

//Global Variables
unsigned char period;
unsigned char count;
unsigned char sound;
unsigned char input;

//Global Constants
const unsigned char p_max = 50;
const unsigned char p_min = 1;

//State Machine
enum States{start, init, freq} state;
void make_sound(){
	sound = (sound && 0x10) ? 0x00 : 0x10;	
}
void tick(){
	input = (~PINA & 0x03);
	switch(state){
		case start:
			count = 0; period = 1; state = init; break;
		case init:
			if(input==0x02 && period < p_max){
				period++;
				state = freq;	
			}
			else if(input==0x01 && period > p_min){
				period--;
				state = freq;
			}
			else{
				state = init;
			}
			break;
		case freq:
			state = (input) ? freq : init;
			break;
		default:
			break;
	}
	switch(state){
		case start:
			break;
		case init:
			if(count++ > period){
				count = 0;
				make_sound();
			}
			break;
		case freq:
			break;
		default:
			break;
	}
	sound = (sound | input);
	PORTB = sound;
}

int main(){
	//Initialize Registers
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	
	//Set Timers
	TimerSet(1);
	TimerOn();
	state = start;
	while(1) {
		while (!TimerFlag);
		TimerFlag = 0;
		tick();
	}
}

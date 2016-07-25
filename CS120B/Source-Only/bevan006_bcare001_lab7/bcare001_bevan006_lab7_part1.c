/*
 * bcarey_lab7_part1.c - 4/20/2016
 *
 * Author : Braddley Carey - bcare001@ucr.edu
 *			bcare001
 *
 * Partner:	Brad Evans - bevan006@ucr.edu
 *
 * Lab Section: 21 
 *
 * Assignment: Lab 7 - Exercise 1
 *
 * I acknowledge all content contained herein, excluding template
 * or example code, is my own original work unless otherwise
 * stated.
 */ 

#include <avr/interrupt.h>
#include <string.h>
#include "io.c"

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

//PWM Code
void set_PWM(double frequency) {
	static double current_frequency;
	if (frequency != current_frequency) {
		if (!frequency) { TCCR3B &= 0x08; }
		else { TCCR3B |= 0x03; }
		
		if (frequency < 0.954) { OCR3A = 0xFFFF; }
		else if (frequency > 31250) { OCR3A = 0x0000; }
		else { OCR3A = (short)(8000000 / (128 * frequency)) - 1; }
		
		TCNT3 = 0;
		current_frequency = frequency;
	}
}
void PWM_on() {
	TCCR3A = (1 << COM3A0);
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	set_PWM(0);
}
void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}


//My Code
const double tone_c4 = 261.63;
const double tone_d4 = 293.66;
const double tone_e4 = 329.63;
enum states{start, init, c4, d4, e4} state;
void tick(){
	unsigned char input = (~PINA && 0x07);
	switch(state){
		case start:
			state = init; break;
		case init:
			if(input==0x01){
				state = c4;
			}
			else if(input==0x02){
				state = d4;
			}
			else if(input==0x04){
				state = e4;
			}
			else{
				state = init;
			}
			break;
		case c4:
			state = (input != 0x01) ? init : c4;
			break;
		case d4:
			state = (input != 0x02) ? init : d4;
			break;
		case e4:
			state = (input != 0x04) ? init : e4;
			break;
		default:
			state = start; break;
	}
	switch(state){
		case start:
			set_PWM(0); break;
		case init:
			set_PWM(0); break;
		case c4:
			set_PWM(tone_c4); break;
		case d4:
			set_PWM(tone_d4); break;
		case e4:
			set_PWM(tone_e4); break;
		default:
			break;
	}
}
int main(){
	//Initialize Registers
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	
	//Set Timers
	TimerSet(10);
	TimerOn();
	PWM_on();
	
	//Variables
	state = start;
	
	while(1) {
		while (!TimerFlag);
		TimerFlag = 0;
		tick();
	}
}

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
const double note[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};
unsigned char i = 0;

enum States{start,wait,up_hold,up,down_hold,down} state;
void Tick() {
	
	
	unsigned char a = (~PINA & 0x07);
	switch(state) { // Transitions
		case start:
			set_PWM(0);
			state = wait;
			break;
		case wait:	
			if (a==0x02) {
				state = up_hold; 
			} else if (a==0x04) {
				state = down_hold;
			} else {
				state = wait;
			}
			break;
		case up_hold:
			if (a==0x00) {
				i = 0;
				state = up;
			} else {
				state = up_hold;
			}
			break;
		case down_hold:
			if (a==0x00) {
				i = 7;
				state = down;
			} else {
				state = down_hold;
			}
			break;
		case up:
			if (a==0x01) {
				state = wait;
			} else if (a==0x04) {
				state = down_hold;
			} else {
				if (i==8) {
					i=0;
					state = wait;
				} else {
					state = up;
					i++;
				}
			}
			break;
		case down:
			if (a==0x01) {
				state = wait;
			} else if (a==0x02) {
				state = up_hold;
			} else {
				if (i==0) {
					state = wait;
				} else {
					i--;					
					state = down;
				}
			}
			break;
		default:
			state = start;
			break;
	}
	switch(state) { // State actions
		
		case start:
			break;
		case wait:
			set_PWM(0);
			i = 0;
			break;
		case up_hold:
			break;
		case down_hold:
			break;
		case up:
			set_PWM(note[i]);
			break;
		case down:
			set_PWM(note[i]);
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
	TimerSet(500);
	TimerOn();
	PWM_on();
	
	//Variables
	state = start;
	
	while(1) {
		while (!TimerFlag);
		TimerFlag = 0;
		Tick();
	}
}

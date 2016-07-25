/*
 * bevan006_bcare001_lab10_part1.c - 5/4/2016
 *
 * Author : Braddley Carey - bcare001@ucr.edu
 *			bcare001
 *
 * Partner:	Brad Evans - bevan006@ucr.edu
 *
 * Lab Section: 21 
 *
 * Assignment: Lab 10 - Exercise 1
 *
 * I acknowledge all content contained herein, excluding template
 * or example code, is my own original work unless otherwise
 * stated.
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "keypad.h"
#include "bit.h"

//Globals
const unsigned char tasksNum = 1;
const unsigned char tasksPeriodGCD = 100;
typedef struct task {
	int state; // Current state of the task
	unsigned long period; // Rate at which the task should tick
	unsigned long elapsedTime; // Time since task's previous tick
	int (*TickFct)(int); // Function to call for task's tick
} task;
task tasks[1];


//Timer Functions
volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
void TimerISR() {
	unsigned char i;
	for (i = 0; i < tasksNum; ++i) { // Heart of the scheduler code
		if ( tasks[i].elapsedTime >= tasks[i].period ) { // Ready
			tasks[i].state = tasks[i].TickFct(tasks[i].state);
			tasks[i].elapsedTime = 0;
		}
		tasks[i].elapsedTime += tasksPeriodGCD;
	}
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

const int keypad_period=100;
enum Keypad_States{keypad_start, keypad_poll} Keypad_State;
int tickFct_Keypad(int state){
	unsigned char input = GetKeypadKey();
	switch(state){
		case keypad_start:
			state = keypad_poll;
			break;
		case keypad_poll:
			break;
		default:
			break;
	}	
	switch(state){
		case keypad_start:
			break;
		case keypad_poll:
			switch(input){
				case '\0':
					PORTB=0x1F; break;
				case '1':
					PORTB=0x01; break;
				case '2':
					PORTB=0x02; break;
				case '3':
					PORTB=0x03; break;
				case '4':
					PORTB=0x04; break;
				case '5':
					PORTB=0x05; break;
				case '6':
					PORTB=0x06; break;
				case '7':
					PORTB=0x07; break;
				case '8':
					PORTB=0x08; break;
				case '9':
					PORTB=0x09; break;
				case '0':
					PORTB=0x00; break;
				case 'A':
					PORTB=0x0A; break;
				case 'B':
					PORTB=0x0B; break;
				case 'C':
					PORTB=0x0C; break;
				case 'D':
					PORTB=0x0D; break;
				case '*':
					PORTB=0x0E; break;
				case '#':
					PORTB=0x0F; break;
			}
			break;
		default:
			break;
	}
	return state;
}

int main(void){
	unsigned char i=0;
	//Keypad Task
	tasks[i].state = keypad_start;
	tasks[i].period = keypad_period;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct(&tickFct_Keypad);
	
	TimerSet(100);
	TimerOn();
    while (1){
		
    }
}


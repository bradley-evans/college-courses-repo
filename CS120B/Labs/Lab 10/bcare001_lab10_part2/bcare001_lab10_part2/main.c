/*
 * bcarey_lab10_part2.c - 5/15/2016
 *
 * Author : Braddley Carey - bcare001@ucr.edu
 *			bcare001
 *
 * Partner:	Brad Evans - bevan006@ucr.edu
 *
 * Lab Section: 21 
 *
 * Assignment: Lab 10 - Exercise 2
 *
 * I acknowledge all content contained herein, excluding template
 * or example code, is my own original work unless otherwise
 * stated.
 */ 

#include <avr/interrupt.h>
#include <string.h>
#include "io.c"

//Constants
#define BUFFER 53
#define LCD_SIZE 16

//Globals
unsigned char message[BUFFER] = "                CS120B is Legend... wait for it DARY!";

//Timer Functions
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

enum states{start, iterate} state;
void shift(){
	for(int i=0; i<BUFFER-1; i++){
		message[i] = message[i+1];
	}
	message[BUFFER-1] = message[0];
	for(int i=0; i<LCD_SIZE-1;i++){
		LCD_Cursor(i);
		LCD_WriteData(message[i]);
	}
	
}
void led(){
	switch(state){
		case start:
			state = iterate; break;
		case iterate:
			state = iterate;
			break;
	}
	switch(state){
		case start:
			break;
		case iterate:
			shift();
			break;
	}
}

int main(){
	//Initialize Registers
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0xFF; PORTA = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
<<<<<<< HEAD
	DDRA = 0xFF; PORTA = 0xFF;
=======
	DDRC = 0x00; PORTC = 0xFF;
>>>>>>> refs/remotes/origin/master
	
	//Set Timers
	TimerSet(25);
	TimerOn();
	LCD_init();
	
	while(1) {
		while (!TimerFlag);
		TimerFlag = 0;
		//led();
		LCD_DisplayString(1,"test");
	}
}

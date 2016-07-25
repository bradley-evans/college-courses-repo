/*
 * bcarey_lab5_part3.c - 4/14/2016
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

enum LED_States {init, start, blink, pause, reset} led_state;
unsigned char tempB;
unsigned char counter;

void led(){
	unsigned char a = (~PINA & 0x01);
	switch(led_state){
		case init:
			counter = 0;
			led_state = start;
			break;
		case start:
			led_state = a ? start : blink;
			break;
		case blink:
			if(!a && counter > 20) {
				led_state = blink;
				if(tempB == 0x00){
					tempB = 0x01;				}else if(tempB == 0x01){
					tempB = 0x02;	            }else if(tempB == 0x02){					tempB = 0x04;	            }else if(tempB == 0x04){
					tempB = 0x01;
				}
				counter = 0;
				PORTB = tempB;
			}else if(!a && counter <= 20){
				counter++;
				led_state = blink;
			}else{
				led_state = pause;
			}
			break;
		case pause:
			led_state = a ? pause : reset;
			break;
		case reset:
			led_state = a ? start : reset;
			break;
		default:
			break;
	}
	switch(led_state){
		case init:
			break;
		case start:
			tempB = 0x00;
			break;
		case blink:
			break;
		case pause:
			break;
		case reset:
			break;
		default:
			break;
	}
}

int main(){
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	TimerSet(50);
	TimerOn();
	
	tempB = 0x00;
	led_state = init;
	while(1) {
		while (!TimerFlag);
			TimerFlag = 0;
		led();
	}
}

/*
 * bcarey_lab5_part4.c - 4/17/2016
 *
 * Author : Braddley Carey - bcare001@ucr.edu
 *			bcare001
 *
 * Partner:	Brad Evans - bevan006@ucr.edu
 *
 * Lab Section: 21 
 *
 * Assignment: Lab 5 - Exercise 4
 *
 * I acknowledge all content contained herein, excluding template
 * or example code, is my own original work unless otherwise
 * stated.
 */ 

#include <avr/interrupt.h>
#include <string.h>
#include "io.c"
#include "timer.h"

enum LED_States {start, init, blink, press, release, win, loss, score, unscore, reset} led_state;
unsigned char tempB;
unsigned char counter;
unsigned char curr_score;
unsigned char screen;
void nextLED(){
	if(tempB == 0x01)
		tempB = 0x02;
	else if(tempB == 0x02)
		tempB = 0x04;
	else
		tempB = 0x01;
	PORTB = tempB;
}
void led(){
	unsigned char a = (~PINA & 0x01);
	unsigned char r = (~PINA & 0x02);
	switch(led_state){
		case start:
			LCD_DisplayString(1, "Score: ");
			LCD_Cursor(8);
			LCD_WriteData('5');
			curr_score = 5;
			led_state = init;
			break;
		case init:
			led_state = r ? init : blink;
			break;
		case blink:
			counter++;
			if(r){
				curr_score = 5;
				led_state = init;
			}else{
				if(a){
					led_state = press;
				}else{
					if(counter>=20){
						nextLED();
						counter = 0;
					}
				}
			}
			break;
		case press:
			led_state = a ? press : release;
			break;
		case release:
			led_state = (tempB == 0x02) ? score : unscore;
			break;
		case score:
			curr_score++;
			LCD_Cursor(8);
			LCD_WriteData(curr_score+'0');
			led_state = (curr_score < 9) ? init : win;
			break;
		case unscore:
			curr_score--;
			LCD_Cursor(8);
			LCD_WriteData(curr_score+'0');
			led_state = (curr_score > 0) ? init : loss;
			break;
		case win:
			led_state = reset;
		case loss:
			led_state = reset;
		case reset:
			if(r){
				led_state = start;
			}
			break;
		default:
			break;
	}
	switch(led_state){
		case init:
			LCD_Cursor(8);
			LCD_WriteData(curr_score+'0');
			counter = 0;
			screen = 0;
			break;
		case win:
			LCD_DisplayString(1,"  WINNER!!");
			break;
		case loss:
			LCD_DisplayString(1,"  LOSER...");
			
			break;
		default:
			break;
	}
	PORTD = (PIND && 0x80) || led_state;
}

int main(){
	//Initialize Registers
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	
	//Set Timers
	TimerSet(50);
	TimerOn();
	LCD_init();
	tempB = 0x00;
	led_state = start;
	while(1) {
		while (!TimerFlag);
		TimerFlag = 0;
		led();
	}
}

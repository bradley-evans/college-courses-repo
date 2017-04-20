
#include <avr/interrupt.h>
#include <string.h>
#include "io.c"
#include "bit.h"
#include "keypad.h"

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

enum states{start, display} state;
void Tick() {
	unsigned char key;
	static unsigned char cursor = 0;
	// transitions'
	switch(state) {
		case start:
			LCD_Cursor(0);
			state = display; break;
		case display:
			state = display; break;
		default:
			state = start;
	}
	// state actions
	switch(state) {
		case start:
		break;
		case display:
		key = GetKeypadKey();
		if(key!='\0'){
			cursor = (cursor==16 ? 0 : cursor);
			LCD_Cursor(++cursor);
			LCD_WriteData(key);
			LCD_Cursor(0);
		}
		break;
	}
}

int main(void) {
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0xFF; PORTA = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	DDRC = 0xF0; PORTC = 0x0F; // PC7..4 outputs init 0s, PC3..0 inputs init 1s
	
	TimerSet(200);
	TimerOn();
	LCD_init();
	LCD_DisplayString(1,"Congratulations!");
	state = start;
	while(1) {
		while (!TimerFlag);
		TimerFlag = 0;
		Tick();
	}
}
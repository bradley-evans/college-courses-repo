#include <avr/io.h>
#include "io.c"
int main(void)
{
	DDRA = 0xFF; PORTA = 0x00; // LCD data lines
	DDRD = 0xFF; PORTD = 0x00; // LCD control lines
	// Initializes the LCD display
	LCD_init();
	// Starting at position 1 on the LCD screen, writes Hello World
	LCD_DisplayString(1, " ");
	while(1) {continue;}
}
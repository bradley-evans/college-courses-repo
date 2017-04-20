/*
 * bcare001_lab4_lab_chip.c
 *
 * Created: 4/8/2016 2:16:01 PM
 * Author : rente
 */ 

#include <avr/io.h>


int main(void)
{
    DDRB = 0xFF; PORTB = 0x00;
    while (1) 
    {
		PORTB = 0xF0;
    }
}


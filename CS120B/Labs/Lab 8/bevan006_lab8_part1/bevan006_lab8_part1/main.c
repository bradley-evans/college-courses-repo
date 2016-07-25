/*
 * bevan006_lab8_part1.c
 *
 * Created: 5/2/2016 2:30:24 PM
 * Author : bevans
 */ 

#include <avr/io.h>

//enum States{start} state;
//unsigned short adc_result;

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	// in Free Running Mode, a new conversion will trigger whenever
	// the previous conversion completes.
}

void tick() {
	
}

int main(void)
{
	ADC_init();
    /* Replace with your application code */
    while (1) 
    {
		
    }
}


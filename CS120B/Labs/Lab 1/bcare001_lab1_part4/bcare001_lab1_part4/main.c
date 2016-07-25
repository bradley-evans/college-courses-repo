/*
 * bcarey_lab1_part4.c - 3/30/2016
 *
 * Author : Braddley Carey - bcare001@ucr.edu
 *			bcare001
 *
 * Partner:	Brad Evans - bevan006@ucr.edu
 *
 * Lab Section: 21 
 *
 * Assignment: Lab 1 - Exercise 3
 *
 * I acknowledge all content contained herein, excluding template
 * or example code, is my own original work unless otherwise
 * stated.
 */ 

/* 
 * #################################
 * ###   PORTS USED   ##############
 * #################################
 *    INPUTS
 * #################################
 * PA7-PA0 : Weight of Rider r1
 * PB7-PB0 : Weight of Rider r2
 * PC7-PC0 : Weight of Rider r3
 * #################################
 *    OUTPUTS
 * #################################
 * PD0     : LED (too much weight)
 * PD1     : LED (unbalanced...weight between r1 and r3 too large)
 * PD4-PD2 : Shift amount to give weight estimate
 * PD7-PD3 : Weight estimate
 */

#include <avr/io.h>

int main(void)
{
	//Configure Ports
	DDRA = 0x00;
	DDRB = 0x00;
	DDRC = 0x00;
	DDRD = 0xFF;
	//Initialize outputs to 0
	PORTA = 0x00; 
	PORTB = 0x00;
	PORTC = 0x00;
	//Initialize inputs to 0
	PORTD = 0x00; 
	//Variables
	unsigned int total_weight;
	unsigned char shift;
	unsigned char tempD;
	
    while (1){
		shift = 0;
		tempD = 0x00;
	//Total weight
		total_weight = PINA + PINB + PINC;
		//if total weight is greater than 140kg set PD0==1
		if(total_weight > 140){
			tempD = (tempD & 0xFE) | 0x01;
		}else{
			tempD = (tempD & 0xFE);
		}
	//Unbalanced
		//if difference in weight between r1 and r3 > 80 set PD1==1
		if((PINA-PINC)>80 || (PINC-PINA)>80){
			tempD = (tempD & 0xFD) | (0x01<<1);	
		}else{
			tempD = (tempD & 0xFD);			
		}
	//Estimate weight
		while(total_weight>0x07){
			total_weight = total_weight>>1;
			shift++;	
		}
		//set shift
		tempD = (tempD & 0xE3) | (shift<<2);
		//set weight estimate
		tempD = (tempD & 0x1F) | (total_weight<<5);
	//Set PD7-PD0
		PORTD = tempD;
    }
}





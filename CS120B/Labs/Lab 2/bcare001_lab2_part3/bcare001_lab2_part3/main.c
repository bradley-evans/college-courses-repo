/*
 * bcarey_lab2_part2.c - 3/30/2016
 *
 * Author : Braddley Carey - bcare001@ucr.edu
 *			bcare001
 *
 * Partner:	Brad Evans - bevan006@ucr.edu
 *
 * Lab Section: 21 
 *
 * Assignment: Lab 2 - Exercise 2
 *
 * I acknowledge all content contained herein, excluding template
 * or example code, is my own original work unless otherwise
 * stated.
 */ 

#include <avr/io.h>

//Function Definitions
unsigned char setBit(unsigned char x, unsigned char k, unsigned char b){
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char getBit(unsigned char x, unsigned char k){
	return ((x & (0x01 << k)) != 0);
}

int main(void)
{
	//Assign and initialize Ports
	DDRA = 0x00; //Configure port A as inputs
	DDRC = 0xFF; //Configure port C as output
	PORTA = 0x00; //Initialize inputs to 0
	PORTC = 0x00; //Initialize outputs to 0
	unsigned char tempC = 0x00;
	unsigned char tank = 0x00;
	
    while (1){
		//Get tank value
		tank = 0x0F & PINA;
		//Set PC6 - Low Fuel LED
		if(tank<=4){
			tempC=setBit(tempC,6,1);
		}else{
			tempC=setBit(tempC,6,0);
		}
		//Set PC5
		if(tank>=1){
			tempC=setBit(tempC,5,1);
		}else{
			tempC=setBit(tempC,5,0);
		}
		//Set PC4
		if(tank>=3){
			tempC=setBit(tempC,4,1);
		}else{
			tempC=setBit(tempC,4,0);
		}
		//Set PC3
		if(tank>=5){
			tempC=setBit(tempC,3,1);
		}else{
			tempC=setBit(tempC,3,0);
		}
		//Set PC2
		if(tank>=7){
			tempC=setBit(tempC,2,1);
		}else{
			tempC=setBit(tempC,2,0);
		}
		//Set PC1
		if(tank>=10){
			tempC=setBit(tempC,1,1);
		}else{
			tempC=setBit(tempC,1,0);
		}
		//Set PC0
		if(tank>=13){
			tempC=setBit(tempC,0,1);
		}else{
			tempC=setBit(tempC,0,0);
		}
		// IF USER IS UNBUCKLED + IN DRIVER SEAT + KEY IN IGNITION,
		// ILLUMINATE SEATBELT LIGHT.
		if (getBit(PINA,4) && getBit(PINA,5) && !getBit(PINA,6)) {
			tempC = setBit(tempC,7,1);
		} else {
			tempC = setBit(tempC,7,0);
		}
		//Output to register C
		PORTC = tempC;
	}
}











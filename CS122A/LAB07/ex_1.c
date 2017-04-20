#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/portpins.h>
#include <avr/pgmspace.h>

//FreeRTOS include files
#include "FreeRTOS.h"
#include "task.h"
#include "croutine.h"

// Lab Specific

    // None specified for this lab.

// Definitions

// SetBit and ClrBit
#define SET_BIT(p,i) ((p) |= (1 << (i)))
#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
#define GET_BIT(p,i) ((p) & (1 << (i)))

/* GLOBAL VARIABLES */
unsigned char output;


/* GLOBAL FUNCTIONS */
void A2D_init() {
    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
    // ADEN: Enables ADC conversion.
    // ADSC: Starts A2D conversion.
    // ADATE: Enables autotriggering, allos for constant A2D conversion.
}
unsigned short input;

/* SET LCD STATE MACHINE */
enum getinput_State {getinput_INIT,getinput_RUN} getinput_state;

void getinput_init(){
    getinput_state = getinput_INIT;
    output = 0;
}

void getinput_Tick(){
    //Actions
    switch(getinput_state){
        case getinput_INIT:
            break;
        case getinput_RUN:
            input = ADC;
            break;
        default:
            break;
    }
    //Transitions
    switch(getinput_state){
        case getinput_INIT:
            getinput_state = getinput_RUN;
            break;
        case getinput_RUN:
            getinput_state = getinput_RUN;
            break;
        default:
            getinput_state = getinput_INIT;
            break;
    }
}
void getinput_Task()
{
    getinput_init();
    while (1) {
        getinput_Tick();
        vTaskDelay(10);
    }
}

/* LCD OUTPUT STATE MACHINE */
enum setlcd_State {setlcd_INIT,setlcd_RUN} setlcd_state;

void setlcd_init(){
    setlcd_state = setlcd_INIT;
}

void setlcd_Tick(){
    //Actions
    switch(setlcd_state){
        case setlcd_INIT:
            break;
        case setlcd_RUN:
            PORTD = input;
            PORTB = input >> 8;
            break;
        default:
            break;
    }
    //Transitions
    switch(setlcd_state){
        case setlcd_INIT:
            setlcd_state = setlcd_RUN;
            break;
        case setlcd_RUN:
            setlcd_state = setlcd_RUN;
            break;
        default:
            setlcd_state = setlcd_INIT;
            break;
    }
}
void setlcd_Task()
{
    setlcd_init();
    while (1) {
        setlcd_Tick();
        vTaskDelay(10);
    }
}

void StartSecPulse(unsigned portBASE_TYPE Priority)
{
    xTaskCreate(getinput_Task, (signed portCHAR *)"counterTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
    xTaskCreate(setlcd_Task, (signed portCHAR *)"xmitTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
}


int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;      // Set PORTA to input.
    DDRB = 0xFF; PORTB = 0x00;
    DDRD = 0xFF; PORTD = 0x00;      // Set PORTD to output.
    
    // Initialize ADC.
    A2D_init();

    //Start Tasks
    StartSecPulse(1);
    //RunScheduler
    vTaskStartScheduler();
    
    return 0;
}
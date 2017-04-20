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

unsigned char rows[5] =          {0x01,0x02,0x04,0x08,0x10};

unsigned char column[8] =        {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};  

unsigned char row,col;
unsigned char left,right,up,down;


/* GLOBAL FUNCTIONS */
void A2D_init() {
    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
    // ADEN: Enables ADC conversion.
    // ADSC: Starts A2D conversion.
    // ADATE: Enables autotriggering, allos for constant A2D conversion.
}
unsigned short input;

void Set_A2D_Pin(unsigned char pinNum) {
    ADMUX = (pinNum <= 0x07) ? pinNum : ADMUX;
    // Allow channel to stabilize
    static unsigned char i = 0;
    for ( i=0; i<15; i++ ) { asm("nop"); } 
}

/* SET LCD STATE MACHINE */
enum getinput_State {getinput_INIT,getinput_UD,getinput_LR} getinput_state;

void getinput_init(){
    getinput_state = getinput_INIT;
}

void getinput_Tick(){
    //Actions
    input = ADC;
    switch(getinput_state){
        case getinput_INIT:
            Set_A2D_Pin(0x00);
            break;
        case getinput_LR:
            input = ADC;
            if (input >= 580) {
                left = 0;
                right = 1;
            } else if (input <= 490) {
                left = 1;
                right = 0;
            } else {
                left = 0;
                right = 0;
            }
            Set_A2D_Pin(0x01);
            break;
        case getinput_UD:
            if (input >= 580) {
                down = 0;
                up = 1;
            } else if (input <= 490) {
                down = 1;
                up = 0;
            } else {
                down = 0;
                up = 0;
            }
            Set_A2D_Pin(0x00);
            break;
        default:
            break;
    }
    //Transitions
    switch(getinput_state){
        case getinput_INIT:
            getinput_state = getinput_LR;
            break;
        case getinput_LR:
            getinput_state = getinput_UD;
            break;
        case getinput_UD:
            getinput_state = getinput_LR;
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
    left = 1;
    right = 1;
    up = 1;
    down = 1;
}

void setlcd_Tick(){
    //Actions
    switch(setlcd_state){
        case setlcd_INIT:
            break;
        case setlcd_RUN:
            PORTD = ( up | down << 1 | left << 3 | right << 5 );
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
        vTaskDelay(500);
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
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;      // Set PORTC to output.
    
    // Initialize ADC.
    A2D_init();

    //Start Tasks
    StartSecPulse(1);
    //RunScheduler
    vTaskStartScheduler();
    
    return 0;
}
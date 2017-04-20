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
/*
unsigned char off_array[5][8] =     {   {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},  
                                        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},  
                                        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},  
                                        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},  
                                        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}     };  

unsigned char curr_array[5][8] =     {  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},  
                                        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},  
                                        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},  
                                        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},  
                                        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}     };        
*/
unsigned char row,col;


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
enum setmatrix_State {setmatrix_INIT,setmatrix_RUN} setmatrix_state;

void setmatrix_init(){
    setmatrix_state = setmatrix_INIT;
}

void setmatrix_Tick(){
    //Actions
    switch(setmatrix_state){
        case setmatrix_INIT:
            break;
        case setmatrix_RUN:
            if ( col < 7 ) {
                col++;
            } else {
                col = 0;
                if (row < 3) {
                    row++;
                } else {
                    row = 0;
                }
            }
            PORTC = column[col];
            PORTD = ~rows[row];
            break;
        default:
            break;
    }
    //Transitions
    switch(setmatrix_state){
        case setmatrix_INIT:
            setmatrix_state = setmatrix_RUN;
            break;
        case setmatrix_RUN:
            setmatrix_state = setmatrix_RUN;
            break;
        default:
            setmatrix_state = setmatrix_INIT;
            break;
    }
}
void setmatrix_Task()
{
    setmatrix_init();
    while (1) {
        setmatrix_Tick();
        vTaskDelay(500);
    }
}

void StartSecPulse(unsigned portBASE_TYPE Priority)
{
    xTaskCreate(getinput_Task, (signed portCHAR *)"counterTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
    xTaskCreate(setmatrix_Task, (signed portCHAR *)"xmitTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
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
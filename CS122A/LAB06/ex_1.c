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
unsigned char output;               // Output going to shift register
unsigned char button1, button2;     // Buttons
unsigned char row, pattern;             // Row and Pattern

unsigned char singlepin_vals[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

/* GLOBAL FUNCTIONS */


/* PATTERN MANIPUPATING STATE MACHINE */
enum setpattern_State {setpattern_INIT,setpattern_RUN} setpattern_state;

void setpattern_init(){
    setpattern_state = setpattern_INIT;
}

void setpattern_Tick(){
    //Actions
    switch(setpattern_state){
        case setpattern_INIT:
            break;
        case setpattern_RUN:
            if (button1 && !button2) {
                if (row < 5) {
                    row++;
                }
            } else if (!button1 && button2) {
                if (row > 0) {
                    row--;
                }
            }
            pattern = 0xFF;
            break;
        default:
            break;
    }
    //Transitions
    switch(setpattern_state){
        case setpattern_INIT:
            setpattern_state = setpattern_RUN;
            break;
        case setpattern_RUN:
            setpattern_state = setpattern_RUN;
            break;
        default:
            setpattern_state = setpattern_INIT;
            break;
    }
}
void setpattern_Task()
{
    setpattern_init();
    while (1) {
        setpattern_Tick();
        vTaskDelay(500);
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
            PORTC = pattern;
            PORTD = ~singlepin_vals[row];
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

/* BUTTON CHECKING STATE MACHINE */
enum checkbtn_State {checkbtn_INIT,checkbtn_RUN} checkbtn_state;

void checkbtn_init(){
    checkbtn_state = checkbtn_INIT;
}

void checkbtn_Tick(){
    
    //Actions
    switch(checkbtn_state){
        case checkbtn_INIT:
            break;
        case checkbtn_RUN:
            button1 = (~PINA & 0x01);
            button2 = (~PINA & 0x02);
            break;
        default:
            break;
    }
    //Transitions
    switch(checkbtn_state){
        case checkbtn_INIT:
            checkbtn_state = checkbtn_RUN;
            break;
        case checkbtn_RUN:
            checkbtn_state = checkbtn_RUN;
            break;
        default:
            checkbtn_state = checkbtn_INIT;
            break;
    }
}
void checkbtn_Task()
{
    checkbtn_init();
    while (1) {
        checkbtn_Tick();
        vTaskDelay(100);
    }
}

void StartSecPulse(unsigned portBASE_TYPE Priority)
{
    xTaskCreate(setpattern_Task, (signed portCHAR *)"counterTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
    xTaskCreate(setlcd_Task, (signed portCHAR *)"xmitTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
    xTaskCreate(checkbtn_Task, (signed portCHAR *)"buttonTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
}


int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;      // Set PORTA to input.
    DDRC = 0xFF; PORTC = 0x00;      // Set PORTB to output.
    DDRD = 0xFF; PORTD = 0x00;      // Set PORTB to output.
    

    //Start Tasks
    StartSecPulse(1);
    //RunScheduler
    vTaskStartScheduler();
    
    return 0;
}
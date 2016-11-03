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
unsigned char output;               // Output going to stepper motor.
unsigned char button1, button2, button3;     // Buttons

unsigned char motor_phase[8] = {0x01,0x03,0x02,0x06,0x04,0x0C,0x08,0x09};
unsigned char phase;
unsigned short steps;

/* GLOBAL FUNCTIONS */


/* PATTERN MANIPUPATING STATE MACHINE */
enum setmotor_State {setmotor_INIT,setmotor_RUN} setmotor_state;

void setmotor_init(){
    setmotor_state = setmotor_INIT;
    phase = 0;
}

void setmotor_Tick(){
    //Actions
    switch(setmotor_state){
        case setmotor_INIT:
            break;
        case setmotor_RUN:
            if (steps > 0) {
                if (phase < 7) {
                    phase++;
                } else {
                    phase = 0;
                }
                steps--;
            }
            PORTB = motor_phase[phase];
            break;
        default:
            break;
    }
    //Transitions
    switch(setmotor_state){
        case setmotor_INIT:
            setmotor_state = setmotor_RUN;
            break;
        case setmotor_RUN:
            setmotor_state = setmotor_RUN;
            break;
        default:
            setmotor_state = setmotor_INIT;
            break;
    }
}
void setmotor_Task()
{
    setmotor_init();
    while (1) {
        setmotor_Tick();
        vTaskDelay(3);
    }
}

/* SET ROTATION STATE MACHINE */
enum setrot_State {setrot_INIT,setrot_RUN} setrot_state;

void setrot_init(){
    setrot_state = setrot_INIT;
    steps = 1000;
}

void setrot_Tick(){
    
    //Actions
    switch(setrot_state){
        case setrot_INIT:
            break;
        case setrot_RUN:
            if ( button1 && !(button2 || button3) ) {
                button1 = 0;
                steps = 1024;
            } else if ( button2 && !(button1 || button3) ) {
                button2 = 0;
                steps = 2048;
            } else if ( button3 && !(button1 || button1) ) {
                button3 = 0;
                steps = 4096;
            }
            break;
        default:
            break;
    }
    //Transitions
    switch(setrot_state){
        case setrot_INIT:
            setrot_state = setrot_RUN;
            break;
        case setrot_RUN:
            setrot_state = setrot_RUN;
            break;
        default:
            setrot_state = setrot_INIT;
            break;
    }
}
void setrot_Task()
{
    setrot_init();
    while (1) {
        setrot_Tick();
        vTaskDelay(3);
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
            button3 = (~PINA & 0x04);
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
        vTaskDelay(3);
    }
}


void StartSecPulse(unsigned portBASE_TYPE Priority)
{
    xTaskCreate(setmotor_Task, (signed portCHAR *)"setmotorTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
    xTaskCreate(setrot_Task, (signed portCHAR *)"setrot_Task", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
    xTaskCreate(checkbtn_Task, (signed portCHAR *)"buttonTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
}


int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;      // Set PORTA to input.
    DDRB = 0xFF; PORTB = 0x00;      // Set PORTB to output.
    

    //Start Tasks
    StartSecPulse(1);
    //RunScheduler
    vTaskStartScheduler();
    
    return 0;
}
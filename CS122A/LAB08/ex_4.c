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
#include "keypad.h"

// Definitions

// SetBit and ClrBit


/* GLOBAL VARIABLES */
unsigned char output;               // Output going to stepper motor.

unsigned char motor_phase[8] = {0x01,0x03,0x02,0x06,0x04,0x0C,0x08,0x09};
unsigned char phase, place;         // global iterators
unsigned short steps, angle;
unsigned char keypad_input;     
unsigned char pressFlag, reverseFlag;
unsigned char expr[4];

/* GLOBAL FUNCTIONS */
void setExpression(unsigned char input) {
    expr[place] = input;
    place++;
    if (input == '#' || input == 'A' || input == 'B') {
        if (input == 'B') {
            reverseFlag = 1;
        } else {
            reverseFlag = 0;
        }
        place--;
        expr[place] = 0;
        if (place > 0) {
            place--;
            angle = angle + (expr[place]-48);
            expr[place] = 0;
        }        
        if (place > 0) {
            place--;
            angle = angle + ( (expr[place]-48) * 10);
            expr[place] = 0;
        }
        if (place > 0) {
            place--;
            angle = angle + ( (expr[place]-48) * 100);
            expr[place] = 0;
        }
        steps = (angle / 5.625) * 64;
        place = 0;
        angle = 0;
    }
    if (place > 3) {place = 0;}
}


/* PATTERN MANIPUPATING STATE MACHINE */
enum setmotor_State {setmotor_INIT,setmotor_FORWARD,setmotor_REVERSE} setmotor_state;

void setmotor_init(){
    setmotor_state = setmotor_INIT;
    phase = 0;
}

void setmotor_Tick(){
    //Actions
    switch(setmotor_state){
        case setmotor_INIT:
            break;
        case setmotor_FORWARD:
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
        case setmotor_REVERSE:
            if (steps > 0) {
                if (phase > 0) {
                    phase--;
                } else {
                    phase = 7;
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
            setmotor_state = reverseFlag ? setmotor_REVERSE : setmotor_FORWARD;
            break;
        case setmotor_FORWARD:
            setmotor_state = reverseFlag ? setmotor_REVERSE : setmotor_FORWARD;
            break;
        case setmotor_REVERSE:
            setmotor_state = reverseFlag ? setmotor_REVERSE : setmotor_FORWARD;
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
    steps = 0;
}

void setrot_Tick(){
    
    //Actions
    switch(setrot_state){
        case setrot_INIT:
            break;
        case setrot_RUN:

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

/* KEYPAD INPUT RETRIEVAL STATE MACHINE */
enum getkey_State {getkey_INIT,getkey_WAIT,getkey_PRESS} getkey_state;

void getkey_init(){
    getkey_state = getkey_INIT;
    keypad_input = ' ';
    place = 0;
}

void getkey_Tick(){
    //Actions
    switch(getkey_state){
        case getkey_INIT:
            break;
        case getkey_WAIT:
            if (GetKeypadKey() != '\0') { 
                keypad_input = GetKeypadKey();
                pressFlag = 1;
            }
            break;
        case getkey_PRESS:
            if (GetKeypadKey() == '\0') {
                pressFlag = 0;
                setExpression(keypad_input);
            }
        default:
            break;
    }
    //Transitions
    switch(getkey_state){
        case getkey_INIT:
            getkey_state = getkey_WAIT;
            break;
        case getkey_WAIT:
            getkey_state = pressFlag ? getkey_PRESS : getkey_WAIT;
            break;
        case getkey_PRESS:
            getkey_state = pressFlag ? getkey_PRESS : getkey_WAIT;
            break;
        default:
            getkey_state = getkey_INIT;
            break;
    }
}
void getkey_Task()
{
    getkey_init();
    while (1) {
        getkey_Tick();
        vTaskDelay(30);
    }
}

void StartSecPulse(unsigned portBASE_TYPE Priority)
{
    xTaskCreate(setmotor_Task, (signed portCHAR *)"setmotorTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
    xTaskCreate(setrot_Task, (signed portCHAR *)"setrot_Task", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
    xTaskCreate(getkey_Task, (signed portCHAR *)"buttonTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
}


int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;      // Set PORTA to input.
    DDRB = 0xFF; PORTB = 0x00;      // Set PORTB to output.
    DDRD = 0xF0; PORTD = 0x0F;      // Set PORTC to a ready state for a keypad
    

    //Start Tasks
    StartSecPulse(1);
    //RunScheduler
    vTaskStartScheduler();
    
    return 0;
}
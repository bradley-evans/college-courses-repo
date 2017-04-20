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
unsigned char position;
unsigned char light_arr[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
unsigned char limitFlag;


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
    position = 4;
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
    limitFlag = 0;
}

void setlcd_Tick(){
    //Actions
    switch(setlcd_state){
        case setlcd_INIT:
            break;
        case setlcd_RUN:
            if (input >= 580) {
                if (input >= 800) {
                    position = (position<7) ? position+1 : position;
                } else if (limitFlag) {
                    position = (position<7) ? position+1 : position;
                }
            } else if (input <= 490) {
                if (input <= 280) {
                    position = (position>0) ? position-1 : position;
                } else if (limitFlag) {
                    position = (position>0) ? position-1 : position;
                }
            } 
            limitFlag = !limitFlag;
            PORTD = light_arr[position];
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
    DDRD = 0xFF; PORTD = 0x00;      // Set PORTC to output.
    
    // Initialize ADC.
    A2D_init();

    //Start Tasks
    StartSecPulse(1);
    //RunScheduler
    vTaskStartScheduler();
    
    return 0;
}
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
#define SREG_BUS PORTB
#define SER 0
#define OE 1
#define RCLK 2
#define SRCLK 3
#define SRCLR 4

#define SET_BIT(p,i) ((p) |= (1 << (i)))
#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
#define GET_BIT(p,i) ((p) & (1 << (i)))


/* GLOBAL VARIABLES */
unsigned char output;               // Output going to shift register
unsigned char button1, button2;     // Buttons
unsigned char selection;
unsigned char iterator;

unsigned char patternA[14] = {0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F};
unsigned char patternB[14] = {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01,0x02,0x04,0x08,0x10,0x20,0x40};
unsigned char patternC[14] = {0xAA,0x55,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F};
unsigned char patternD[14] = {0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F};


/* GLOBAL FUNCTIONS */
void transmit_data(unsigned char data) {
    SET_BIT(SREG_BUS,SRCLR);
    CLR_BIT(SREG_BUS,RCLK);
    for (unsigned char i=0; i<8; i++) {
        CLR_BIT(SREG_BUS,SRCLK);
        if (data & 0x01) {
            SET_BIT(SREG_BUS,SER);
        } else {
            CLR_BIT(SREG_BUS,SER);
        }
        data >>= 1;
        SET_BIT(SREG_BUS,SRCLK);
    }
    SET_BIT(SREG_BUS,RCLK);
    CLR_BIT(SREG_BUS,OE);
}

void lightshow(unsigned char it) {
    switch(selection) {
        case 0:
            output = 0x00;
            break;
        case 1:
            output = patternA[it];
            break;
        case 2:
            output = patternB[it];
            break;
        case 3:
            output = patternC[it];
            break;
        case 4:
            output = patternD[it];
            break;
        default:
            output = 0x00;
            break;
    }
}

/* LCD OUTPUT STATE MACHINE */
enum selector_State {selector_INIT,selector_RUN} selector_state;

void selector_init(){
    selector_state = selector_INIT;
    selection = 0;
    output = 0;
    iterator = 0;
}

void selector_Tick(){
    //Actions
    switch(selector_state){
        case selector_INIT:
            break;
        case selector_RUN:
            if (button1 && button2) {
                selection = 0;
            } else if (button1 && !button2) {
                if (selection != 4) {
                    selection++;
                }
            } else if (button2 && !button1) {
                if (selection != 0) {
                    selection--;
                }
            }
            if (iterator < 14) {
                iterator++;
            } else {
                iterator = 0;
            }
            lightshow(iterator);
            break;
        default:
            break;
    }
    //Transitions
    switch(selector_state){
        case selector_INIT:
            selector_state = selector_RUN;
            break;
        case selector_RUN:
            selector_state = selector_RUN;
            break;
        default:
            selector_state = selector_INIT;
            break;
    }
}
void selector_Task()
{
    selector_init();
    while (1) {
        selector_Tick();
        vTaskDelay(200);
    }
}

/* SHIFT REGISTER TRANSMITTER STATE MACHINE */
enum xmit_State {xmit_INIT,xmit_RUN} xmit_state;

void xmit_init(){
    xmit_state = xmit_INIT;
}

void xmit_Tick(){
    
    //Actions
    switch(xmit_state){
        case xmit_INIT:
            break;
        case xmit_RUN:
            transmit_data(output);
            break;
        default:
            break;
    }
    //Transitions
    switch(xmit_state){
        case xmit_INIT:
            xmit_state = xmit_RUN;
            break;
        case xmit_RUN:
            xmit_state = xmit_RUN;
            break;
        default:
            xmit_state = xmit_INIT;
            break;
    }
}
void xmit_Task()
{
    xmit_init();
    while (1) {
        xmit_Tick();
        vTaskDelay(100);
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
    xTaskCreate(selector_Task, (signed portCHAR *)"counterTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
    xTaskCreate(xmit_Task, (signed portCHAR *)"xmitTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
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
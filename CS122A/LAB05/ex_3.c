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
#define SREG_BUS1 PORTB
#define SREG_BUS2 PORTD
#define SER 0
#define OE 1
#define RCLK 2
#define SRCLK 3
#define SRCLR 4

#define SET_BIT(p,i) ((p) |= (1 << (i)))
#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
#define GET_BIT(p,i) ((p) & (1 << (i)))


/* GLOBAL VARIABLES */
unsigned char output1,output2;               // Output going to shift register
unsigned char button1, button2, button3, button4;     // Buttons
unsigned char selection1,selection2;
unsigned char iterator;

unsigned char patternA[14] = {0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F};
unsigned char patternB[14] = {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01,0x02,0x04,0x08,0x10,0x20,0x40};
unsigned char patternC[14] = {0xAA,0x55,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F};
unsigned char patternD[14] = {0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F};


/* GLOBAL FUNCTIONS */
void transmit_data_reg1(unsigned char data) {
    SET_BIT(SREG_BUS1,SRCLR);
    CLR_BIT(SREG_BUS1,RCLK);
    for (unsigned char i=0; i<8; i++) {
        CLR_BIT(SREG_BUS1,SRCLK);
        if (data & 0x01) {
            SET_BIT(SREG_BUS1,SER);
        } else {
            CLR_BIT(SREG_BUS1,SER);
        }
        data >>= 1;
        SET_BIT(SREG_BUS1,SRCLK);
    }
    SET_BIT(SREG_BUS1,RCLK);
    CLR_BIT(SREG_BUS1,OE);
}
void transmit_data_reg2(unsigned char data) {
    SET_BIT(SREG_BUS2,SRCLR);
    CLR_BIT(SREG_BUS2,RCLK);
    for (unsigned char i=0; i<8; i++) {
        CLR_BIT(SREG_BUS2,SRCLK);
        if (data & 0x01) {
            SET_BIT(SREG_BUS2,SER);
        } else {
            CLR_BIT(SREG_BUS2,SER);
        }
        data >>= 1;
        SET_BIT(SREG_BUS2,SRCLK);
    }
    SET_BIT(SREG_BUS2,RCLK);
    CLR_BIT(SREG_BUS2,OE);
}

void lightshow(unsigned char it) {
    switch(selection1) {
        case 0:
            output1 = 0x00;
            break;
        case 1:
            output1 = patternA[it];
            break;
        case 2:
            output1 = patternB[it];
            break;
        case 3:
            output1 = patternC[it];
            break;
        case 4:
            output1 = patternD[it];
            break;
        default:
            output1 = 0x00;
            break;
    }
    switch(selection2) {
        case 0:
            output2 = 0x00;
            break;
        case 1:
            output2 = patternA[it];
            break;
        case 2:
            output2 = patternB[it];
            break;
        case 3:
            output2 = patternC[it];
            break;
        case 4:
            output2 = patternD[it];
            break;
        default:
            output2 = 0x00;
            break;
    }
}

/* LCD OUTPUT STATE MACHINE */
enum selector_State {selector_INIT,selector_RUN} selector_state;

void selector_init(){
    selector_state = selector_INIT;
    selection1 = 0;
    selection2 = 0;
    output1 = 0;
    output2 = 0;
    iterator = 0;
}

void selector_Tick(){
    //Actions
    switch(selector_state){
        case selector_INIT:
            break;
        case selector_RUN:
            if (button1 && button2) {
                selection1 = 0;
            } else if (button1 && !button2) {
                if (selection1 != 4) {
                    selection1++;
                }
            } else if (button2 && !button1) {
                if (selection1 != 0) {
                    selection1--;
                }
            }
            if (button3 && button4) {
                selection2 = 0;
            } else if (button3 && !button4) {
                if (selection2 != 4) {
                    selection2++;
                }
            } else if (button4 && !button3) {
                if (selection2 != 0) {
                    selection2--;
                }
            }
            if (iterator < 14) {
                iterator++;
            } else {
                iterator = 0;
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
        vTaskDelay(100);
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
            transmit_data_reg1(output1);
            transmit_data_reg2(output2);
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
            button3 = (~PINA & 0x04);
            button4 = (~PINA & 0x08);
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
    DDRD = 0XFF; PORTD = 0X00;      // Set PORTD to output.

    //Start Tasks
    StartSecPulse(1);
    //RunScheduler
    vTaskStartScheduler();
    
    return 0;
}
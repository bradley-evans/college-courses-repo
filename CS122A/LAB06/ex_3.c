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
unsigned char button1, button2, button3, button4;     // Buttons
unsigned char row, col_x, col_y;             // Row and Column
unsigned char shift_y, shift_x;

unsigned char row_vals_square[40] = {   0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,  
                                        0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,  
                                        0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,  
                                        0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,  
                                        0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10 };

unsigned char col_vals_square[7][8] = {     {   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00     },
                                            {   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00     },
                                            {   0x00,0x00,0x04,0x08,0x10,0x20,0x00,0x00     },  
                                            {   0x00,0x00,0x04,0x00,0x00,0x20,0x00,0x00     },
                                            {   0x00,0x00,0x04,0x08,0x10,0x20,0x00,0x00     },
                                            {   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00     },
                                            {   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00     }   };
unsigned char row_val, col_val;

/* GLOBAL FUNCTIONS */


/* PATTERN MANIPUPATING STATE MACHINE */
enum setpattern_State {setpattern_INIT,setpattern_RUN} setpattern_state;

void setpattern_init(){
    setpattern_state = setpattern_INIT;
    shift_x = 2;
    shift_y = 1;
}

void setpattern_Tick(){
    //Actions
    switch(setpattern_state){
        case setpattern_INIT:
            break;
        case setpattern_RUN:
            if (button1 && !button2) {
                if (shift_x < 4) {
                    shift_x++;
                }
            } else if (button2 && !button1) {
                if (shift_x > 0) {
                    shift_x--;
                }
            }
            if (button3 && !button4) {
                if (shift_y < 2) {
                    shift_y++;
                }
            } else if (button4 && !button3) {
                if (shift_y > 0) {
                    shift_y--;
                }
            }
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
        vTaskDelay(1);
    }
}

/* LCD OUTPUT STATE MACHINE */
enum setlcd_State {setlcd_INIT,setlcd_RUN} setlcd_state;

void setlcd_init(){
    setlcd_state = setlcd_INIT;
    row = 0;
    col_x = 0;
    col_y = 0;
}

void setlcd_Tick(){
    //Actions
    switch(setlcd_state){
        case setlcd_INIT:
            break;
        case setlcd_RUN:
            if (row < 39) {
                row++;
            } else {
                row = 0;
                col_x = 0;
                col_y = 0;
            }
            if (col_x < 7) {
                col_x++;
            } else {
                col_x = 0;
                if (col_y < 5) {
                    col_y++;
                } else {
                    col_y = 0;
                }
            }
            PORTC = col_vals_square[col_y+shift_y][col_x]<<2>>shift_x;
            PORTD = ~row_vals_square[row];
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
        vTaskDelay(1);
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
        vTaskDelay(500);
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
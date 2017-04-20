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
#include "usart_ATmega1284.h"

enum follow_State {follow_INIT,follow_RUN} follow_state;

unsigned char led_state;

void follow_init(){
    follow_state = follow_INIT;
}

void follow_Tick(){
    //Actions
    switch(follow_state){
        case follow_INIT:
            PORTA = 0xFF;
            break;
        case follow_RUN:
            while (!USART_HasReceived(0));
            if (USART_HasReceived(0)) {
                led_state = USART_Receive(0);
                USART_Flush(0);
            }
            PORTA = (led_state|0x02);
            break;
        default:
            PORTA = 0xFF;
            break;
    }
    //Transitions
    switch(follow_state){
        case follow_INIT:
            follow_state = follow_RUN;
            break;
        case follow_RUN:
            follow_state = follow_RUN;
            break;
        default:
            follow_state = follow_INIT;
            break;
    }
}
void follow_Task()
{
    follow_init();
    while (1) {
        follow_Tick();
        vTaskDelay(10);
    }
}

void StartSecPulse(unsigned portBASE_TYPE Priority)
{
    xTaskCreate(follow_Task, (signed portCHAR *)"LedSecTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
}

int main(void)
{
    DDRA = 0x00; PORTA=0xFF;
    DDRD = 0xFF;

    initUSART(0); // initializes USART0
    initUSART(1); // initializes USART1

    //Start Tasks
    StartSecPulse(1);
    //RunScheduler
    vTaskStartScheduler();
    
    return 0;
}
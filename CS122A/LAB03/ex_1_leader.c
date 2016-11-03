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

enum blink_State {blink_INIT,blink_ON,blink_OFF} blink_state;

unsigned char blink_led;
unsigned char p2_led;
unsigned char p4_led;

void sendState(unsigned char this_state) {
    if (USART_IsSendReady(0)) {
        USART_Send(this_state,0);
    }
}


void blink_init(){
    blink_state = blink_INIT;
}

void blink_Tick(){
    //Actions
    switch(blink_state){
        case blink_INIT:
            PORTA = 0;
            sendState(0);
            break;
        case blink_ON:
            PORTA = 0xFF;
            sendState(0xFF);
            break;
        case blink_OFF:
            PORTA = 0;
            sendState(0);
            break;
        default:
            PORTA = 0;
            sendState(0);
            break;
    }
    //Transitions
    switch(blink_state){
        case blink_INIT:
            blink_state = blink_ON;
            break;
        case blink_ON:
            blink_state = blink_OFF;
            break;
        case blink_OFF:
            blink_state = blink_ON;
            break;
        default:
            blink_state = blink_INIT;
            break;
    }
}
void blink_Task()
{
    blink_init();
    while (1) {
        blink_Tick();
        vTaskDelay(100);
    }
}

void StartSecPulse(unsigned portBASE_TYPE Priority)
{
    xTaskCreate(blink_Task, (signed portCHAR *)"LedSecTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
}

int main(void)
{    
    DDRA = 0x00; PORTA = 0xFF;      // Set PORTA to output.
    DDRB = 0x00; PORTB = 0xFF;      // Set PORTB to output.
    DDRD = 0x00; PORTD = 0xFF;      // Set PORTD to output
    
    //Start Tasks
    StartSecPulse(1);
    //RunScheduler
    vTaskStartScheduler();
    
    return 0;
}
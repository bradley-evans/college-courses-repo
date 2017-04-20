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

/* GLOBAL VARIABLES */
unsigned char follow_led;
unsigned char leader_led;
unsigned char buttonFlag;
unsigned short noPacketCount;
unsigned char autoLead;

/* GLOBAL FUNCTIONS */
void sendState(unsigned char this_state) {
    if (USART_IsSendReady(0)) {
        USART_Send(this_state,0);
    }
}

/* LEADER STATE MACHINE */
enum leader_State {leader_INIT,leader_ON,leader_FOLLOW,leader_OFF} leader_state;

void leader_init(){
    leader_state = leader_INIT;
    leader_led = 0;
}

void leader_Tick(){
    //Actions
    switch(leader_state){
        case leader_INIT:
            leader_led = 0;
            sendState(0);
            break;
        case leader_ON:
            leader_led = 0x01;
            sendState(0x01);
            break;
        case leader_OFF:
            leader_led = 0;
            sendState(0);
            break;
        default:
            leader_led = 0;
            sendState(0);
            break;
    }
    //Transitions
    switch(leader_state){
        case leader_INIT:
            leader_state = leader_ON;
            break;
        case leader_ON:
            leader_state = leader_OFF;
            break;
        case leader_OFF:
            leader_state = leader_ON;
            break;
        default:
            leader_state = leader_INIT;
            break;
    }
}
void leader_Task()
{
    leader_init();
    while (1) {
        leader_Tick();
        vTaskDelay(500);
    }
}

/* FOLLOWER STATE MACHINE */

enum follow_State {follow_INIT,follow_RUN} follow_state;

void follow_init(){
    follow_state = follow_INIT;
    follow_led = 0;
    noPacketCount = 0;
}

void follow_Tick(){
    //Actions
    switch(follow_state){
        case follow_INIT:
            follow_led = 0x00;
            break;
        case follow_RUN:
            if (USART_HasReceived(0)) {
                noPacketCount = 0;
                autoLead = 0;
                follow_led = USART_Receive(0);
                USART_Flush(0);
            } else {
                noPacketCount++;
                if (noPacketCount >= 300) {
                    autoLead = 1;
                }
            }
            break;
        default:
            follow_led = 0x00;
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

/* BLINK MULTIPLEXER */

enum blink_State {blink_INIT,blink_RUN} blink_state;

void blink_init(){
    blink_state = blink_INIT;
    buttonFlag = 0;
    PORTA = 0;
}

void blink_Tick(){
    buttonFlag = (~PINB & 0x01);
    //Actions
    switch(blink_state){
        case blink_INIT:
            PORTA = 0x00;
            break;
        case blink_RUN:
            if (buttonFlag || autoLead) {
                PORTA = leader_led & 0x01;
            } else {
                PORTA = follow_led | 0x02;
            }
            break;
        default:
            PORTA = 0x00;
            break;
    }
    //Transitions
    switch(blink_state){
        case blink_INIT:
            blink_state = blink_RUN;
            break;
        case blink_RUN:
            blink_state = blink_RUN;
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
        vTaskDelay(10);
    }
}

void StartSecPulse(unsigned portBASE_TYPE Priority)
{
    xTaskCreate(leader_Task, (signed portCHAR *)"LedSecTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
    xTaskCreate(follow_Task, (signed portCHAR *)"LedSecTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
    xTaskCreate(blink_Task, (signed portCHAR *)"LedSecTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );

}


int main(void)
{
    DDRA = 0x00; PORTA=0xFF;    // Set PORTA to output.
    DDRB = 0xFF; PORTB = 0x00;  // Set PORTB to input.
    DDRD = 0xFF;                

    initUSART(0); // initializes USART0
    initUSART(1); // initializes USART1

    //Start Tasks
    StartSecPulse(1);
    //RunScheduler
    vTaskStartScheduler();
    
    return 0;
}
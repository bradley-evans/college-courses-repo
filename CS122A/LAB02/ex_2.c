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
enum p0_State {p0_INIT,p0_BLINK} p0_state;
enum p2_State {p2_INIT,p2_BLINK} p2_state;
enum p4_State {p4_INIT,p4_BLINK} p4_state;
enum output_State {output_INIT,output_RUN} output_state;

unsigned char p0_led;
unsigned char p2_led;
unsigned char p4_led;

void p0_init(){
    p0_state = p0_INIT;
}

void p0_Tick(){
    //Actions
    switch(p0_state){
        case p0_INIT:
            p0_led = 0;
        break;
        case p0_BLINK:
            if (p0_led == 1) {
                p0_led = 0;
            } else {
                p0_led = 1;
            }
        break;
        default:
            p0_led = 0;
        break;
    }
    //Transitions
    switch(p0_state){
        case p0_INIT:
            p0_state=p0_BLINK;
            break;
        case p0_BLINK:
            p0_state=p0_BLINK;
            break;
        default:
            p0_state=p0_INIT;
            break;
    }
}

void p2_init(){
    p2_state = p2_INIT;
}

void p2_Tick(){
    //Actions
    switch(p2_state){
        case p2_INIT:
            p2_led = 0;
        break;
        case p2_BLINK:
            if (p2_led == 1) {
                p2_led = 0;
            } else {
                p2_led = 1;
            }
        break;
        default:
            p2_led = 0;
        break;
    }
    //Transitions
    switch(p2_state){
        case p2_INIT:
            p2_state=p2_BLINK;
            break;
        case p2_BLINK:
            p2_state=p2_BLINK;
            break;
        default:
            p2_state=p2_INIT;
            break;
    }
}

void p4_init(){
    p4_state = p4_INIT;
}

void p4_Tick(){
    //Actions
    switch(p4_state){
        case p4_INIT:
            p4_led = 0;
        break;
        case p4_BLINK:
            if (p4_led == 1) {
                p4_led = 0;
            } else {
                p4_led = 1;
            }
        break;
        default:
            p4_led = 0;
        break;
    }
    //Transitions
    switch(p4_state){
        case p4_INIT:
            p4_state=p4_BLINK;
            break;
        case p4_BLINK:
            p4_state=p4_BLINK;
            break;
        default:
            p4_state=p4_INIT;
            break;
    }
}

void output_init(){
    output_state = output_INIT;
}

void output_Tick(){
    //Actions
    switch(output_state){
        case output_INIT:
            PORTD=0;
        break;
        case output_RUN:
            PORTD = (p0_led | (p2_led << 2) | (p4_led << 4));
        break;
        default:
            PORTD = 255;
        break;
    }
    //Transitions
    switch(output_state){
        case output_INIT:
            output_state=output_RUN;
            break;
        case output_RUN:
            output_state=output_RUN;
            break;
        default:
            output_state=output_INIT;
            break;
    }
}

void p0_Task()
{
    p0_init();
    while (1) {
        p0_Tick();
        vTaskDelay(50);
    }
}

void p2_Task()
{
    p2_init();
    while (1) {
        p2_Tick();
        vTaskDelay(100);
    }
}

void p4_Task()
{
    p4_init();
    while (1) {
        p4_Tick();
        vTaskDelay(250);
    }
}

void output_Task()
{
    output_init();
    while (1) {
        output_Tick();
        vTaskDelay(50);
    }
}

void StartSecPulse(unsigned portBASE_TYPE Priority)
{
    xTaskCreate(p0_Task, (signed portCHAR *)"LedSecTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
    xTaskCreate(p2_Task, (signed portCHAR *)"LedSecTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
    xTaskCreate(p4_Task, (signed portCHAR *)"LedSecTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
    xTaskCreate(output_Task, (signed portCHAR *)"LedSecTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
}

int main(void)
{
    DDRA = 0x00; PORTA=0xFF;
    DDRD = 0xFF;
    //Start Tasks
    StartSecPulse(1);
    //RunScheduler
    vTaskStartScheduler();
    
    return 0;
}
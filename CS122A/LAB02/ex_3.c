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
enum LED_State {LED_INIT,LED_INC,LED_DEC} LED_state;
enum output_State {output_INIT,output_RUN} output_state;

unsigned char lights;

void LED_init(){
    LED_state = LED_INIT;
}

void LED_Tick(){
    //Actions
    switch(LED_state){
        case LED_INIT:
            lights = 1;
            break;
        case LED_INC:
            lights = lights << 1;
            break;
        case LED_DEC:
            lights = lights >> 1;
            break;
        default:
            lights = 129;
            break;
    }
    //Transitions
    switch(LED_state){
        case LED_INIT:
            LED_state=LED_INC;
            break;
        case LED_INC:
            if (lights == 128) {
                LED_state = LED_DEC;
            } else {
                LED_state = LED_INC;
            }
            break;
        case LED_DEC:
            if (lights == 1) {
                LED_state = LED_INC;
            } else {
                LED_state = LED_DEC;
            }
            break;
        default:
            LED_state=LED_INIT;
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
        PORTD=lights;
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

void LED_Task()
{
    LED_init();
    while (1) {
        LED_Tick();
        vTaskDelay(50);
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
    xTaskCreate(LED_Task, (signed portCHAR *)"LedSecTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
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
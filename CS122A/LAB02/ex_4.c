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

enum cb_State {cb_INIT,cb_CHECK,cb_WAIT} cb_state;

unsigned char lights;
unsigned char buttonFlag;

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
            } else if (buttonFlag == 1) {
            buttonFlag = 0;
            LED_state = LED_DEC;
            } else {
            LED_state = LED_INC;
        }
        break;
        case LED_DEC:
        if (lights == 1) {
            LED_state = LED_INC;
            } else if (buttonFlag == 1) {
            buttonFlag = 0;
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

void checkbutton_init() {
    buttonFlag = 0;
    cb_state = cb_INIT;
}

void checkbutton_Tick(){
    //Actions
    switch(cb_state){
        case cb_INIT:
        buttonFlag=0;
        break;
        case cb_CHECK:
        buttonFlag = (~PINA & 0x01);
        break;
        case cb_WAIT:
        break;
        default:
        buttonFlag=0;
        break;
    }
    //Transitions
    switch(cb_state){
        case cb_INIT:
        cb_state=cb_CHECK;
        break;
        case cb_CHECK:
        if (buttonFlag) {
            cb_state = cb_WAIT;
            } else {
            cb_state = cb_CHECK;
        }
        break;
        case cb_WAIT:
        if (buttonFlag == 0) {
            cb_state = cb_CHECK;
            } else {
            cb_state = cb_WAIT;
        }
        break;
        default:
        cb_state=cb_INIT;
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

void checkbutton_Task() {
    checkbutton_init();
    while(1) {
        checkbutton_Tick();
        vTaskDelay(10);
    }
}

void StartSecPulse(unsigned portBASE_TYPE Priority)
{
    xTaskCreate(LED_Task, (signed portCHAR *)"LedSecTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
    xTaskCreate(checkbutton_Task, (signed portCHAR *)"LedSecTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
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
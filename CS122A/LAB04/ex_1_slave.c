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

//FreeRTOS include files:
#include "FreeRTOS.h"
#include "task.h"
#include "croutine.h"
#include "usart_ATmega1284.h"

// Definitions
#define DDR_SPI DDRB
#define DD_MISO 6
#define DD_MOSI 5
#define DD_SCK 7

/* GLOBAL VARIABLES */
unsigned char receivedData;     // stores data from SPI
unsigned char data;             // stores actual data for transmission
unsigned char iter;
unsigned char speed, pattern;
unsigned char timing, pace;
unsigned char patternA[14] = {0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F};
unsigned char patternB[14] = {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01,0x02,0x04,0x08,0x10,0x20,0x40};
unsigned char patternC[14] = {0xAA,0x55,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F};
unsigned char patternD[14] = {0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F};

/* GLOBAL FUNCTIONS */
// Servant Initialization
void SPI_SlaveInit(void) {
    // set DDRB to have MISO line as output and MOSI, SCK, and SS as input
    DDRB = 0x40;
    // set SPCR register to enable SPI and enable SPI interrupt (pg. 168)
    SPCR = SPCR|0xC0;
    // make sure global interrupts are enabled on SREG register (pg. 9)
    SREG = SREG|0x80;
   
}
 
 
ISR(SPI_STC_vect) { // this is enabled in with the SPCR register’s “SPI
    // Interrupt Enable”
    // SPDR contains the received data, e.g. unsigned char receivedData =
    // SPDR;
    receivedData=SPDR;
}

void parseData(void) {
    
    speed = receivedData & 0x0F;
    pattern = receivedData >> 4;
    if (speed == 1) {
        pace = 5;
    } else if (speed == 2) {
        pace = 10;
    } else if (speed == 3) {
        pace = 15;
    } else {
        pace = 20;
    }
}

/* SLAVE STATE MACHINE */
enum getdata_State {getdata_INIT,getdata_RUN} getdata_state;

void getdata_init(){
    getdata_state = getdata_INIT;
    SPI_SlaveInit();
}

void getdata_Tick(){
    //Actions
    switch(getdata_state){
        case getdata_INIT:
            break;
        case getdata_RUN:
            parseData();
            break;
        default:
            break;
    }
    //Transitions
    switch(getdata_state){
        case getdata_INIT:
            getdata_state = getdata_RUN;
            break;
        case getdata_RUN:
            getdata_state = getdata_RUN;
            break;
        default:
            getdata_state = getdata_INIT;
            break;
    }
}
void getdata_Task()
{
    getdata_init();
    while (1) {
        getdata_Tick();
        vTaskDelay(100);
    }
}

enum outputled_State {outputled_INIT,outputled_RUN} outputled_state;

void outputled_init(){
    outputled_state = outputled_INIT;
    iter = 0;
    timing = 0;
}

void outputled_Tick(){
    //Actions
    switch(outputled_state){
        case outputled_INIT:
            break;
        case outputled_RUN:
            timing = timing + 1;
            if ( (timing % pace) == 0 ) {
                if (pattern == 1) {
                    PORTA = patternA[iter];
                    iter = iter + 1;
                } else if (pattern == 2) {
                    PORTA = patternB[iter];
                    iter = iter + 1;
                } else if (pattern == 3) {
                    PORTA = patternC[iter];
                    iter = iter + 1;
                } else {
                    PORTA = patternD[iter];
                    iter = iter + 1;
                }
            }
            if (timing > 100) {
                timing = 0;
            }
            if (iter == 14) {
                iter = 0;
            }
            break;
        default:
            break;
    }
    //Transitions
    switch(outputled_state){
        case outputled_INIT:
            outputled_state = outputled_RUN;
            break;
        case outputled_RUN:
            outputled_state = outputled_RUN;
            break;
        default:
            outputled_state = outputled_INIT;
            break;
    }
}
void outputled_Task()
{
    outputled_init();
    while (1) {
        outputled_Tick();
        vTaskDelay(50);
    }
}

void StartSecPulse(unsigned portBASE_TYPE Priority)
{
    xTaskCreate(getdata_Task, (signed portCHAR *)"GetDataTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
    xTaskCreate(outputled_Task, (signed portCHAR *)"GetDataTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );    
}


int main(void)
{
    DDRA = 0xFF; PORTA = 0x00;      // Set PORTA to output.
    DDRB = 0x00; PORTB = 0xFF;      // Set PORTB to input.


    //Start Tasks
    StartSecPulse(1);
    //RunScheduler
    vTaskStartScheduler();
    
    return 0;
}
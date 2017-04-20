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
#include "lcd.h"     // conflcits with io.h?
#include "bit.h"
#include "keypad.h"

// Definitions
#define DDR_SPI DDRB
#define DD_MISO 6
#define DD_MOSI 5
#define DD_SCK 7


/* GLOBAL VARIABLES */
unsigned char data;             // stores actual data for transmission
unsigned char speed = '0', pattern = '0';   // stores speed, pattern information
unsigned char lcd_waiting[32] = "Waiting...                      ";
unsigned char lcd_running[32] = "Running...                      ";
unsigned char keypad_input;
unsigned char selected = 0;
unsigned char patternA[14] = {0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F};
unsigned char patternB[14] = {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01,0x02,0x04,0x08,0x10,0x20,0x40};
unsigned char patternC[14] = {0xAA,0x55,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F};
unsigned char patternD[14] = {0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F};

/* GLOBAL FUNCTIONS */
void parseData(void) {
    if      (speed == '0') {
        data = (data & 0xF0);
        data = (data | 0x00);
    } else if (speed == '1') {
        data = (data & 0xF0);
        data = (data | 0x01);
    } else if (speed == '2') { 
        data = (data & 0xF0);
        data = (data | 0x02);
    } else if (speed == '3') { 
        data = (data & 0xF0);
        data = (data | 0x03);
    } else if (speed == '4') { 
        data = (data & 0xF0);
        data = (data | 0x04);
    }    
    if      (pattern == '0') {
        data = (data & 0x0F);
        data = (data | 0x00);
    } else if (pattern == '1') {
        data = (data & 0x0F);
        data = (data | 0x10);
    } else if (pattern == '2') { 
        data = (data & 0x0F);
        data = (data | 0x20);
    } else if (pattern == '3') { 
        data = (data & 0x0F);
        data = (data | 0x30);
    } else if (pattern == '4') { 
        data = (data & 0x0F);
        data = (data | 0x40);
    }
}

// Master Initialization Function
void SPI_MasterInit(void){
    DDRB = 0xB0;
    SPCR |= 0x51;
    SREG = SREG|0x80;
    //spsr
}
 
void SPI_MasterTransmit(char cData)
{
    /* Start transmission */
    SPDR = cData;
    /* Wait for transmission complete */
    while(!(SPSR & (1<<SPIF))){
        ;
    }
}

/* LCD OUTPUT STATE MACHINE */
enum lcdout_State {lcdout_INIT,lcdout_RUN} lcdout_state;

void lcdout_init(){
    lcdout_state = lcdout_INIT;
    LCD_init();
}

void lcdout_Tick(){
    //Actions
    switch(lcdout_state){
        case lcdout_INIT:
            break;
        case lcdout_RUN:
            lcd_output[11] = speed;
            lcd_output[27] = pattern;
            if (selected == 0) { 
                lcd_output[0] = '*';
                lcd_output[16] = ' ';
            } else if (selected == 1) {
                lcd_output[0] = ' ';
                lcd_output[16] = '*';
            }
            LCD_DisplayString(1,lcd_output);
            break;
        default:
            break;
    }
    //Transitions
    switch(lcdout_state){
        case lcdout_INIT:
            lcdout_state = lcdout_RUN;
            break;
        case lcdout_RUN:
            lcdout_state = lcdout_RUN;
            break;
        default:
            lcdout_state = lcdout_INIT;
            break;
    }
}
void lcdout_Task()
{
    lcdout_init();
    while (1) {
        lcdout_Tick();
        vTaskDelay(10);
    }
}

/* KEYPAD INPUT RETRIEVAL STATE MACHINE */
enum getkey_State {getkey_INIT,getkey_RUN} getkey_state;

void getkey_init(){
    getkey_state = getkey_INIT;
    keypad_input = ' ';
}

void getkey_Tick(){
    //Actions
    switch(getkey_state){
        case getkey_INIT:
            break;
        case getkey_RUN:
            keypad_input = GetKeypadKey();
            if (keypad_input != '\0') { lcd_output[31]=keypad_input; }
            break;
        default:
            break;
    }
    //Transitions
    switch(getkey_state){
        case getkey_INIT:
            getkey_state = getkey_RUN;
            break;
        case getkey_RUN:
            getkey_state = getkey_RUN;
            break;
        default:
            getkey_state = getkey_INIT;
            break;
    }
}
void getkey_Task()
{
    getkey_init();
    while (1) {
        getkey_Tick();
        vTaskDelay(30);
    }
}

enum menu_State {menu_INIT,menu_RUN} menu_state;

void menu_init(){
    menu_state = menu_INIT;
    keypad_input = ' ';
}

void menu_Tick(){
    //Actions
    switch(menu_state){
        case menu_INIT:
            break;
        case menu_RUN:
            switch(keypad_input) {
                case '*':
                    selected = !selected;
                    break;
                case '1':
                    if (!selected) {
                        speed = '1';
                    } else {
                        pattern = '1';
                    }
                    keypad_input = '\0';
                    break;
                case '2':
                    if (!selected) {
                        speed = '2';
                    } else {
                        pattern = '2';
                    }
                    keypad_input = '\0';
                    break;
                case '3':
                    if (!selected) {
                        speed = '3';
                    } else {
                        pattern = '3';
                    }
                    keypad_input = '\0';
                    break;
                case '4':
                    if (!selected) {
                        speed = '4';
                    } else {
                        pattern = '4';
                    }
                    keypad_input = '\0';
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    //Transitions
    switch(menu_state){
        case menu_INIT:
            menu_state = menu_RUN;
            break;
        case menu_RUN:
            menu_state = menu_RUN;
            break;
        default:
            menu_state = menu_INIT;
            break;
    }
}
void menu_Task()
{
    menu_init();
    while (1) {
        menu_Tick();
        vTaskDelay(200);
    }
}

enum xmit_State {xmit_INIT,xmit_RUN} xmit_state;

void xmit_init(){
    xmit_state = xmit_INIT;
    SPI_MasterInit();
}

void xmit_Tick(){
    
    //Actions
    switch(xmit_state){
        case xmit_INIT:
            break;
        case xmit_RUN:
            parseData();
            SPI_MasterTransmit(data);
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
        vTaskDelay(200);
    }
}

void StartSecPulse(unsigned portBASE_TYPE Priority)
{
    xTaskCreate(lcdout_Task, (signed portCHAR *)"lcdoutTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
    xTaskCreate(getkey_Task, (signed portCHAR *)"getkeyTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
    xTaskCreate(menu_Task, (signed portCHAR *)"menuTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
    xTaskCreate(xmit_Task, (signed portCHAR *)"menuTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL );
}


int main(void)
{
    DDRA = 0xFF; PORTA = 0x00;      // Set PORTA to output.
    DDRB = 0xFF; PORTB = 0x00;      // Set PORTB to output (0-3) input (4-7).
    DDRC = 0xF0; PORTC = 0x0F;      // Set PORTC to a ready state for a keypad
    DDRD = 0xFF; PORTD = 0x00;      // Set PORTD to output
    

    //Start Tasks
    StartSecPulse(1);
    //RunScheduler
    vTaskStartScheduler();
    
    return 0;
}
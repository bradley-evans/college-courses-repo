/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 4/4/2016 14:15:13 PST
*/

#include "rims.h"

/*Define user variables and functions for this state machine here.*/
unsigned char LED_Clk;
void TimerISR() {
   LED_Clk = 1;
}

enum LED_States { LED_init, LED_wait1, LED_led2_on, LED_wait2, LED_led1_on } LED_State;

TickFct_led_latch() {
   switch(LED_State) { // Transitions
      case -1:
         LED_State = LED_init;
         break;
         case LED_init: 
         if (1) {
            LED_State = LED_wait1;
         }
         break;
      case LED_wait1: 
         if (A0) {
            LED_State = LED_led2_on;
         }
         else if (!A0) {
            LED_State = LED_wait1;
         }
         break;
      case LED_led2_on: 
         if (!A0) {
            LED_State = LED_wait2;
         }
         else if (A0) {
            LED_State = LED_led2_on;
         }
         break;
      case LED_wait2: 
         if (A0) {
            LED_State = LED_led1_on;
         }
         else if (!A0) {
            LED_State = LED_wait2;
         }
         break;
      case LED_led1_on: 
         if (A0) {
            LED_State = LED_led1_on;
         }
         else if (!A0) {
            LED_State = LED_wait1;
         }
         break;
      default:
         LED_State = LED_init;
   } // Transitions

   switch(LED_State) { // State actions
      case LED_init:
         B0=1;
         B1=0;
         break;
      case LED_wait1:
         break;
      case LED_led2_on:
         B0=0;
         B1=1;
         
         break;
      case LED_wait2:
         break;
      case LED_led1_on:
         B0=1;
         B1=0;
         break;
      default: // ADD default behaviour below
      break;
   } // State actions

}

int main() {

   const unsigned int periodled_latch = 1000; // 1000 ms default
   TimerSet(periodled_latch);
   TimerOn();
   
   LED_State = -1; // Initial state
   B = 0; // Init outputs

   while(1) {
      TickFct_led_latch();
      while(!LED_Clk);
      LED_Clk = 0;
   } // while (1)
} // Main
/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 4/14/2016 19:7:59 PST
*/

#include "rims.h"

unsigned char tempB;
unsigned char led_Clk;
void TimerISR() {
   led_Clk = 1;
}

enum led_States { led_start, led_blink, led_pause, led_reset } led_State;

TickFct_LED() {
   switch(led_State) { // Transitions
      case -1:
         led_State = led_start;
         break;
         case led_start: 
         if (!A0) {
            led_State = led_blink;
         }
         else if (A0) {
            led_State = led_start;
         }
         break;
      case led_blink: 
         if (!A0) {
            led_State = led_blink;
            if(tempB == 0x00){
                tempB = 0x01;
            }
            else if(tempB == 0x01){
                tempB = 0x02;
            }
            else if(tempB == 0x02){
                tempB = 0x04;
            }
            else if(tempB == 0x04){
                tempB = 0x01;
            }
         }
         else if (A0) {
            led_State = led_pause;
         }
         break;
      case led_pause: 
         if (A0) {
            led_State = led_pause;
         }
         else if (!A0) {
            led_State = led_reset;
         }
         break;
      case led_reset: 
         if (A0) {
            led_State = led_start;
         }
         else if (1) {
            led_State = led_reset;
         }
         else if (!A0) {
            led_State = led_reset;
         }
         break;
      default:
         led_State = led_start;
   } // Transitions

   switch(led_State) { // State actions
      case led_start:
         tempB=0x00;
         break;
      case led_blink:
         B = tempB;
         break;
      case led_pause:
         break;
      case led_reset:
         break;
      default: // ADD default behaviour below
      break;
   } // State actions

}

int main() {

   const unsigned int periodLED = 300;
   TimerSet(periodLED);
   TimerOn();
   
   led_State = -1; // Initial state
   B = 0; // Init outputs

   while(1) {
      TickFct_LED();
      while(!led_Clk);
      led_Clk = 0;
   } // while (1)
} // Main
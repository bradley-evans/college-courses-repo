/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 4/4/2016 17:37:7 PST
*/

#include "rims.h"

/*Define user variables and functions for this state machine here.*/
unsigned char LOCK_Clk;
void TimerISR() {
   LOCK_Clk = 1;
}

enum LOCK_States { LOCK_init_0, LOCK_wait_1, LOCK_input1_2, LOCK_wait_4, LOCK_input2_5, LOCK_unlock_6, LOCK_wait_3 } LOCK_State;

TickFct_lock() {
   switch(LOCK_State) { // Transitions
      case -1:
         LOCK_State = LOCK_init_0;
         break;
         case LOCK_init_0: 
         if (1) {
            LOCK_State = LOCK_wait_1;
         }
         break;
      case LOCK_wait_1: 
         if ((A0||A1||A2||A7)) {
            LOCK_State = LOCK_input1_2;
         }
         else if (!(A0||A1||A2||A7)) {
            LOCK_State = LOCK_wait_1;
         }
         break;
      case LOCK_input1_2: 
         if (A0||A1||!A2||A7) {
            LOCK_State = LOCK_init_0;
         }
         else if (!(A0||A1||!A2||A7)) {
            LOCK_State = LOCK_wait_3;
         }
         break;
      case LOCK_wait_4: 
         if ((A0||A1||A2||A7)) {
            LOCK_State = LOCK_input2_5;
         }
         else if (!(A0||A1||A2||A7)) {
            LOCK_State = LOCK_wait_4;
         }
         break;
      case LOCK_input2_5: 
         if (!(A0||!A1||A2||A7)) {
            LOCK_State = LOCK_unlock_6;
         }
         else if ((A0||!A1||A2||A7)) {
            LOCK_State = LOCK_init_0;
         }
         break;
      case LOCK_unlock_6: 
         if (A7) {
            LOCK_State = LOCK_init_0;
         }
         else if (!A7
) {
            LOCK_State = LOCK_unlock_6;
         }
         break;
      case LOCK_wait_3: 
         if (A0||A1||A2||A3) {
            LOCK_State = LOCK_wait_3;
         }
         else if (!(A0||A1||A2||A3)
) {
            LOCK_State = LOCK_wait_4;
         }
         break;
      default:
         LOCK_State = LOCK_init_0;
   } // Transitions

   switch(LOCK_State) { // State actions
      case LOCK_init_0:
         B0=0;
         B2=0;
         B3=0;
         B4=0;
         break;
      case LOCK_wait_1:
         B2=1;
         B3=0;
         B4=0;
         break;
      case LOCK_input1_2:
         B2=0;
         B3=1;
         B4=0;
         break;
      case LOCK_wait_4:
         B2=0;
         B3=0;
         B4=1;
         break;
      case LOCK_input2_5:
         B2=1;
         B3=0;
         B4=1;
         break;
      case LOCK_unlock_6:
         B0=1;
         B2=0;
         B3=1;
         B4=1;
         break;
      case LOCK_wait_3:
         B2=1;
         B3=1;
         B4=0;
         break;
      default: // ADD default behaviour below
      break;
   } // State actions

}

int main() {

   const unsigned int periodlock = 1000; // 1000 ms default
   TimerSet(periodlock);
   TimerOn();
   
   LOCK_State = -1; // Initial state
   B = 0; // Init outputs

   while(1) {
      TickFct_lock();
      while(!LOCK_Clk);
      LOCK_Clk = 0;
   } // while (1)
} // Main
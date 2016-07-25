/*
 * bevan006_bcare001_lab10_part5.c - 5/22/2016
 *
 * Author : Braddley Carey - bcare001@ucr.edu
 *			bcare001
 *
 * Partner:	Brad Evans - bevan006@ucr.edu
 *
 * Lab Section: 21 
 *
 * Assignment: Lab 10 - Exercise 5
 *
 * I acknowledge all content contained herein, excluding template
 * or example code, is my own original work unless otherwise
 * stated.
 */ 
//Includes
#include <avr/io.h>
#include <avr/interrupt.h>
#include "keypad.h"
#include "io.c"

//Task Global Constants
#define tasksNum  3
#define tasksPeriodGCD 50
#define keypadGCD 100
#define obstacleGCD 100
#define collisionGCD 100

//Game Global Constants
#define PLAYER_TOP 1
#define PLAYER_BOT 17
#define LCD_TOP_LEFT 1
#define LCD_TOP_RIGHT 16
#define LCD_BOT_LEFT 17
#define LCD_BOT_RIGHT 32
#define OFF 0
#define ON 1


//Shared Variables
unsigned char pause = ON, gameover = OFF, player = PLAYER_TOP;
unsigned char obs1=LCD_TOP_RIGHT, obs2=(LCD_BOT_RIGHT - 8);
unsigned char gameover_message[10] = "<GAMEOVER>";
unsigned char pause_message[8] = "<PAUSED>";
unsigned char portBtemp = 0x00;

//Task Structure
typedef struct task {
	int state; // Current state of the task
	unsigned long period; // Rate at which the task should tick
	unsigned long elapsedTime; // Time since task's previous tick
	int (*TickFct)(int); // Function to call for task's tick
} task;
task tasks[tasksNum];

//Timer Functions
volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
void TimerISR();
void TimerOn();
void TimerOff();
ISR(TIMER1_COMPA_vect);
void TimerSet(unsigned long M);

//Function Prototypes
void move_obstacles();
void toggle_pause();
void restart_game();
void move_player(int);
void display_gameover();

//State Machines
enum Keypad_States{keypad_start, keypad_poll} Key_State;
int tickFct_Keypad(int state);
enum Obstacle_States{obs_start, obs_mov, obs_pause, obs_unpause_ready} Obs_State;
int tickFct_Obstacles(int state);
enum Collision_States{col_start, col_check, col_gameover} Col_State;
int tickFct_Collision(int state);

//Main
int main(void){
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0xFF; PORTA = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	DDRC = 0xF0; PORTC = 0x0F;
	
	//Task initializing
	unsigned char i=0;
	
	//Keypad Task
	tasks[i].state = keypad_start;
	tasks[i].period = keypadGCD;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &tickFct_Keypad;
	i++;
		
	//Obstacle Movement
	tasks[i].state = obs_start;
	tasks[i].period = obstacleGCD;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &tickFct_Obstacles;
	i++;
	
	//Collision Detection
	tasks[i].state = col_start;
	tasks[i].period = collisionGCD;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &tickFct_Collision;
	
	//Setup
	TimerSet(tasksPeriodGCD);
	TimerOn();
	LCD_init();
	LCD_DisplayString(1,(unsigned char*)" ");
	LCD_Cursor(1);
	LCD_WriteData('@');
	LCD_Cursor(0);
    while (1){
			
	}
}

//Function Definitions
void toggle_pause(){
	pause = pause ? 0 : 1;
	if(pause){
		for(int i=0; i<8; i++){
			LCD_Cursor(i+5); LCD_WriteData(pause_message[i]);
		}
	}else{
		LCD_DisplayString(1,(unsigned char*)" ");
		LCD_Cursor(player); LCD_WriteData('@');
		move_obstacles();
	}
}
void move_obstacles(){
	LCD_Cursor(obs1); LCD_WriteData(' ');
	LCD_Cursor(obs2); LCD_WriteData(' ');
	if(obs1==LCD_TOP_LEFT){
		obs1 = LCD_TOP_RIGHT;
	}else{
		obs1--;
	}
	if(obs2==LCD_BOT_LEFT){
		obs2 = LCD_BOT_RIGHT;
	}else{
		obs2--;
	}
	LCD_Cursor(obs1); LCD_WriteData('#');
	LCD_Cursor(obs2); LCD_WriteData('#');
	LCD_Cursor(player); LCD_WriteData('@');
	LCD_Cursor(0);
}
void restart_game(){
	LCD_DisplayString(1,(unsigned char*)"");
	player = PLAYER_TOP;
	LCD_Cursor(player); LCD_WriteData('@');
	LCD_Cursor(0);
	obs1=LCD_TOP_RIGHT; obs2=(LCD_BOT_RIGHT - 8);
	gameover = OFF;
	pause = OFF; 	
}
void move_player(int pos){
	if(pos == PLAYER_TOP){
		player = PLAYER_TOP;
		LCD_Cursor(PLAYER_BOT); LCD_WriteData(' ');
		LCD_Cursor(PLAYER_TOP); LCD_WriteData('@');
	}else if(pos==PLAYER_BOT){
		player = PLAYER_BOT;
		LCD_Cursor(PLAYER_TOP); LCD_WriteData(' ');
		LCD_Cursor(PLAYER_BOT); LCD_WriteData('@');	
	}
	LCD_Cursor(0);
}
void display_gameover(){
	for(int i=0; i<10; i++){
		LCD_Cursor(i+3); LCD_WriteData(gameover_message[i]);
	}
}

//State Machine Definitions
int tickFct_Keypad(int state){
	char key = GetKeypadKey();
	switch(state){
		case keypad_start:
			state = keypad_poll;
			break;
		case keypad_poll:
			state = keypad_poll;
			break;
	}
	switch(state){
		case keypad_start:
			break;
		case keypad_poll:
			switch(key){
				case '\0':
					break;
				case '1':
					if( gameover == OFF ){toggle_pause();}
					else if( gameover == ON ){restart_game();}
					break;
				case '4':
					if( gameover == OFF ){move_player(PLAYER_TOP);}
					break;
				case '7':
					if( gameover == OFF ){move_player(PLAYER_BOT);}
					break;
				default:
					break;
			}
			break;
	}
	return state;
}
int tickFct_Obstacles(int state){
	static unsigned char i = 0;
	switch(state){
		case obs_start:
			obs1 = 16; obs2 = 24;
			if(pause&&!gameover){
				state = obs_unpause_ready;
			}else if(!pause&&!gameover){
				state = obs_mov;
			}else{
				state = obs_start;
			}
			break;
		case obs_mov:
			if(pause&&!gameover){
				state = obs_pause;
				i=0;
			}else if(!pause&&!gameover){
				state = obs_mov;
			}else{
				state = obs_start;
			}
			break;
		case obs_pause:
			if( i++ > 5 ){
				state = obs_unpause_ready;
			}else{
				state = obs_pause;
			}
			break;
		case obs_unpause_ready:
			if(pause){
				state = obs_unpause_ready;
			}else{
				state = obs_mov;
			}
			break;
		default:
			state = obs_start;
	}
	switch(state){
		case obs_start:
			break;
		case obs_mov:
			move_obstacles();
			break;
		case obs_pause:
			break;
		case obs_unpause_ready:
			break;
	}
	return state;
}
int tickFct_Collision(int state){
	switch(state){
		case col_start:
			state = col_check;
			break;
		case col_check:
			if( player == obs1 || player == obs2 ){
				state = col_gameover;
				display_gameover();
				gameover = ON;	
			}
			break;
		case col_gameover:
			state = (gameover == ON) ? col_gameover : col_check;
			break;
		default:
			break;	
	}
	switch(state){
		case col_start:
			break;
		case col_check:
			break;
		case col_gameover:
			break;
		default:
			break;
	}
	return state;
}

//Timer Definitions
void TimerISR() {
	unsigned char i;
	for (i = 0; i < tasksNum; ++i) { // Heart of the scheduler code
		if ( tasks[i].elapsedTime >= tasks[i].period ) { // Ready
			tasks[i].state = tasks[i].TickFct(tasks[i].state);
			tasks[i].elapsedTime = 0;
		}
		tasks[i].elapsedTime += tasksPeriodGCD;
	}
	TimerFlag = 1;
}
void TimerOn() {
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1=0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}
void TimerOff() {
	TCCR1B = 0x00;
}
ISR(TIMER1_COMPA_vect) {
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0) {
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}
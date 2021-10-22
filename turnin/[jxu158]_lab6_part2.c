/*	Author: Jerry Xu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 6  Exercise 2
 *	Exercise Description: turn on b0, b1, or b3 LEDS every cycle. only one should be on at a time, always in order of 0, 1, 2
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *https://youtu.be/1-bdlyhu9QI
 */
 #include <avr/io.h>

#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"

enum States{init, blink1, blink2, blink3} state;
unsigned char tempB, tempA;
unsigned char flag = 1;
unsigned char i = 0;
unsigned char arr[] = {0x01, 0x02, 0x04, 0x02};

void tick(){
	switch(state){
		case init:
			tempB = 0;
			i = 0;
			state = blink1;
			break;
		case blink1:
			if(!tempA){
				state = blink2;
			}
			else {state = blink1;}
			break;
		case blink2:
			if(!tempA){
				state = blink2;
			}
			else{
				state = blink3;
			}
			break;
		case blink3:
			if(!tempA){state = blink1;}
			else{state = blink3; }
			break;
	}
	switch(state){
		case init: break;
		case blink1: 
			tempB = arr[i%4];
			i++;
			break;
		default:break;
		
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	state = init;
	
	TimerSet(300);
	TimerOn();
	
    /* Insert your solution below */
    while (1) {
    	PORTA = PINA;
		tempA = ~PINA;
		tick();
		PORTB = tempB;
		while(!TimerFlag);
		TimerFlag = 0;
    }
    return 1;
}

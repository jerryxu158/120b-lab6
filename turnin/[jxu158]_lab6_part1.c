/*	Author: Jerry Xu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 6  Exercise 1
 *	Exercise Description: turn on b0, b1, or b3 LEDS every cycle. only one should be on at a time, always in order of 0, 1, 2
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 * https://youtu.be/eA5YAqBcdH8
 *
 */
 #include <avr/io.h>

#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"

enum States{init, blink1, blink2, blink3} state;
unsigned char tempB = 0;


void tick(){
	switch(state){
		case init:
			tempB = 0;
			state = blink1;
			break;
		case blink1:
			tempB = 0x01;
			state = blink2;
			break;
		case blink2:
			tempB = 0x02;
			state = blink3;
			break;
		case blink3:
			tempB = 0x04;
			state = blink1;
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	state = init;
	
	TimerSet(1000);
	TimerOn();
	
    /* Insert your solution below */
    while (1) {
    	PORTA = PINA;
    	unsigned char tempA = ~PINA;
		tick();
		PORTB = tempB;
		while(!TimerFlag);
		TimerFlag = 0;
    }
    return 1;
}

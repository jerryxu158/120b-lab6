/*	Author: Jerry Xu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 6  Exercise 3
 *	Exercise Description: Buttons are connected to PA0 and PA1. Output for PORTC is initially 7. 
 *	Pressing PA0 increments PORTC if you hold, increment every 1 second instead (stopping at 9). 
 *	Pressing PA1 decrements PORTC if you hold, dec every second instead (stopping at 0). 
 *	If both buttons are depressed (even if not initially simultaneously), PORTC resets to 0.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 * https://youtu.be/ipHH_nKcfqs
 *
 */
#include <avr/io.h>
#include <timer.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Inc, Dec, Reset, Standby} state;
	unsigned char tempA = 0x00; 
	unsigned char tempC = 0x00;
	unsigned char counter = 0;
	
	
void tick(){
	switch(state){
		case Start:
			state = Standby;
			tempC = 0x07;
			counter = 0;
			break;
		case Standby:
			if(tempA == 0x00){state = Standby;}
			else if(tempA == 0x01){
				if(tempC < 9){
					tempC++;
				}
				 state = Inc;
				 counter = 0;
			}
			else if (tempA == 0x02) {
				if(tempC > 0){
					tempC--;
				}			
				state = Dec;
				counter = 0;
			}
			else if(tempA == 0x03){tempC = 0; state = Reset;}
			break;
		case Inc:
			if(tempA == 0x00){state = Standby;}
			else if(tempA == 0x01) {
				state = Inc;
				counter++;
				if(counter%10 == 0){
					if(tempC < 9){
					tempC++;
					}
				}
			}
			else if (tempA == 0x02) {
				if(tempC > 0){
					tempC--;
				}			
				state = Dec;
				counter = 0;
			}
			else if(tempA == 0x03) {tempC = 0; state = Reset;}
			break;
		case Dec:
			if(tempA == 0x00){state = Standby;}
			else if(tempA == 0x01){
				if(tempC < 9){
					tempC++;
				}
				 state = Inc;
			}
			else if(tempA == 0x02) {
				counter++;
				if(counter%10 == 0){
					if(tempC > 0){
					tempC--;
					}
				}	
				state = Dec;
			}

			else if(tempA == 0x03) {tempC = 0; state = Reset;}
			break;
		case Reset:
			if(tempA == 0x03){state = Reset;}
			else if (tempA == 0x02) {
				if(tempC > 0){
					tempC--;
				}			
				state = Dec;
				counter = 0;
			}
			else if(tempA == 0x01){
				if(tempC < 9){
					tempC++;
				}
				 state = Inc;
				 counter = 0;
			}
			else if(!tempA){state = Standby;}
			break;
	}
	switch(state){//no actions in states, only on transitions
		default: break;
	}
}		
int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	TimerSet(100);
	TimerOn();
	
	state = Start;
	
    while (1) {
		PORTA = PINA;
		tempA = PORTA;
		tempA = tempA & 0x03;
		tick();
		PORTB = tempC;
		while(!TimerFlag);
		TimerFlag = 0;
    }
    return 1;
}

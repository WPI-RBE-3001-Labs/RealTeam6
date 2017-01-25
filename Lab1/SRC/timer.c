/*
 * timer.c
 *
 *  Created on: Jan 23, 2017
 *      Author: nbeeten
 */

#include "main.h"
#include <avr/interrupt.h>

unsigned long timerCnt = 0;


ISR(TIMER1_OVF_vect){
	//update the timer count every .455 seconds
	timerCnt++;
	if(timerCnt%11){
		timerCnt++;
	}
}

ISR(TIMER0_COMPA_vect){
	PWMTimerCnt++;
}

unsigned long getTimerCnt(){
	return timerCnt;
}

/**
 * @brief Initializes the specified timer in the specified mode. This
 * header file provides constants for NORMAL operation mode and
 * CTC operation mode, however there are many more modes of operation
 * for the Timers that can be experimented with.
 *
 * @param timer The number of the timer to be initialized (0-2).
 * @param mode The mode to initialize the specified timer in.
 * @param comp Only used in CTC mode. The value that the
 * timer counts to before it triggers an interrupt and resets.
 *
 * @todo Create a switch to initialize different timers
 *
 */
void initTimer(int timer, int mode, unsigned int comp){
	switch(timer){
	case 1:
		TCCR1A = 0b00000000;
		TCCR1B = 0b01000011; //set up for 64 pre-scaler
		TIMSK1 |= (1 << TOIE1); // enable the Overflow Interrupt
		break;

	case 0:
		//set timer 0 to be in CTC mode
		TCCR0A = 0b10000010; //set to CTC mode with the OC0A cleared on Compare Match
		TCCR0B = 0b11000101; //set up for 1024 pre-scaler
		TIMSK0 |= (1 << OCIE0A); // enable the OC0A Interrupt
		OCR0A = comp;//set the number to count to
		break;
	}
}

/**
 * @brief Only used when the specified timer is in CTC mode. Changes
 * the value of the comparison register to the new specified value.
 *
 * @param timer The timer comparison value to change (0-2).
 * @param comp The value to set the comparison register to.
 *
 * @todo Create a function that will set a new compare value for the given timer.
 */
void setCompValue(unsigned char timer, unsigned short int comp){

}

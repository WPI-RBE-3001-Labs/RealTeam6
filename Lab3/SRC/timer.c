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
	//update the timer count every .227 seconds
	timerCnt++;
	if(timerCnt%11){
		timerCnt--;
	}
}

ISR(TIMER0_COMPA_vect){
	PWMTimerCnt++;
}

ISR(TIMER1_COMPA_vect){
	PIDFlag = 1;
	encoderFlag = 1;
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
//void initTimer(int timer, int mode, unsigned int comp){
//	switch(timer){
//	case 1:
//		if(mode == 1){
//			TCCR1A = 0b00000000;
//			TCCR1B = 0b01000011; //set up for 64 pre-scaler
//			TIMSK1 |= (1 << TOIE1); // enable the Overflow Interrupt
//		} else if(mode==0){
//			TCCR1A = 0b10000000; //set to CTC mode with the OC0A cleared on Compare Match
//			TCCR1B = 0b11000011; //set up for 64 pre-scaler
//			TIMSK1 |= (1 << OCIE1A); // enable the OC0A Interrupt
//			OCR1A = comp;//set the number to count to
//		}
//		break;
//
//	case 0:
//		//set timer 0 to be in CTC mode
//		TCCR0A = 0b10000010; //set to CTC mode with the OC0A cleared on Compare Match
//		TCCR0B = 0b11000101; //set up for 1024 pre-scaler
//		TIMSK0 |= (1 << OCIE0A); // enable the OC0A Interrupt
//		OCR0A = comp;//set the number to count to
//		break;
//	}
//}
//
///**
// * @brief Only used when the specified timer is in CTC mode. Changes
// * the value of the comparison register to the new specified value.
// *
// * @param timer The timer comparison value to change (0-2).
// * @param comp The value to set the comparison register to.
// *
// * @todo Create a function that will set a new compare value for the given timer.
// */
//void setCompValue(unsigned char timer, unsigned short int comp){
//
//}

//void initTimer(int timer, int mode, unsigned int comp)
//{
//	switch (timer)
//	{
//	case 0:	//Timer 0
//		TCCR0A = 0b00000000;
//		TCCR0B = 0b00000010;
//		TIMSK0 = 0b00000001;
//		break;
//	case 1: //Timer 1
//		//Clock source, no prescaling for now
//		//to change the prescaling, see page 100
//		TCCR1B &= 0b11111001;
//		TCCR1B |= 0b00000001;
//		switch (mode)
//		{
//		case 0: //Normal mode
//			TCCR1A &= 0b11111100;
//			TCCR1B &= 0b11111011;
//			break;
//		case 1:
//			break;
//		case 2: //CTC mode
////			TCCR1A |= 0b00000001;
////			TCCR1A |= 0b00000010;
//			TCCR1A |= 0b00100000;
//			TCCR1B &= 0b11111011;
//			break;
//		}
//		setCompValue(1, comp);
//		break;
//	case 2:	//Timer 2
//		//Clock source, no prescaling for now
//		//to change the prescaling, see page 100
//		TCCR2B &= 0b11111001;
//		TCCR2B |= 0b00000001;
//
//		switch (mode)
//		{
//		case 0: //Normal mode
//			TCCR2A &= 0b11111100;
//			TCCR2B &= 0b11111011;
//			break;
//		case 1:
//			break;
//		case 2: //CTC mode
//			TCCR2A &= 0b11111110;
//			TCCR2A |= 0b00000010;
//			TCCR2B &= 0b11111011;
//			break;
//		}
//		setCompValue(2, comp);
//		break;
//	}
//}

void initTimer(unsigned char timer, int mode, unsigned char comp){
	cli();
	switch(timer){
	case 0:
		TCCR0A = mode << COM0A0 | mode << WGM00;
		TCCR0B = 5 << CS00;
		TIMSK0 |= 1 << OCIE0A;
		OCR0A = comp;

		if(mode ==1){
			TCCR0A |= 1 << COM0B1;
			TCCR0B |= 1 << WGM02;
			DDRB |= 1 << 4;
		}
		break;

	case 1:
		TCCR1A = mode << COM1A0 | (mode*mode) << WGM10;
		TCCR1B = 5 << CS10 | 1 << WGM12;
		TIMSK1 |= 1 << OCIE1A;
		OCR1AL = comp;

		if(mode == 1){
			TCCR1A |= 1 << COM1B1;
			TCCR1B |= 1 << WGM13;
			DDRD |= 1 << 4;
		}
		break;
	case 2:
		TCCR2A = mode << COM2A0 | mode << WGM20;
		TCCR2B = CS20 << 5;
		TIMSK2 |= OCIE2A << 1;
		OCR2A = comp;

		if(mode == 1){
			TCCR2A |= 1 << COM2B1;
			TCCR2B |= 1 << WGM22;
			DDRD |= 1 << 6;
		}
		break;

	default:
		break;
	}
	sei();

}



void setCompValue(unsigned char timer, unsigned short int comp)
{
	switch (timer)
	{
	case 0:
		OCR0A = comp;
		break;
	case 1:
		OCR1A = comp;
		TIMSK1 = 0b00000010;
		break;
	case 2:
		OCR2A = comp;
		TIMSK2 = 0b00000010;
		break;
	}
}


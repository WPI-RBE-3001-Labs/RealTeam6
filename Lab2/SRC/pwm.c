/*
 * pwm.c
 *
 *  Created on: Feb 5, 2017
 *      Author: nbeeten
 */

#include "main.h"

void initPWMPin(){
	//sets all of PortB to be outputs;
	DDRB &= 0b11111111;
	PORTB &= 0b00000000;
	PINB &= 0b00000000;

}

void generatePWM(unsigned int countTo){
	//if timer reaches countTo
	switch(output){

	case 1:
		if(PWMTimerCnt >= countTo){
			//switch port
			output = 0;
			PWMTimerCnt = 0;
			putCharDebug('p');
			PORTB = 0b00000000;
		}
		break; //end case 1

	case 0:
		if(PWMTimerCnt >= countTo){
			//switch port
			output = 1;
			PWMTimerCnt = 0;
			putCharDebug('s');
			PORTB = 0b00000010;
		}
		break; //end case 0
	}
}

void outputPWM(){
	switch(button){

	case 7:
		//generates a 100Hz signal
		Thigh = 39;
		generatePWM(Thigh);
		break;

	case 6:
		//generates 20Hz signal
		Thigh = 195;
		generatePWM(Thigh);
		break;

	case 5:
		//generates a 1Hz signal
		Thigh = 3906;
		generatePWM(Thigh);
		break;
	}
}

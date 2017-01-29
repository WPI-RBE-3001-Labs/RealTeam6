/*
 * globals.c
 *
 *  Created on: Jan 23, 2017
 *      Author: nbeeten
 */

#include "main.h"

void initGlobals(){

	ADCvalue = 0;
	ADCValAvailable = 0;
	timerCnt = 0;
	PWMTimerCnt = 0;
	timeVal = 0;
	interrupt = 0;
	button = 6;
	output = 0;
	Thigh = 0;

}

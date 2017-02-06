/*
 * globals.c
 *
 *  Created on: Jan 23, 2017
 *      Author: nbeeten
 */

//#include "main.h"
#include "globals.h"
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
	ADC_90 = 600;
	ADC_0 = 228;
	DAC_VALUE_A = 0;
	DAC_VALUE_B = 2047;
	rampFlag = 0;



	//PID
	preErrorH = 0;
	preErrorL = 0;
	errorH = 0;
	errorL = 0;

}

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
	ADCCheckAllChannels = 0;
	PIDFlag = 0;
	encoderOneFlag = 0;
	encoderTwoFlag = 0;
	lastPIDFlag = 0;

	infraOneFlag = 0;
	infraTwoFlag = 0;

	infraOneDataFlag = 0;
	infraTwoDataFlag = 0;

	ADCValues[0] = 0;
	ADCValues[1] = 0;
	ADCValues[2] = 0;
	ADCValues[3] = 0;
	ADCValues[4] = 0;
	ADCValues[5] = 0;
	ADCValues[6] = 0;
	ADCValues[7] = 0;

	pidConstants[0] = 0;
	pidConstants[1] = 0;
	pidConstants[2] = 0;
	pidConstants[3] = 0;
	pidConstants[4] = 0;
	pidConstants[5] = 0;
	pidConstants[6] = 0;
	pidConstants[7] = 0;

	//PID
	preErrorH = 0;
	preErrorL = 0;
	errorH = 0;
	errorL = 0;

	UPPER_LEN = 4.25;
	LOWER_LEN = 6;

	firstAccelRead = 0;

	refReadX = 10;

	encOne = 0;
	encTwo = 0;

	IR1_1 = 100;
	IR1_2 = 100;
	IR1_3 = 100;


	IR2_1 = 100;
	IR2_2 = 100;
	IR2_3 = 100;
}

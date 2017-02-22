/*
 * printStatements.c
 *
 *  Created on: Feb 5, 2017
 *      Author: nbeeten
 */

#include "main.h"

/**
 * @brief prints the time stamp, pot value, pot angle, pot milivolts
 */
void printPotVal(){
	double potAngle = 0;
	double potmV = 0;

	//save all values to things that can be used in a print function
	potAngle = ADCtoAngle(ADCvalue);
	potmV = ADCtoMiliV(ADCvalue);
	timeVal = timerCnt * 0.25;

	printf("%f, %d, %g, %f\n\r", timeVal, ADCvalue, potAngle, potmV);
}

void printPWMVal(){
	double dutyCyc = 0;
	//int freq = 0;
	//int state = 0;

	printf("%f, %d, %d, %d\n\r", dutyCyc, button, Thigh, ADCvalue);
}


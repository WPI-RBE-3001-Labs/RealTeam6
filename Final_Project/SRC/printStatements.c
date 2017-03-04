/*
 * printStatements.c
 *
 *  Created on: Feb 5, 2017
 *      Author: nbeeten
 */

#include "main.h"
#include <math.h>

/**
 * @brief prints the time stamp, pot value, pot angle, pot milivolts
 */
void printPotVal(){
	double potAngle = 0;
	double potmV = 0;

	//save all values to things that can be used in a print function
	potAngle = ADCtoAngleH(ADCvalue);
	potmV = ADCtoMiliV(ADCvalue);
	timeVal = timerCnt * 0.25;

	printf("%f, %d, %g, %f\n\r", timeVal, ADCvalue, potAngle, potmV);
}

void printPWMVal(){
	double dutyCyc = 0;

	printf("%f, %d, %d, %d\n\r", dutyCyc, button, Thigh, ADCvalue);
}

void printPos(){
	int lowerA, upperA,lowerPotVal,upperPotVal;
	float posX, posY;

	lowerPotVal = getADC(LOWARMPOT);
	upperPotVal = getADC(HIGHARMPOT);

	lowerA = ADCtoAngleL(getADC(LOWARMPOT));
	upperA = ADCtoAngleH(getADC(HIGHARMPOT));

	posX = LOWER_LEN*cos(lowerA * M_PI/180) + UPPER_LEN*cos(lowerA * M_PI/180 + upperA* M_PI/180);
	posY = GNDDIST + LOWER_LEN*sin(lowerA * M_PI/180) + UPPER_LEN*sin(lowerA * M_PI/180 + upperA* M_PI/180);

	printf("Current lowPot:  %d,  Current highPot:  %d,  ", lowerPotVal, upperPotVal);
	printf("Current lowA:  %d,  Current highA:  %d,  ", lowerA, upperA);
	printf("Current X:  %f,  Current Y:  %f, \n\r", (double)posX, (double)posY);
}

void printPID(int highTarget, int lowTarget){
	int lowerA, upperA;

	lowerA = ADCtoAngleL(getADC(LOWARMPOT));
	upperA = ADCtoAngleH(getADC(HIGHARMPOT));

	printf(" High Target, %d,", highTarget);
	printf(" High Actual, %d,", upperA);
	printf(" High Error, %d,", actErrorH);
	printf(" Low Target, %d,", lowTarget);
	printf(" Low Actual, %d,", lowerA);
	printf(" Low Error, %d \n\r", actErrorL);

}

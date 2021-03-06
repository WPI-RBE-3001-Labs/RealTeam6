/*
 * main.h
 *
 *  Created on: Jan 21, 2017
 *      Author: nbeeten
 */

#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include "RBELib/RBELib.h"
#include "globals.h"
#include "freerunADC.h"

#define MAX_ADC 1023
#define ADC_CHANNEL 4

double ADCtoAngle(unsigned int potVal);
double ADCtoMiliV(unsigned int potVal);
void printPotVal();
void printPWMVal();
int returnBITS();
void checkButtons();
void initButtons();
void initPWMPin();
void generatePWM(unsigned int countTo);
void outputPWM();


#endif /* SRC_MAIN_H_ */

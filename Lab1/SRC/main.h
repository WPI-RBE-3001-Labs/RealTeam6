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
#define ADC_CHANNEL 3

double ADCtoAngle(unsigned short potVal);
double ADCtoMiliV(unsigned short potVal);
void printPotVal();

#endif /* SRC_MAIN_H_ */

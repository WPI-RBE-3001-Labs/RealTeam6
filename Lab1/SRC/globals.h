/*
 * globals.h
 *
 *  Created on: Jan 23, 2017
 *      Author: nbeeten
 */

#ifndef SRC_GLOBALS_H_
#define SRC_GLOBALS_H_

#include "main.h"

volatile unsigned int ADCvalue;
volatile int ADCValAvailable;
unsigned long timerCnt;
double timeVal;
volatile unsigned long int interrupt;

#endif /* SRC_GLOBALS_H_ */

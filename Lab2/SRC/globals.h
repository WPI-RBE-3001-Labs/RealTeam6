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
unsigned long PWMTimerCnt;
double timeVal;
volatile unsigned long int interrupt;
unsigned int Thigh;
unsigned int DAC_VALUE_A;
unsigned int DAC_VALUE_B;
int output;
int rampFlag;
short button;
double ADC_90, ADC_0;

#endif /* SRC_GLOBALS_H_ */

/*
 * globals.h
 *
 *  Created on: Jan 23, 2017
 *      Author: nbeeten
 */

#ifndef SRC_GLOBALS_H_
#define SRC_GLOBALS_H_

volatile unsigned int ADCvalue;
volatile int ADCValAvailable;
unsigned long timerCnt;
unsigned int lastCnt;
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

//PID
unsigned int errorH;
unsigned int errorL;
unsigned int preErrorH;
unsigned int preErrorL;


#endif /* SRC_GLOBALS_H_ */

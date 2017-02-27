/*
 * globals.h
 *
 *  Created on: Feb 7, 2017
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
int PIDFlag;
int lastPIDFlag;

short button;

short encoderOneFlag;
short encoderTwoFlag;

short infraOneFlag;
short infraTwoFlag;
short infraOneDataFlag;
short infraTwoDataFlag;

char firstAccelRead;

signed int refReadX;
signed int refReadY;
signed int refReadZ;

double ADC_90, ADC_0;

//PID
int errorH;
int errorL;
int preErrorH;
int preErrorL;
int actErrorH;
int actErrorL;

signed long pidH;
signed long pidL;

unsigned short ADCValues[8];

volatile double pidConstants[8];

int ADCCheckAllChannels;

long encOne, encTwo;

#define LOWARMPOT 2
#define HIGHARMPOT 3
#define POT1 5
#define POT2 6
#define POT3 7

#define KP 78
#define KI 1
#define KD 83

double UPPER_LEN;
double LOWER_LEN;

double Dis1;
double Dis2;

double IR1_1;
double IR1_2;
double IR1_3;

double IR2_1;
double IR2_2;
double IR2_3;


void initGlobals();



#endif /* SRC_GLOBALS_H_ */

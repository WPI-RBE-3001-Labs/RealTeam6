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
#include "ADCcalc.h"
#include "currentSense.h"
#include "PIDmotors.h"

#define MAX_ADC 1023
#define ADC_CHANNEL 4
#define DBUS0_CHANNEL 2
#define DBUS1_CHANNEL 3



double ADCtoMiliV(unsigned int potVal);
void printPotVal();
void printPWMVal();
int returnBITS();
void checkButtons();
void initButtons();
void initPWMPin();
void generatePWM(unsigned int countTo);
void outputPWM();
void ramp();
void PIDCntrl();


#endif /* SRC_MAIN_H_ */

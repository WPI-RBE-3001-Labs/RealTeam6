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
#include "printStatements.h"
#include "buttons.h"
#include "pwm.h"

#define MAX_ADC 1023
#define ADC_CHANNEL 4
#define DBUS0_CHANNEL 2
#define DBUS1_CHANNEL 3


int returnBITS();
void ramp();


#endif /* SRC_MAIN_H_ */

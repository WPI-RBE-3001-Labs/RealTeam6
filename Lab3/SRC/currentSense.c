/*
 * currentSense.c
 *
 *  Created on: Feb 5, 2017
 *      Author: nbeeten
 */
#include "currentSense.h"
#include "RBELib/RBELib.h"
void initCurrent(int motor){
	switch (motor){
	case 0: //lower motor
		initADC(0);
	break;

	case 1: //upper motor
		initADC(1);
	break;
	}
}

float readCurrent(int motor){
	unsigned short ADCval = 0;
	float voltageRead;
	switch (motor){
	case 0: //lower motor
		ADCval = getADC(0);
	break;

	case 1: //upper motor
		ADCval = getADC(1);
	break;
	}

	//convert the ADC value to a voltage
	voltageRead = ADCval * 5/((2^10)); //5V range divided by the number of bits
	//shift the out put down by -2.5V to cancel out the  current shift
	voltageRead -= 392;

	//convert to current and divide by gain
	return voltageRead; //output is amps seen across the sense resistor
}


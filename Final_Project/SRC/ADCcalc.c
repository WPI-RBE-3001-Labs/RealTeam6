/*
 * ADCcalc.c
 *
 *  Created on: Jan 29, 2017
 *      Author: jltai
 */

#include "main.h"


/**
 * @brief converts the 10 bit adc value from the pot to the voltage through the pot in mV
 *
 * @param potVal the 10 bit adc output
 * @return the voltage across the potentiometer in mV
 */
double ADCtoMiliV(unsigned int potVal){
	return ((double) potVal)/MAX_ADC*5000;
}

/**
 * @brief converts the 10 bit adc value to the pot angle
 *
 * @param potVal the 10 bit adc output
 * @return the Angle of the potentiometer
 */
double ADCtoAngleH(unsigned int potVal){
	return (((double) potVal)-ADCH_0)*(90/(ADCH_0-ADCH_90));
}

double ADCtoAngleL(unsigned int potVal){
	return (((double) potVal)-ADCL_0)*(90/(ADCL_90-ADCL_0));
}

double ADCtoHundred(unsigned int potVal){
	return ((double) potVal)/MAX_ADC*100;
}

double ADCtoDistance(unsigned int infraVal){
	return (20/(ADCtoMiliV(infraVal)/1000-0.3));
}

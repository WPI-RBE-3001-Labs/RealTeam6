/*
 * main.c
 *
 *  Created on: Jan 20, 2017
 *      Author: nbeeten
 */
#include "main.h"

int main(){
	//start USART at buad rate of 115200
	initRBELib();

	debugUSARTInit(115200);

	//sets the ADC to Free Run Mode on the ADC Channel chosen
	freeRunADC(ADC_CHANNEL);



	//print command to tell what do
	printf("%s", "  Press s to start recording data  ");


	//printf("%h", getADC(4));

	while(getCharDebug() != 0x00){
		//start timer 1 (numbers don't currently mean anything...awk...)
		initTimer(1, 1, 1);
		while(1){
			printPotVal();
		}
	}




}

int returnBITS(){
	return ADMUX;
}

/**
 * @brief converts the 10 bit adc value to the pot angle
 *
 * @param potVal the 10 bit adc output
 * @return the Angle of the potentiometer
 */
double ADCtoAngle(unsigned int potVal){
	return ((double) potVal)/MAX_ADC*270;
}

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
 * @brief prints the time stamp, pot value, pot angle, pot milivolts
 */
void printPotVal(){
	double potAngle = 0;
	double potmV = 0;

	//save all values to things that can be used in a print function
	potAngle = ADCtoAngle(ADCvalue);
	potmV = ADCtoMiliV(ADCvalue);
	timeVal = timerCnt * 0.5;

	printf("%f, %d, %f, %f, %ld\n\r", timeVal, ADCvalue, potAngle, potmV, interrupt);
}

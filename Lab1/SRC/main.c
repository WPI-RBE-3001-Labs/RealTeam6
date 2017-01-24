/*
 * main.c
 *
 *  Created on: Jan 20, 2017
 *      Author: nbeeten
 */
#include "main.h"

int main(){
	//start USART at buad rate of 9600
	debugUSARTInit(9600);

	//sets the ADC to Free Run Mode on the ADC Channel chosen
	freeRunADC(ADC_CHANNEL);
	//print command to tell what to do
	printf("Press s to start recording data");


	while(getCharDebug() != 's'){
		//maybe broken^^ (not sure what USART_Recieve gives)
		//start timer 1 (numbers don't currently mean anything...awk...)
		initTimer(1, 1, 1);
		unsigned long lastTimer = 0;
		unsigned long currentTimer = 0;
		while(1){
			currentTimer = timerCnt;
			if(lastTimer != currentTimer){
				printPotVal();
			}
		}
	}
}

/**
 * @brief converts the 10 bit adc value to the pot angle
 *
 * @param potVal the 10 bit adc output
 * @return the Angle of the potentiometer
 */
double ADCtoAngle(unsigned short potVal){
	return potVal/MAX_ADC*5000;
}

/**
 * @brief converts the 10 bit adc value from the pot to the voltage through the pot in mV
 *
 * @param potVal the 10 bit adc output
 * @return the voltage across the potentiometer in mV
 */
double ADCtoMiliV(unsigned short potVal){
	return potVal/MAX_ADC*270;
}

/**
 * @brief prints the time stamp, pot value, pot angle, pot milivolts
 */
void printPotVal(){
	double potAngle = 0;
	double potmV = 0;
	unsigned long timeVal = 0;

	//save all values to things that can be used in a print function
	potAngle = ADCtoAngle(ADCvalue);
	potmV = ADCtoMiliV(ADCvalue);
	timeVal = timerCnt;

	printf("%f, %d, %f, %f", timeVal*.5, ADCvalue, potAngle, potmV);
}

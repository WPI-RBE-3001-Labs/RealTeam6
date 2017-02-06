/*
 * ADCsetup.h
 *
 *  Created on: Jan 20, 2017
 *      Author: nbeeten
 *      Author: jltai
 *      Author: rpcole
 */

#include "main.h"

/**
 * @brief Initializes the ADC and make one channel active.
 * You can choose to use either interrupts or polling to read
 * the desired channel.
 *
 * @param channel The ADC channel to initialize.
 *
 */
void initADC(int channel){

	//sets the corresponding channel to be an input pin
	DDRA &= ~(1 << channel);

	//Disables the DIDR0 register for the corresponding channel
	//recommended by the data sheet to save power (25.8.6)
	//DIDR0 |= (1 << channel);

	//sets the Vref to be AVCC (5V)
	ADMUX = (0 << 7)|(1 << 6);
	//ADMUX = 1 << 6;

	//Set the ADC prescaler to 128
	ADCSRA = (1 << 2)|(1 << 1)|(1);
	//ADCSRA = 1 << 1;
	//ADCSRA = 1;

	//clears the ADMUX_MUX bits
	ADMUX = (0b11100000|channel);

	//sets the ADMUX_MUX bits to be the corresponding channel
	// ADMUX |= channel;

	//enable the ADC
	ADCSRA |= 1 << 7;

}

/**
 * @brief Disables ADC functionality and clears any saved values (globals).
 *
 * @param channel  The ADC channel to disable.
 *
 * does NOT clear the ADMUX_MUX bits
 *
 */
void clearADC(int channel){
	//disable the ADC
	ADCSRA = 0 << 7;

	//sets the corresponding channel to be an output pin
	DDRA |= (1 << channel);

	//Enables the DIDR0 register for the corresponding channel
	//recommended by the data sheet to save power (25.8.6)
	DIDR0 &= ~(1 << channel);

	//sets the ADCL and ADCH bits to 0
	ADCL = 0;
	ADCH = 0;
}

/**
 * @brief Run a conversion on and get the analog value from one ADC
 * channel if using polling.
 *
 * @param channel  The ADC channel to run a conversion on.
 * @return adcVal The 8-10 bit value returned by the ADC
 * conversion.  The precision depends on your settings and
 * how much accuracy you desire.
 *
 */
unsigned short getADC(int channel){
	unsigned short adcVal = 0;

	//clears the ADMUX.MUX[4:0] (used for channel selection)
	ADMUX &= 0b11100000;

	ADMUX |= channel;

	//start conversion
	ADCSRA = 1 << 6;

	//wait for conversion to end
	while (~(ADCSRA & 0b01000000)){
		adcVal = 0;
	}

	//calculate results of the ADC conversion from ADCL and ADCH (reading ADCL first)
	if(ADMUX & 0b00100000){ //ADC result is left shifted
		adcVal |= (ADCL >> 6);
		adcVal |= (ADCH << 2);
	} else {//ADC result is right shifted
		adcVal |= ADCL;
		adcVal |= (ADCH << 8);
	}

	return adcVal;
}



/**
 * @brief Change the channel the ADC is sampling if using interrupts.
 *
 * @param channel  The ADC channel to switch to.
 *
 * @todo Create a way to switch ADC channels if you are using interrupts.
 */
void changeADC(int channel){



}

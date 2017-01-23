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
	DDRAbits &= ~(1 << channel);

	//Disables the DIDR0 register for the corresponding channel
	//recommended by the data sheet to save power (25.8.6)
	DIDR0bits |= (1 << channel);

	//sets the Vref to be AVCC (5V)
	ADMUXbits._REFS1 = 0;
	ADMUXbits._REFS0 = 1;

	//Set the ADC prescaler to 128
	ADCSRAbits._ADPS2 = 1;
	ADCSRAbits._ADPS1 = 1;
	ADCSRAbits._ADPS0 = 1;

	//enable the ADC
	ADCSRAbits._ADEN = 1;
}

/**
 * @brief Disables ADC functionality and clears any saved values (globals).
 *
 * @param channel  The ADC channel to disable.
 *
 */
void clearADC(int channel){
	//disable the ADC
	ADCSRAbits._ADEN = 0;

	//sets the corresponding channel to be an output pin
	DDRAbits |= (1 << channel);

	//Enables the DIDR0 register for the corresponding channel
	//recommended by the data sheet to save power (25.8.6)
	DIDR0bits &= ~(1 << channel);

	//sets the ADCL and ADCH bits to 0
	ADCLbits = 0;
	ADCHbits = 0;
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
	ADMUXbits &= 0b11100000;

	ADMUXbits |= channel;

	//start conversion
	ADCSRAbits._ADSC = 1;

	//wait for conversion to end
	while (~(ADCSRAbits._ADSC)){
		adcVal = 0;
	}

	//calculate results of the ADC conversion from ADCL and ADCH (reading ADCL first)
	if(ADMUXbits._ADLAR == 1){ //ADC result is left shifted
		adcVal |= (ADCLbits >> 6);
		adcVal |= (ADCHbits >> 6);
	} else {//ADC result is right shifted
		adcVal |= ADCLbits;
		adcVal |= (ADCHbits << 8);
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

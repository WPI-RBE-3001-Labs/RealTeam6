/*
 * freerunADC.c
 *
 *  Created on: Jan 23, 2017
 *      Author: nbeeten
 */
#include "main.h"

unsigned short adcVal = 0;


/**
 * @brief inits the ADC to the given channel and sets the ADC to Free-run Mode with an interrupt firing when a conversion completes.
 */
freeRunADC(int channel){

	//disable the global interrupt while the ADC sets up
	cli();

	//inits the ADC to the given channel
	initADC(channel);

	//sets the ADC_ADTS to be 000 which is free running
	ADCSRB &= 0b11111000;

	//sets ADC_ADIE to 1 which enables interrupts
	ADCSRA |= 0b00001000;

	//starts the first conversion
	ADCSRA |= 0b01000000;

	//enable the global interrupt since we are done
	sei();
}

ISR(ADC_vect){
	//sets the global variable to be the value of the ADC (I think is that variable)
	if(ADMUX & 0b00100000){ //ADC result is left shifted
		ADCvalue |= (ADCL >> 6);
		ADCvalue |= (ADCH << 2);
	} else {//ADC result is right shifted
		ADCvalue = ADC;
	}

	//tell that the ADC has value
	ADCValAvailable = 1;
}

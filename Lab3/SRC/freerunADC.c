/*
 * freerunADC.c
 *
 *  Created on: Jan 23, 2017
 *      Author: nbeeten
 */
#include "main.h"

unsigned int Enable_Interrupts = (1 << ADIE);
unsigned int Conv_Start = (1 << ADSC);
unsigned int initializer = (1 << ADIE)|(1 << ADSC);

/**
 * @brief inits the ADC to the given channel and sets the ADC to Free-run Mode with an interrupt firing when a conversion completes.
 */
void freeRunADC(int channel){

	//disable the global interrupt while the ADC sets up
	cli();

	//inits the ADC to the given channel
	initADC(channel);

	//sets the ADC_ADTS to be 000 which is free running
	ADCSRB = 0b11111000;

	//sets ADC_ADIE to 1 which enables interrupts
	ADCSRA |= 0b10101000;

	//starts the first conversion
	ADCSRA |= 0b01000000;

	//enable the global interrupt since we are done
	sei();
}

ISR(ADC_vect){
	interrupt += 1;

	/*
	 * gets all the values of all the channels of the ADC and stores them in an array
	 * called ADCValues
	 */
	//selects the current channel selected in the ADC
	if(ADCCheckAllChannels == 1){
		int currentChannel = ADMUX & 0b0001111;

		if(currentChannel > 0 && currentChannel < 7){
			if(ADMUX & 0b00100000){ //ADC result is left shifted
				ADCValues[currentChannel - 1] = ((ADCL >> 6)|0b11);
				ADCValues[currentChannel - 1] = (ADCH << 2);
			} else {//ADC result is right shifted
				ADCValues[currentChannel - 1] = ADC;
			}
			//increment the channel to check
			ADMUX++;
		} else if (currentChannel >= 7){
			if(ADMUX & 0b00100000){ //ADC result is left shifted
				ADCValues[currentChannel - 1] = ((ADCL >> 6)|0b11);
				ADCValues[currentChannel - 1] = (ADCH << 2);
			} else {//ADC result is right shifted
				ADCValues[currentChannel - 1] = ADC;
			}
			//reset channel to start again
			ADMUX &= 0b1110000;
		} else { //only other case is zero (or neg but shouldn't get there ever)
			if(ADMUX & 0b00100000){ //ADC result is left shifted
				ADCValues[7] = ((ADCL >> 6)|0b11);
				ADCValues[7] = (ADCH << 2);
			} else {//ADC result is right shifted
				ADCValues[7] = ADC;
			}
			//increment the channel to check
			ADMUX++;
		}
	} else { // just looking at one pot on 4
		//sets the global variable to be the value of the ADC (I think is that variable)
		if(ADMUX & 0b00100000){ //ADC result is left shifted
			ADCvalue = ((ADCL >> 6)|0b11);
			ADCvalue = (ADCH << 2);
		} else {//ADC result is right shifted
			ADCvalue = ADC;
		}
		//tell that the ADC has value
		ADCValAvailable = 1;
	}
}

//@todo set a new isr for timer2 for the later part of the lba at the right frequency,
//where the isr stores adc val to a lgobal array to be printed

/*
 * main.c
 *
 *  Created on: Jan 20, 2017
 *      Author: nbeeten
 */
#include "main.h"

#define PART1 0
#define PART2 1
#define PART3 2

#define MODE PART2

int main(){
	//start USART at buad rate of 115200
	initRBELib();

	debugUSARTInit(115200);

	//sets the ADC to Free Run Mode on the ADC Channel chosen
	freeRunADC(ADC_CHANNEL);

	switch(MODE){

	case PART1:
		//print command to tell user what to do
		printf("%s", "  Press any letter to start recording data  ");

		while(getCharDebug() != 0x00){
			//start timer 1 (numbers don't currently mean anything...awk...)
			initTimer(1, 1, 1);
			while(1){
				//prints pot values needed for part 1
				printPotVal();
			}
		}
		break; //end of case PART1

	case PART2:
		//inits the buttons on PORTB
		initButtons();
		//init PWM ports
		initPWMPin();
		//print command to tell user what to do
		printf("%s", "  Press any letter to start recording data  ");
		while(getCharDebug() != 0x00){
			//start timer 0 at CTC and comp 1
			initTimer(0, 1, 1);
			while(1){
				//checkButtons();
				outputPWM();
				//prints values needed for part 2
				printPWMVal();
			}
		}
		break;//end of case PART2

	case PART3:
		//inits the buttons on PORTB
		initButtons();
		//init PWM ports
		initPWMPin();
		putCharDebug('p');
		//print command to tell user what to do
		printf("%s", "  Press any letter to start recording data  ");
		putCharDebug('p');
		while(getCharDebug() != 0x00){
			putCharDebug('p');
			//start timer 1 (numbers don't currently mean anything...awk...)
			initTimer(0, 1, 1);
			putCharDebug('p');
			while(1){

				//prints pot values needed for part 1
				printPWMVal();
			}
		}
		break;//end of case PART3

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

	printf("%f, %d, %f, %f\n\r", timeVal, ADCvalue, potAngle, potmV);
}

void printPWMVal(){
	double dutyCyc = 0;
	//int freq = 0;
	//int state = 0;

	printf("%f, %d, %d, %d\n\r", dutyCyc, button, Thigh, ADCvalue);
}
/**
 * @brief sets the button global variable to be the button that was pressed.
 *
 * Checks starting at port 7 and works down
 */
void checkButtons(){
	if (PINC & 256){
		button = 7;

	}
	else if(PINC & 128){
		button = 6;

	}
	else if(PINC & 64){
		button = 5;

	}
	else if(PINC & 16){
		button = 4;
	}
	else{
		button = 10;
	}
}

/**
 * @brief inits the buttons on PORTB by setting all of PORTB pins to input
 */
void initButtons(){
	//sets all of PortB to be inputs
	DDRB &= 0b00000000;
}

void initPWMPin(){
	//sets all of PortD to be outputs;
	DDRD &= 0b11111111;
	PORTD &= 0b00000000;
	PIND &= 0b00000000;

}

void generatePWM(unsigned int countTo){
	//if timer reaches countTo
	if((PWMTimerCnt >= Thigh) && output){
		//switch port
		output = 0;
		PWMTimerCnt = 0;
		PORTD = 0;
	} else if((PWMTimerCnt >= Thigh) && ~output){
		//switch port
		output = 1;
		PWMTimerCnt = 0;
		PORTD = 1;
	}
}

void outputPWM(){
	switch(button){

	case 7:
		//generates a 100Hz signal
		Thigh = 39;
		generatePWM(78);
		break;

	case 6:
		//generates 20Hz signal
		Thigh = 195;
		generatePWM(390);
		break;

	case 5:
		//generates a 1Hz signal
		Thigh = 3906;
		generatePWM(7812);
		break;
	}
}


/*
 * main.c
 *
 *  Created on: Jan 20, 2017
 *      Author: nbeeten
 */
#include "main.h"
#include "RBELib/RBELib.h"
//#include "globals.h"

#define PRINT_POT 0
#define TRIANGLE_WAVE 1
#define ARM_DRIVE 2
#define CURRENT_SENSE 3
#define PID_CONTROL 4
#define ARM_POSITION 5

#define MODE TRIANGLE_WAVE

/////BIT MASKS FOR DAC/////
#define WRITE_MODE 0b0000
#define UPDATE_MODE 0b0001
#define ADDRESS_A 0b0001
#define ADDRESS_B 0b0010
#define ADDRESS_ALL 0b1111

int main(){
	//start USART at baud rate of 115200
	initRBELib();
	initGlobals();
	debugUSARTInit(115200);

	//initialize the DACValues
	DAC_VALUE_A = 0;
	DAC_VALUE_B = 4095;
	rampFlag = 0;

	//sets the ADC to Free Run Mode on the ADC Channel chosen
	freeRunADC(DBUS0_CHANNEL);

	switch(MODE){

	case PRINT_POT:
		//print command to tell user what to do
		printf("%s", "  Press any letter to start recording data  ");

		while(getCharDebug() != 0x00){
			//start timer 1 (rest numbers don't currently mean anything...awk...)
			initTimer(1, 1, 1);
			while(1){
				//prints pot values needed for part 1
				printPotVal();
			}
		}
		break; //end of case PRINT_POT

	case TRIANGLE_WAVE:
		//print command to tell user what to do
		printf("%s", "  starting  ");
		////start timer 1 (numbers don't currently mean anything...awk...)
		initTimer(0, 1, 1);
		initSPI();
		while(1){
			ramp();

			setDAC(1, DAC_VALUE_A);

			setDAC(2, DAC_VALUE_B);


		}
		break; //end of case TRIANGLE_WAVE

	case ARM_DRIVE:
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
		break; //end of case ARM_DRIVE

	case CURRENT_SENSE:

		break; //end of case CURRENT_SENSE

	case PID_CONTROL:

		break; //end of case PID_CONTROL

	case ARM_POSITION:

		break; //end of case ARM_POSITION
	}

}

int returnBITS(){
	return ADMUX;
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

	printf("%f, %d, %g, %f\n\r", timeVal, ADCvalue, potAngle, potmV);
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
	//sets all of PortC to be inputs
	DDRC &= 0b00000000;
}

void initPWMPin(){
	//sets all of PortB to be outputs;
	DDRB &= 0b11111111;
	PORTB &= 0b00000000;
	PINB &= 0b00000000;

}

void generatePWM(unsigned int countTo){
	//if timer reaches countTo
	switch(output){

	case 1:
		if(PWMTimerCnt >= countTo){
			//switch port
			output = 0;
			PWMTimerCnt = 0;
			putCharDebug('p');
			PORTB = 0b00000000;
		}
		break; //end case 1

	case 0:
		if(PWMTimerCnt >= countTo){
			//switch port
			output = 1;
			PWMTimerCnt = 0;
			putCharDebug('s');
			PORTB = 0b00000010;
		}
		break; //end case 0
	}
}

void outputPWM(){
	switch(button){

	case 7:
		//generates a 100Hz signal
		Thigh = 39;
		generatePWM(Thigh);
		break;

	case 6:
		//generates 20Hz signal
		Thigh = 195;
		generatePWM(Thigh);
		break;

	case 5:
		//generates a 1Hz signal
		Thigh = 3906;
		generatePWM(Thigh);
		break;
	}
}

void ramp(){
	if((DAC_VALUE_A < 4095) && rampFlag == 0){
		DAC_VALUE_A++ ;
		DAC_VALUE_B-- ;
	} else if ((DAC_VALUE_A >= 4095) && rampFlag == 0){
		DAC_VALUE_A-- ;
		DAC_VALUE_B++ ;
		rampFlag = 1;
	} else if ((DAC_VALUE_A > 0) && rampFlag == 1){
		DAC_VALUE_A-- ;
		DAC_VALUE_B++ ;
	}else if ((DAC_VALUE_A <= 0) && rampFlag == 1){
		DAC_VALUE_A++ ;
		DAC_VALUE_B-- ;
		rampFlag = 0;
	}
}



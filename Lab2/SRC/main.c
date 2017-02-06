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

#define MODE PID_CONTROL




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
	//freeRunADC(DBUS0_CHANNEL);

	//test stuff
	for(int i = 0; i <= 7; i++){
		freeRunADC(i);
	}



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
		initTimer(1, 1, 1);
		initSPI();
		while(1){
			ramp();

			setDAC(1, DAC_VALUE_A);
			setDAC(2, DAC_VALUE_B);
			printf("Value A: %d, Value B: %d\n\r", DAC_VALUE_A, DAC_VALUE_B);

		}
		break; //end of case TRIANGLE_WAVE

	case ARM_DRIVE:
		initTimer(1, 1, 1);
		initSPI();
		while(1){
			driveLink(0, 1);
			_delay_ms(200);
			driveLink(0, 0);
			_delay_ms(200);
			//driveLink(1, 0); // to make sure the other one doesnt move

		}
		break; //end of case ARM_DRIVE

	case CURRENT_SENSE:
		initCurrent(0);
		while(1){
			driveLink(0, 1);
			_delay_ms(200);
			driveLink(0, 0);
			_delay_ms(200);
			printf("Current 0: %f\n\r",(double) readCurrent(0));
		}
		break; //end of case CURRENT_SENSE

	case PID_CONTROL:

		while(1){

			//@todo need to add feedforward to PID, shoudl just be a value added based off of gravity but im not sure how that works
			//maybe we use the current sensor for that could be super wrong

			//the following array values come from the board as they are stored in sequence from the ADC
			//4-7 is analog in from pots
			for(int i = 4; i <= 7; i++){
				pidConstants[i] = ADCtoHundred(ADCValues[i]);
			}
			setConst('H', pidConstants[4], pidConstants[5], pidConstants[6]);
			//3 is higher link *should probably check if i'm wrong here*
			pidH = calcPID('H', 60, ADCtoAngle(ADCValues[3]) );

			if(errorH > 0){
				driveLinkPID(1, 1, pidH);
			}else if (errorH < 0){
				driveLinkPID(1, 0, pidH);
			}

		}

		break; //end of case PID_CONTROL

	case ARM_POSITION:

		break; //end of case ARM_POSITION
	}

} //end of main



int returnBITS(){
	return ADMUX;
}

void ramp(){
	if((DAC_VALUE_A < 4095) && rampFlag == 0){
		DAC_VALUE_A += 40 ;
		DAC_VALUE_B -= 40 ;
	} else if ((DAC_VALUE_A >= 4095) && rampFlag == 0){
		DAC_VALUE_A -= 40 ;
		DAC_VALUE_B += 40 ;
		rampFlag = 1;
	} else if ((DAC_VALUE_A > 0) && rampFlag == 1){
		DAC_VALUE_A -= 40 ;
		DAC_VALUE_B += 40 ;
	}else if ((DAC_VALUE_A <= 0) && rampFlag == 1){
		DAC_VALUE_A += 40 ;
		DAC_VALUE_B -= 40 ;
		rampFlag = 0;
	}
}



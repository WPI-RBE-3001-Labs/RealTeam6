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

#define LINKTARGET 60

/////BIT MASKS FOR DAC/////
#define WRITE_MODE 0b0000
#define UPDATE_MODE 0b0001
#define ADDRESS_A 0b0001
#define ADDRESS_B 0b0010
#define ADDRESS_ALL 0b1111

#define LOWARMPOT 2
#define HIGHARMPOT 3
#define POT1 5
#define POT2 6
#define POT3 7

#define KP 140
#define KI 1
#define KD 1


int main(){
	//start USART at baud rate of 115200
	initRBELib();
	initGlobals();
	debugUSARTInit(115200);

	//initialize the DACValues
	DAC_VALUE_A = 0;
	DAC_VALUE_B = 4095;
	rampFlag = 0;

	//inits the ADC for each Potentiometer
	initADC(POT1);
	initADC(POT2);
	initADC(POT3);

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
		initSPI();
		initCurrent(0);
		while(1){
			driveLink(0, 1);
			printf("Current 0: %f\n\r",(double) readCurrent(0));
			_delay_ms(200);
			driveLink(0, 0);
			printf("Current 0: %f\n\r",(double) readCurrent(0));
			_delay_ms(200);
		}
		break; //end of case CURRENT_SENSE

	case PID_CONTROL:
		initSPI();
		while(1){
			//@todo need to add feedforward to PID, shoudl just be a value added based off of gravity but im not sure how that works
			//maybe we use the current sensor for that could be super wrong

			//the following array values come from the board as they are stored in sequence from the ADC
			//4-7 is analog in from pots
			for(int i = 4; i <= 7; i++){
				pidConstants[i] = ADCtoHundred(getADC(i));
			}
			setConst('H', KP, KI, KD);
			printf("     Target: %d", LINKTARGET);
			printf("     Actual: %f", ADCtoAngle(getADC(HIGHARMPOT)));
			//calc what to send to motor
			pidH = calcPID('H', 60, ADCtoAngle(getADC(HIGHARMPOT)) );

			printf("     Motor Command: %d", pidH);
			printf("     Current: %f\n\r", (double) readCurrent(1));

			driveLinkPIDDir(1, pidH);
		}
		break; //end of case PID_CONTROL

	case ARM_POSITION:
		initSPI();
		initTimer(1,0,1439);

		while(1){
			if (PIDFlag == 1){
				ADCValues[LOWARMPOT] = getADC(LOWARMPOT);
				ADCValues[POT1] = getADC(POT1);
				ADCValues[POT2] = getADC(POT2);
				ADCValues[POT3] = getADC(POT3);

				setConst('L',ADCValues[POT1],ADCValues[POT2],ADCValues[POT3]);
				signed int Lpwr = calcPID('L',75,ADCtoAngle(ADCValues[LOWARMPOT]));

				driveLinkPID(0,Lpwr);
				stopSelect(1);

				printf("Kp: %d, Ki: %d, Kd: %d, Low Arm Pot: %f\n\r", ADCValues[POT1], ADCValues[POT2], ADCValues[POT3], ADCtoAngle(ADCValues[LOWARMPOT]));
				PIDFlag = 0;
			}
		}
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



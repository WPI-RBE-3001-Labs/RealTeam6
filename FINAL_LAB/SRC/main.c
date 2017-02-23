/*
 * main.c
 *
 *  Created on: Jan 20, 2017
 *      Author: nbeeten
 */
#include "main.h"
#include "RBELib/RBELib.h"
#include <math.h>
//#include "globals.h"

#define PRINT_POT 0
#define TRIANGLE_WAVE 1
#define ARM_DRIVE 2
#define CURRENT_SENSE 3
#define PID_CONTROL 4
#define ARM_POSITION 5
#define GO_XY 6
#define ENCODE 7
#define ACCELERATE 8
#define STREAM 9
#define INFRARED 10

#define MODE INFRARED


#define LINKTARGET 90
#define LINKTARGET_2 45


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

			setConst('H', KP, KI, KD);
			printf("     Target, %d,", LINKTARGET);
			printf("     Actual, %f,", ADCtoAngleH(getADC(HIGHARMPOT)));
			//calc what to send to motor
			pidH = calcPID('H', LINKTARGET, ADCtoAngleH(getADC(HIGHARMPOT)) );

			printf("     Motor Command, %ld,", pidH);
			printf("     Current, %f,\n\r", (double) readCurrent(1));

			driveLinkPIDDir(1, pidH);


		}
		break; //end of case PID_CONTROL

	case ARM_POSITION:
		initSPI();
		while(1){
			setConst('L', KP, KI, KD);
			printf("     Target, %d,", LINKTARGET);
			printf("     Actual, %f,", ADCtoAngleL(getADC(LOWARMPOT)));
			//calc what to send to motor
			pidL = calcPID('L', LINKTARGET, ADCtoAngleL(getADC(LOWARMPOT)) );

			printf("     Motor Command, %ld,", pidL);
			printf("     Current, %f,\n\r", (double) readCurrent(0));

			driveLinkPIDDir(0, pidL);
		}
		break; //end of case ARM_POSITION

	case GO_XY:
		initSPI();
		initButtons();
		int switches;
		while(1){
			switches = (PINCbits._P3 << 3) | (PINCbits._P2 << 2) | (PINCbits._P1 << 1) | (PINCbits._P0 << 0);
			setConst('L', KP+80, KI, KD);
			setConst('H', KP+40, KI, KD);
			//printPos();
			printf("Current lowA:  %f,  Current highA:  %f,  ", (double)(ADCtoAngleL(getADC(LOWARMPOT))), (double)ADCtoAngleH(getADC(HIGHARMPOT)));
			printf("switches:  %d  \n\r", switches);
			if(switches == 0){
				driveLinkPID(0, calcPID('L', 42, ADCtoAngleL(getADC(LOWARMPOT))));
				driveLinkPID(1, calcPID('H', -18, ADCtoAngleH(getADC(HIGHARMPOT))));
			} else if(switches == 1){
				driveLinkPID(0, calcPID('L', 32, ADCtoAngleL(getADC(LOWARMPOT))));
				driveLinkPID(1, calcPID('H', -6, ADCtoAngleH(getADC(HIGHARMPOT))));
			} else if(switches == 2){
				driveLinkPID(0, calcPID('L', 26, ADCtoAngleL(getADC(LOWARMPOT))));
				driveLinkPID(1, calcPID('H', -3, ADCtoAngleH(getADC(HIGHARMPOT))));
			} else if(switches == 3){
				driveLinkPID(0, calcPID('L', 14, ADCtoAngleL(getADC(LOWARMPOT))));
				driveLinkPID(1, calcPID('H', 4, ADCtoAngleH(getADC(HIGHARMPOT))));
			} else if(switches == 4){
				driveLinkPID(0, calcPID('L', 17, ADCtoAngleL(getADC(LOWARMPOT))));
				driveLinkPID(1, calcPID('H', 20, ADCtoAngleH(getADC(HIGHARMPOT))));
			} else if(switches == 5){
				driveLinkPID(0, calcPID('L', 17, ADCtoAngleL(getADC(LOWARMPOT))));
				driveLinkPID(1, calcPID('H', 40, ADCtoAngleH(getADC(HIGHARMPOT))));
			} else if(switches == 6){
				driveLinkPID(0, calcPID('L', 14, ADCtoAngleL(getADC(LOWARMPOT))));
				driveLinkPID(1, calcPID('H', 59, ADCtoAngleH(getADC(HIGHARMPOT))));
			} else if(switches == 7){
				driveLinkPID(0, calcPID('L', 27, ADCtoAngleL(getADC(LOWARMPOT))));
				driveLinkPID(1, calcPID('H', 27, ADCtoAngleH(getADC(HIGHARMPOT))));
			} else if(switches == 8){
				driveLinkPID(0, calcPID('L', 37, ADCtoAngleL(getADC(LOWARMPOT))));
				driveLinkPID(1, calcPID('H', 0, ADCtoAngleH(getADC(HIGHARMPOT))));
			}
		}
		break; //end of case GO_XY

	case ENCODE:
		initSPI();
		initEncoders();
		//initButtons();
		initTimer(1, 2, 91);
		stopMotors();
		while(1){
			//driveLinkPIDDir(0, 2047);
			setDAC(2, 2047);
			setDAC(3, 0);
			stopSelect(0);
			calcEncoder(1);
			printf(" Encoder counts: %ld \n\r", encTwo);
			checkButtons();
			if(button == 4){ //+3V
				printf("d");
				setDAC(2, 2047);
				setDAC(3, 0);
				//driveLinkPIDDir(1, 2047);
			} else if(button == 5){ //-3V
				printf("u");
				//setDAC(3, 2047);
				//setDAC(2, 0);
				driveLinkPIDDir(1, -2047);
			} else if(button == 6){ //6V
				printf("C");
				//setDAC(2, 4095);
				//setDAC(3, 0);
				driveLinkPIDDir(1, 4095);
			} else if(button == 7){ //0V
				printf("K");
				setDAC(2, 0);
				setDAC(3, 0);
			}
			_delay_ms(1);
		}
		break;

	case ACCELERATE:
		initSPI();
		initEncoders();
		initButtons();
		initTimer(1, 2, 91);

		while(1){
			printf("Vref %d, Accel x %d\n\r", refReadX, GetAccelerationH48C(0));
		}
		break;

	case STREAM:
		initSPI();
		initEncoders();
		initTimer(1, 2, 91);
		setConst('L', KP+80, KI, KD);
		setConst('H', KP+40, KI, KD);

		while(1){
			//homeArm();
			gotoAngles(90, 0);
			calcEncoder(0);
			calcEncoder(1);
			printf("Low Angle, %f, High Angle, %f, Accel X, %d, Accel Y, %d, Accel Z, %d, EncoderL, %ld, EncoderH, %ld \n\r", ADCtoAngleH(getADC(LOWARMPOT)),
					ADCtoAngleH(getADC(HIGHARMPOT)), GetAccelerationH48C(0), GetAccelerationH48C(2), GetAccelerationH48C(3), encOne, encTwo);

		}
		break;

	case INFRARED:

		initInfra();

		while(1){

			readInfra();
			Dis1 = ADCtoDistance(IR1);
			Dis2 = ADCtoDistance(IR2);
			printf("IR1,  %f,  IR2, %f\n\r", Dis1, Dis2);
		}

		break;
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

void printPos(){
	int lowerA, upperA;
	float posX, posY;

	lowerA = ADCtoAngleL(getADC(LOWARMPOT));
	upperA = ADCtoAngleH(getADC(HIGHARMPOT));

	posX = LOWER_LEN*cos(lowerA * M_PI/180) + UPPER_LEN*sin(lowerA * M_PI/180 + upperA* M_PI/180);
	posY = LOWER_LEN*sin(lowerA * M_PI/180) - UPPER_LEN*cos(lowerA * M_PI/180 + upperA* M_PI/180);
	printf("Current lowA:  %d,  Current highA:  %d,  ", lowerA, upperA);
	printf("Current X:  %f,  Current Y:  %f, \n\r", (double)posX, (double)posY);
}

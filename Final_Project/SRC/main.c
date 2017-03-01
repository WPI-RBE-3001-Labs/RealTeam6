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


#define TRIANGLE_WAVE 1
#define ARM_DRIVE 2
#define CURRENT_SENSE 3
#define PID_CONTROL 4
#define ARM_POSITION 5
#define GO_XY 6
#define STREAM 9
#define INFRARED 10
#define SERVOS 11
#define TEST_BELT 12
#define TEST_ARMXY 13
#define FINAL_RUN 14

#define MODE FINAL_RUN



//define states for FINAL_RUN state machine
#define DETECT_BLOCK 1
#define WAIT_FOR_BLOCK 2
#define GRAB_BLOCK 3
#define WEIGH_BLOCK 4
#define DROP_LIGHT_BLOCK 5
#define DROP_HEAVY_BLOCK 6

int block_pos = -1;

int FINAL_RUN_STATE = DETECT_BLOCK;

//link targets for PID Testing
#define LINKTARGET 60
#define LINKTARGET_2 90


/////BIT MASKS FOR DAC/////
#define WRITE_MODE 0b0000
#define UPDATE_MODE 0b0001
#define ADDRESS_A 0b0001
#define ADDRESS_B 0b0010
#define ADDRESS_ALL 0b1111

//angles
int OFFSET =15;
int LOW_1 =39;
int HIGH_1 =-89;
int LOW_2 =40;
int HIGH_2 =-87;
int LOW_3 =46;
int HIGH_3 =-96;
int LOW_4= 48;
int HIGH_4= -105;
int LOW_5 =49;
int HIGH_5 =-108;

/////current values///
double curLtotal = 0;
double curHtotal = 0;
double curHAverage;
double curLAverage;


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
		initTimer(1, 2, 91);
		while(1){
			//@todo need to add feedforward to PID, shoudl just be a value added based off of gravity but im not sure how that works
			//maybe we use the current sensor for that could be super wrong

			setConst('H', KP-30, KI, KD);
			double ArmAngle = ADCtoAngleH(getADC(HIGHARMPOT));
			printf("     Target, %d,", LINKTARGET);
			printf("     Actual, %f,", ArmAngle);
			//calc what to send to motor
			pidH = calcPID('H', LINKTARGET, ArmAngle);

			printf("     Motor Command, %ld,", pidH);
			printf("     Current, %f,\n\r", (double) readCurrent(1));

			driveLinkPIDDir(1, pidH);

		}
		break; //end of case PID_CONTROL

	case ARM_POSITION:
		initSPI();
		while(1){
			setConst('L', KP, KI, KD);
			printf("     Target, %d,", LINKTARGET_2);
			printf("     Actual, %f,", ADCtoAngleL(getADC(LOWARMPOT)));
			//calc what to send to motor
			pidL = calcPID('L', LINKTARGET_2, ADCtoAngleL(getADC(LOWARMPOT)) );

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
				driveLinkPIDDir(0, calcPID('L', 42, ADCtoAngleL(getADC(LOWARMPOT))));
				driveLinkPIDDir(1, calcPID('H', -18, ADCtoAngleH(getADC(HIGHARMPOT))));
			} else if(switches == 1){
				driveLinkPIDDir(0, calcPID('L', 32, ADCtoAngleL(getADC(LOWARMPOT))));
				driveLinkPIDDir(1, calcPID('H', -6, ADCtoAngleH(getADC(HIGHARMPOT))));
			} else if(switches == 2){
				driveLinkPIDDir(0, calcPID('L', 26, ADCtoAngleL(getADC(LOWARMPOT))));
				driveLinkPIDDir(1, calcPID('H', -3, ADCtoAngleH(getADC(HIGHARMPOT))));
			} else if(switches == 3){
				driveLinkPIDDir(0, calcPID('L', 14, ADCtoAngleL(getADC(LOWARMPOT))));
				driveLinkPIDDir(1, calcPID('H', 4, ADCtoAngleH(getADC(HIGHARMPOT))));
			} else if(switches == 4){
				driveLinkPIDDir(0, calcPID('L', 17, ADCtoAngleL(getADC(LOWARMPOT))));
				driveLinkPIDDir(1, calcPID('H', 20, ADCtoAngleH(getADC(HIGHARMPOT))));
			} else if(switches == 5){
				driveLinkPIDDir(0, calcPID('L', 17, ADCtoAngleL(getADC(LOWARMPOT))));
				driveLinkPIDDir(1, calcPID('H', 40, ADCtoAngleH(getADC(HIGHARMPOT))));
			} else if(switches == 6){
				driveLinkPIDDir(0, calcPID('L', 14, ADCtoAngleL(getADC(LOWARMPOT))));
				driveLinkPIDDir(1, calcPID('H', 59, ADCtoAngleH(getADC(HIGHARMPOT))));
			} else if(switches == 7){
				driveLinkPIDDir(0, calcPID('L', 27, ADCtoAngleL(getADC(LOWARMPOT))));
				driveLinkPIDDir(1, calcPID('H', 27, ADCtoAngleH(getADC(HIGHARMPOT))));
			} else if(switches == 8){
				driveLinkPIDDir(0, calcPID('L', 37, ADCtoAngleL(getADC(LOWARMPOT))));
				driveLinkPIDDir(1, calcPID('H', 0, ADCtoAngleH(getADC(HIGHARMPOT))));
			}
		}
		break; //end of case GO_XY

	case STREAM:
		initSPI();
		initEncoders();
		initTimer(1, 2, 91);
		setConst('L', KP+80, KI, KD);
		setConst('H', KP+40, KI, KD);

		while(1){
			//homeArm();
			gotoAngles(69, -90);
			calcEncoder(0);
			calcEncoder(1);
			printf("Low Angle, %f, High Angle, %f, Accel X, %d, Accel Y, %d, Accel Z, %d, EncoderL, %ld, EncoderH, %ld \n\r", ADCtoAngleL(getADC(LOWARMPOT)),
					ADCtoAngleH(getADC(HIGHARMPOT)), GetAccelerationH48C(0), GetAccelerationH48C(2), GetAccelerationH48C(3), encOne, encTwo);

		}
		break;

	case INFRARED:

		initSPI();
		initInfra();
		initTimer(1, 2, 91);

		while(1){

			readInfra();

			printf("Dis1,  %f,  Dis2, %f\n\r", Dis1, Dis2);
		}

		break; //end of case INFRARED

	case SERVOS:
		while(1){
			int servoCnt = 0;
			while (servoCnt < 255){
				setServo(6, servoCnt);
				servoCnt ++;
				_delay_ms(5);
			}
			while (servoCnt > 0){
				setServo(6, servoCnt);
				servoCnt --;
				_delay_ms(5);
			}
		}
		break;//end of case SERVOS

	case TEST_BELT:
		initTimer(1, 2, 91);
		runBelt();

		while(1){
			storeDistance(1); //Run this first to store last value
			storeDistance(2);
			readInfra(); //then run this to get the new one
			printf("Sensor Value: %d, Averaged Value: %f, Calculated Distance: %f\n\r", IR1, calcInfraAvg(1), calcBeltPos(calcInfraAvg(1)));
			//			if(calcInfraAvg(1) >= 340){
			//				printf("Block in First IR! \n\r");
			//			} else if(calcInfraAvg(2) >= 340){
			//				printf("Block in Second IR! \n\r");
			//			} else {
			//				printf("beep boop. nothing here boss\n\r");
			//			}

		}
		break;//end of case TEST belt

	case TEST_ARMXY:
		//init the SPI for serial communication
		initSPI();


		initTimer(1, 2, 91);

		//init PID Constants
		setConst('L', KP+90, KI, KD);
		setConst('H', KP+90, KI, KD);

		while(1){
			printPos();
			gotoAngles(LOW_2,HIGH_2);
		}

		break; //end of TEST_ARMXY

	case FINAL_RUN:

		initSPI();
		initInfra();
		initTimer(1, 2, 91);

		stopMotors();
		runBelt();

		//set PID constants for this state
		setConst('L', KP+90, KI, KD);
		setConst('H', KP+40, KI, KD);

		while(1){

			switch(FINAL_RUN_STATE){

			case DETECT_BLOCK:
				stopMotors();


				//home the arm in prep for rest of run
				//homePos();

				storeDistance();

				double avg1 = calcInfraAvg(1);
				double avg2 = calcInfraAvg(2);

				printf("IR1,  %f,  IR2, %f\n\r", avg1, avg2);

				if(avg1 <= 16){
					_delay_ms(250);
					storeDistance();
					storeDistance();
					storeDistance();
					storeDistance();
					storeDistance();
					storeDistance();
					Dis1 = calcInfraAvg(1);
					setConst('L', KP+90, KI, KD);
					setConst('H', KP+40, KI, KD);

					printf("distance1 : %f,   ", Dis1);
					if(Dis1 < 14.5){
						printf("Position 1 \n\r");
						block_pos = 1;
						//						gotoAngles(LOW_1+OFFSET, HIGH_1);
					} else if(Dis1 >= 14.5 && Dis1 < 14.9){
						printf("Position 2 \n\r");
						block_pos = 2;
						//						gotoAngles(LOW_2+OFFSET, HIGH_2);
					} else if(Dis1 >= 14.9 && Dis1 < 15.3){
						printf("position 3 \n\r");
						block_pos = 3;
						//						gotoAngles(LOW_3+OFFSET, HIGH_3);
					} else if(Dis1 >= 15.3 && Dis1 < 15.5){
						printf("position 4 \n\r");
						block_pos = 4;
						//						gotoAngles(LOW_4+OFFSET, HIGH_4);
					} else {
						printf("position 5 \n\r");
						block_pos = 5;
					}
					FINAL_RUN_STATE = WAIT_FOR_BLOCK;

				}
				break; //end of DETECT_BLOCK

			case WAIT_FOR_BLOCK:
				openClaw();
				while(calcInfraAvg(2) >= 15){
					storeDistance();
					switch(block_pos){
					case 1:
						gotoAngles(LOW_1+OFFSET, HIGH_1);
						break;
					case 2:
						gotoAngles(LOW_2+OFFSET, HIGH_2);
						break;
					case 3:
						gotoAngles(LOW_3+OFFSET, HIGH_3);
						break;
					case 4:
						gotoAngles(LOW_4+OFFSET, HIGH_4);
						break;
					case 5:
						gotoAngles(LOW_5+OFFSET, HIGH_5);
						break;
					}

				}
				FINAL_RUN_STATE = GRAB_BLOCK;

				break; //end of WAIT_FOR_BLOCK

			case GRAB_BLOCK:
				_delay_ms(1000);
				stopMotors();
				_delay_ms(2200);
				int pseudoTimer = 0;
				while(pseudoTimer != 500){
					//printf("Low Angle, %f, High Angle, %f\n\r", ADCtoAngleH(getADC(LOWARMPOT)), ADCtoAngleH(getADC(HIGHARMPOT)));
					switch(block_pos){
					case 1:
						gotoAngles(LOW_1+5, HIGH_1+5);
						break;
					case 2:
						gotoAngles(LOW_2+5, HIGH_2);
						break;
					case 3:
						gotoAngles(LOW_3-1, HIGH_3);
						break;
					case 4:
						gotoAngles(LOW_4, HIGH_4+1);
						break;
					case 5:
						gotoAngles(LOW_5, HIGH_5);
						break;
					}
					pseudoTimer ++;
				}
				closeClaw();
				stopMotors();
				_delay_ms(500);
				FINAL_RUN_STATE = WEIGH_BLOCK;
				break; //end of GRAB_BLOCK

			case WEIGH_BLOCK:
				;
				pseudoTimer = 0;
				while(pseudoTimer != 500){
					gotoAngles(60, -25.9);

					pseudoTimer ++;
				}
				curLtotal = 0;
				for(int i = 0; i < 20; i++){
					curLtotal += fabs(readCurrent(1));
				}
				curLAverage = (curLtotal)/20;

				printf("current L: %lf \n\r", curLAverage);


				if(curLAverage < 60){
					printf("light block");
					FINAL_RUN_STATE = DROP_LIGHT_BLOCK;
				} else if (curLAverage > 100){
					printf("heavy block");
					FINAL_RUN_STATE = DROP_HEAVY_BLOCK;
				}
				stopMotors();
				break; //end of WEIGH_BLOCK

			case DROP_LIGHT_BLOCK:
				gotoAngles(110, -110);
				break; //end of DROP_LIGHT_BLOCK

			case DROP_HEAVY_BLOCK:
				gotoAngles(0, -10);
				break; //end of DROP_HEAVY_BLOCK

			}//end of FINAL_RUN_STATE switch case

		}

		break; //end of FINAL_RUN
	}
} //end of main


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

void runBelt(){
	setServo(7, -255);//start the belt, a negative value makes it got the right way
}

void openClaw(){
	//TODO find proper value to set that has claw open
	setServo(6, -255);
}

void closeClaw(){
	//TODO find proper value to set that has claw closed
	setServo(6, 255);
}



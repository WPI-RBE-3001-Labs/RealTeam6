/*
 * PIDmotors.C
 *
 *  Created on: Feb 5, 2017
 *      Author: nbeeten
 */

#include "main.h"

/*
 * @brief Stops the selected link from rotating
 * @param link The link you want to set the values for (1 for H or 0 for L).
 */
void stopSelect(int link){

	switch (link){
	case 0: //lower link
		setDAC(0, 0);
		setDAC(1, 0);
		break;

	case 1: //high link
		setDAC(2, 0);
		setDAC(3, 0);

		break;
	}

}
/*
 * @brief homes the arm and resets the encoder
 */
void homeArm(){
	while(1){
		int lowPID, highPID;

		lowPID = calcPID('L', 90, ADCtoAngleL(getADC(LOWARMPOT)));
		driveLinkPIDDir(0, lowPID);

		highPID = calcPID('H', 0, ADCtoAngleH(getADC(HIGHARMPOT)));
		driveLinkPIDDir(1, highPID);

		if(actErrorH <= 3 && actErrorL <= 3 && actErrorH >= -3 && actErrorL >= -3){
			printf("STAHP");
			stopMotors();
			//set the encoder variables to zero
			encOne = 0;
			encTwo = 0;
			return;
		}
		printf("%d, %d ", lowPID, highPID);
		printf("%d, %d\n\r", actErrorL, actErrorH);
	}
}


/*
 * @brief Drives the selected link in the desired direction at the desired speed
 * @param link The link you want to set the values for (1 for H or 0 for L).
 * @param dir The direction you want the link to rotate (0 or 1).
 * @param pwr The the power that you want to drive the motor at.
 */
void driveLinkPID(int link, int pwr){
	int dir = 0;
	if(pwr < 0){
		pwr = pwr * -1;
		dir = 1;
	}
	switch (link){
	case 0: //lower link
		if(dir){
			setDAC(0, 0);
			setDAC(1, pwr);
		} else {
			setDAC(0, pwr);
			setDAC(1, 0);
		}
		break;
	case 1: //high link
		if(dir){
			setDAC(2, pwr);
			setDAC(3, 0);
		} else {
			setDAC(2, 0);
			setDAC(3, pwr);
		}
		break;
	}

}

/*
 * @brief Drives the selected link in the desired direction at the desired speed
 * @param link The link you want to set the values for (1 for H or 0 for L).
 * @param pwr The the power that you want to drive the motor at.
 */
void driveLinkPIDDir(int link,  int pwr){
	switch (link){
	case 0: //lower link
		//printf("    actErrorL: %d", actErrorL);
		if(actErrorL > 0){
			setDAC(0, pwr);
			setDAC(1, 0);
		} else if(actErrorL < 0){
			setDAC(0, 0);
			setDAC(1, pwr);
		}
		break;
	case 1: //high link
		//printf("    actErrorH: %d", actErrorH);
		if( actErrorH > 0){
			setDAC(2, 0);
			setDAC(3, pwr);

		} else if(actErrorH < 0){
			setDAC(2, pwr);
			setDAC(3, 0);
		}
		break;
	}

}

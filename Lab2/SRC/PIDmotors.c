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
			setDAC(0, pwr);
			setDAC(1, 0);
		} else {
			setDAC(0, 0);
			setDAC(1, pwr);
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
 * @param dir The direction you want the link to rotate (0 or 1).
 * @param pwr The the power that you want to drive the motor at.
 */
void driveLinkPIDDir(int link,  int pwr){
	switch (link){
	case 0: //lower link
		if(pwr > 0){
			setDAC(0, pwr);
			setDAC(1, 0);
		} else if(pwr < 0){
			setDAC(0, 0);
			setDAC(1, pwr);
		}
	break;
	case 1: //high link
		if( actErrorH > 0){
			setDAC(2, pwr);
			setDAC(3, 0);
		} else if(actErrorH < 0){
			setDAC(2, 0);
			setDAC(3, pwr);
		}
	break;
	}

}


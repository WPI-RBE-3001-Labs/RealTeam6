/*
 * PID.c
 *
 *  Created on: Feb 4, 2017
 *      Author: nbeeten
 */
#include "RBELib/RBELib.h"
#include "globals.h"


/**
 * @brief Sets the Kp, Ki, and Kd values for 1 link.
 * @details to set the values, use the following style
 * @code pidConst.Kp = 1.3; @endcode
 * @param link The link you want to set the values for (H or L).
 * @param Kp Proportional value.
 * @param Ki Integral value.
 * @param Kd Derivative value.
 *
 * @todo Create a function to the the PID constants for a given link.
 */

pidConst pidConsts;

void setConst(char link, float Kp, float Ki, float Kd){
	if (link == 'H'){
		pidConsts.Kp_H = Kp;
		pidConsts.Ki_H = Ki;
		pidConsts.Kd_H = Kd;
	} else if (link == 'L'){
		pidConsts.Kp_L = Kp;
		pidConsts.Ki_L = Ki;
		pidConsts.Kd_L = Kd;
	}
}

/**
 * @brief Calculate the PID value.
 * @param  link Which link to calculate the error for (Use 'U' and 'L').
 * @param setPoint The desired position of the link.
 * @param actPos The current position of the link.
 *
 * @todo Make a function to calculate the PID value for a link.
 */
signed int calcPID(char link, int setPoint, int actPos){
	int error = setPoint - actPos;
	float pTerm, iTerm, dTerm, ffTerm;

	if(link == 'H'){

		errorH = error + errorH;
		pTerm = pidConsts.Kp_H * error;
		iTerm = pidConsts.Ki_H * errorH;
		dTerm = pidConsts.Kd_H * preErrorH - error;


		preErrorH = error;

	} else {
		errorL= error + errorL;
		pTerm = pidConsts.Kp_L * error;
		iTerm = pidConsts.Ki_L * errorL;
		dTerm = pidConsts.Kd_L * preErrorL - error;


		preErrorL = error;

	}


	return pTerm + iTerm + dTerm ;

}

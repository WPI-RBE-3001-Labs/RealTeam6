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
 * @todo add feed forward
 * @param  link Which link to calculate the error for (Use 'U' and 'L').
 * @param setPoint The desired position of the link.
 * @param actPos The current position of the link.
 *
 */
signed int calcPID(char link, int setPoint, int actPos){


	float pTerm, iTerm, dTerm;

	if(link == 'H'){

		actErrorH = setPoint - actPos; //sets the actual error of the upper link

		errorH = errorH + actErrorH;
		pTerm = pidConsts.Kp_H * actErrorH;
		iTerm = pidConsts.Ki_H/10 * errorH;
		if(iTerm > 50){
			iTerm = 50;
		}
		//iTerm = 0;
		dTerm = pidConsts.Kd_H * (preErrorH - actErrorH);
		//dTerm = 0;

		preErrorH = actErrorH;

	} else {

		actErrorL = setPoint - actPos; //sets the actual error of the upper link

		errorL = errorL + actErrorL;
		pTerm = pidConsts.Kp_L * actErrorL;
		iTerm = pidConsts.Ki_L/10 * errorL;
		if(iTerm > 50){
			iTerm = 50;
		}
		//iTerm = 0;
		dTerm = pidConsts.Kd_L * (preErrorL - actErrorL);
		//dTerm = 0;

		preErrorL = actErrorL;

	}


	return pTerm + iTerm + dTerm ;

}

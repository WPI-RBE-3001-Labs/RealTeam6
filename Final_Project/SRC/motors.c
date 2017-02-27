/*
 * motors.c
 *
 *  Created on: Feb 5, 2017
 *      Author: nbeeten
 */
#include "RBElib/RBELib.h"
#include "main.h"
#include "ADCcalc.h"
#include <math.h>

/**
 * @brief Helper function to stop the motors on the arm.
 *
 */
void stopMotors(){
	setDAC(0, 0);
	setDAC(1, 0);
	setDAC(2, 0);
	setDAC(3, 0);
}

/**
 * @brief Drive the arm to a desired angle
 *
 * @param lowerTheta The desired angle for the lower link.
 * @param upperTheta The desired angle for the upper link.
 *
 */
void gotoAngles(int lowerTheta, int upperTheta){

	driveLinkPIDDir(0, calcPID('L', lowerTheta, ADCtoAngleL(getADC(LOWARMPOT))));

	driveLinkPIDDir(1, calcPID('H', upperTheta, ADCtoAngleH(getADC(HIGHARMPOT))));

}

/**
 * @brief Drive the end effector of the arm to a desired X and Y position in the workspace.
 *
 * @param x The desired x position for the end effector.
 * @param y The desired y position for the end effector.
 *
 * @todo Use kinematic equations to move the end effector to the desired position.
 */
void gotoXY(int x, int y){

	int LTheta, HTheta;

	double x_ref = x;
	double y_ref = y - 4.5;

	HTheta = -(acos(((pow(x_ref,2.0)+pow(y_ref,2.0))-(pow(LOWER_LEN,2.0)+pow(UPPER_LEN,2.0)))/(2.0*LOWER_LEN*UPPER_LEN)) * 180.0 / M_PI);

	LTheta = (atan2(x_ref,y_ref) - acos((pow(x_ref,2.0)+pow(y_ref,2.0)+pow(LOWER_LEN,2.0)-pow(UPPER_LEN,2.0))/(2.0*LOWER_LEN*sqrt(pow(x_ref,2.0)+pow(y_ref,2.0))))) * 180.0 / M_PI;

	printf("Calc Low Angle, %d, Calc High Angle, %d ,", LTheta, HTheta);
	printPos();

	gotoAngles(LTheta, HTheta);

}

/**
 * @brief Drive a link (upper or lower) in a desired direction.
 *
 * @param link Which link to control.
 * @param dir Which way to drive the link.
 *
 */
void driveLink(int link, int dir){
	switch (link){
	case 0: //lower link
		if(dir){
			setDAC(0, 3000);
			setDAC(1, 0);
		} else {
			setDAC(0, 0);
			setDAC(1, 3000);
		}
		break;
	case 1: //high link
		if(dir){
			setDAC(2, 3000);
			setDAC(3, 0);
		} else {
			setDAC(2, 0);
			setDAC(3, 3000);
		}
		break;
	}

}

/**
 * @brief Drive the arm to a "home" position using the potentiometers.  This
 * should be called before using the encoders and just goes to a default position.
 * Once this has been called once, you can initialize/clear the encoders.
 *
 * @todo Drive the arm to a known position using the potentiometers.
 */
void homePos(){

}

/*
 * motors.c
 *
 *  Created on: Feb 5, 2017
 *      Author: nbeeten
 */
#include "RBElib/RBELib.h"
#include "main.h"
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
 * @todo Make a way to drive the links to a desired angle.
 */
void gotoAngles(int lowerTheta, int upperTheta){

	driveLinkPID(0, calcPID('L', lowerTheta, ADCtoAngle(getADC(LOWARMPOT))));
	driveLinkPID(1, calcPID('H', upperTheta, ADCtoAngle(getADC(HIGHARMPOT))));

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

	//https://ashwinnarayan.blogspot.com/2014/07/inverse-kinematics-for-2dof-arm.html
	//for equation

	int LTheta, HTheta;
	HTheta = atan2(sqrt(1-((x^2+y^2-6^2-4.25^2)/(2*6*4.25)) ), ((x^2+y^2-6^2-4.25^2)/(2*6*4.25)));
	int K1 = 6 + 4.25*cos(HTheta);
	int K2 = 4.25*sin(HTheta);
	int lamda = atan2(K1,K2);
	LTheta = atan2(y,x)-lamda;
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

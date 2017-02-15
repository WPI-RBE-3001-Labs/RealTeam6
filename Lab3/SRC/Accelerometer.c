/*
 * Accelerometer.c
 *
 *  Created on: Feb 13, 2017
 *      Author: jltai
 */

#include "main.h"
#include "RBELib/RBELib.h"

void initAccel(){
	DDRD &= 00000000;
	PORTD &= 00000000;



	}


int GetAccelerationH48C ( int __axis ){
	int accelVal = 0;
	if( __axis == 0){



	}else if(__axis == 1){


	}else if(__axis == 2){



	}
 return accelVal;
}

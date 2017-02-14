/*
 * Accelerometer.c
 *
 *  Created on: Feb 13, 2017
 *      Author: jltai
 */

#include "main.h"
#include "RBELib/RBELib.h"

void initAccel(){
	DDRB &= 00000101;
	DDRC &= 01000000;
}


int GetAccelerationH48C ( int __axis ){
	int accelVal = 0;
	if( __axis == 0){

		PINBbits._P5 = 11000;
		accelVal = PINBbits._P6;

	}else if(__axis == 1){

		PINBbits._P5 = 11001;
		accelVal = PINBbits._P6;

	}else if(__axis == 2){

		PINBbits._P5 = 11010;
		accelVal = PINBbits._P6;

	}

}

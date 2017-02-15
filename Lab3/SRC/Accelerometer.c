/*
 * Accelerometer.c
 *
 *  Created on: Feb 13, 2017
 *      Author: jltai
 */

#include "main.h"
#include "RBELib/RBELib.h"
#include "Accelerometer.h"

void initAccel(){
	DDRD &= 00000000;
	//PORTB



	}


int GetAccelerationH48C ( int __axis ){
	cli();

	unsigned int valAccel = 0;

	PORTBbits._P5 = 1;
	PORTBbits._P6 = 1;



 return 1;
}

/*
 * infrared.c
 *
 *  Created on: Feb 22, 2017
 *      Author: jltai
 */


#include "main.h"
#include "infrared.h"


//analog7 and analog6 are PA7 and PA6 respectively
//8 inches distance from sensors to wall
//20.32 cm distance from sensors to wall



void initInfra(){

	initADC(7);
	initADC(6);

}

void readInfra(){

	IR1 = getADC(6);
	IR2 = getADC(7);

}

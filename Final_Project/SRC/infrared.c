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
	if(infraOneFlag || infraTwoFlag){
		IR1 = getADC(6);
		IR2 = getADC(7);
		infraOneFlag = 0;
		infraTwoFlag = 0;
		infraOneDataFlag = 1;
		infraTwoDataFlag = 1;
	}
}

void storeDistance(){
	readInfra();
	if(infraOneDataFlag){
		IR1_3 = IR1_2;
		IR1_2 = IR1_1;
		IR1_1 = ADCtoDistance(IR1);
		infraOneDataFlag = 0;
	}
	if (infraTwoDataFlag){
		IR2_3 = IR2_2;
		IR2_2 = IR2_1;
		IR2_1 = ADCtoDistance(IR2);
		infraTwoDataFlag = 0;
	}
}

double calcInfraAvg(int sensor){
	if (sensor == 1){
		return (IR1_1 + IR1_2 + IR1_3) / 3.0;
	}else if(sensor == 2){
		return (IR2_1 + IR2_2 + IR2_3) / 3.0;
	} else {
		return 100.0;
	}
}

double calcBeltPos(double irVal){

	return (irVal-480) * -.0133; //returns the distance in inches from the edge of the belt
}

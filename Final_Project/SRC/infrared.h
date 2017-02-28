/*
 * infrared.h
 *
 *  Created on: Feb 22, 2017
 *      Author: jltai
 */

#ifndef SRC_INFRARED_H_
#define SRC_INFRARED_H_


int IR1;
int IR2;

void initInfra();
void readInfra();
void storeDistance();
double calcInfraAvg(int sensor);
double calcBeltPos(double irVal);

#endif /* SRC_INFRARED_H_ */

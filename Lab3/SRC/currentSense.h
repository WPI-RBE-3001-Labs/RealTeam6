/*
 * currentSense.h
 *
 *  Created on: Feb 5, 2017
 *      Author: nbeeten
 */

#ifndef SRC_CURRENTSENSE_H_
#define SRC_CURRENTSENSE_H_

//initialize the current sensor associated with the specified motor
void initCurrent(int motor);

//Read from current sensor associated with the motor specified & return converted value

float readCurrent(int motor);

#endif /* SRC_CURRENTSENSE_H_ */

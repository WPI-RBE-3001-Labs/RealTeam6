/*
 * currentSense.h
 *
 *  Created on: Feb 5, 2017
 *      Author: nbeeten
 */

#ifndef SRC_CURRENTSENSE_H_
#define SRC_CURRENTSENSE_H_

/**
 * @brief initialize the current sensor associated with the motor
 *
 * @param motor the motor affiliated with the channel on the current sensor
 *
 */
void initCurrent(int motor);

/**
 * @brief Gets the value from the current sensor associated with the motor
 *
 * @param motor the motor associated with the current sensor
 *
 * @return value the pre amplification and pre shifted current in mA
 */

float readCurrent(int motor);

#endif /* SRC_CURRENTSENSE_H_ */

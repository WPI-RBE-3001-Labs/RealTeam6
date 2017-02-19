/*
 * Accelerometer.h
 *
 *  Created on: Feb 13, 2017
 *      Author: jltai
 */

#ifndef SRC_ACCELEROMETER_H_
#define SRC_ACCELEROMETER_H_
/**
 * @brief gets the accelerometer data for the specified axis
 *
 * @param __axis the axis to pull data from
 *
 * @return accelVal the acceleration read on the specified axis
 *
 */
int GetAccelerationH48C ( int __axis );

#endif /* SRC_ACCELEROMETER_H_ */

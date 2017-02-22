/*
 * ADCcalc.h
 *
 *  Created on: Jan 29, 2017
 *      Author: jltai
 */

#ifndef SRC_ADCCALC_H_
#define SRC_ADCCALC_H_

/**
 * @brief Maps the given ADC value to a value in miliVolts
 *
 * @param potVal the value from the potentiometer to convert
 *
 * @return value the value in miliVolts that corresponds to the given potentiometer measurement
 */
double ADCtoMiliV(unsigned int potVal);
/**
 * @brief Maps the given ADC value to an angle in degrees for the high potentiometer
 *
 * @param potVal the value from the potentiometer to convert
 *
 * @return value the value in degrees that corresponds to the given potentiometer measurement
 */
double ADCtoAngleH(unsigned int potVal);
/**
 * @brief Maps the given ADC value to an angle in degrees for the low potentiometer
 *
 * @param potVal the value from the potentiometer to convert
 *
 * @return value the value in degrees that corresponds to the given potentiometer measurement
 */
double ADCtoAngleL(unsigned int potVal);
/**
 * @brief Maps the given ADC value to a percentage of the full range.
 *
 * @param potVal the value from the potentiometer to convert
 *
 * @return value the value as a percentage that corresponds to the given potentiometer measurement
 */
double ADCtoHundred(unsigned int potVal);

#endif /* SRC_ADCCALC_H_ */

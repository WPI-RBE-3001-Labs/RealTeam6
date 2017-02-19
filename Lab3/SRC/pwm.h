/*
 * pwm.h
 *
 *  Created on: Feb 5, 2017
 *      Author: nbeeten
 */

#ifndef SRC_PWM_H_
#define SRC_PWM_H_
/**
 * @brief Initializes port B to be PWM enabled
 */
void initPWMPin();
/**
 * @brief generates a PWM signal with a specified count to
 *
 * @param countTo the value used to generate the PWM wave
 */
void generatePWM(unsigned int countTo);
/**
 * @brief Toggles the PWM waveform based on the generatePWM function
 */
void outputPWM();

#endif /* SRC_PWM_H_ */

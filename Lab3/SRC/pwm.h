/*
 * pwm.h
 *
 *  Created on: Feb 5, 2017
 *      Author: nbeeten
 */

#ifndef SRC_PWM_H_
#define SRC_PWM_H_

void initPWMPin();
void generatePWM(unsigned int countTo);
void outputPWM();

#endif /* SRC_PWM_H_ */

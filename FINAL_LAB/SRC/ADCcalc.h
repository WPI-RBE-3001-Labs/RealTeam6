/*
 * ADCcalc.h
 *
 *  Created on: Jan 29, 2017
 *      Author: jltai
 */

#ifndef SRC_ADCCALC_H_
#define SRC_ADCCALC_H_


double ADCtoMiliV(unsigned int potVal);
double ADCtoAngleH(unsigned int potVal);
double ADCtoAngleL(unsigned int potVal);
double ADCtoHundred(unsigned int potVal);
double ADCtoDistance(unsigned int infraVal);

#endif /* SRC_ADCCALC_H_ */

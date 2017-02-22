/*
 * freerunADC.h
 *
 *  Created on: Jan 23, 2017
 *      Author: nbeeten
 */

#ifndef SRC_FREERUNADC_H_
#define SRC_FREERUNADC_H_

/**
 * @brief inits the ADC to the given channel and sets the ADC to Free-run Mode with an interrupt firing when a conversion completes.
 *
 * @param channel the channel to initialize
 */
void freeRunADC(int channel);

#endif /* SRC_FREERUNADC_H_ */

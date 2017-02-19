/*
 * buttons.h
 *
 *  Created on: Feb 5, 2017
 *      Author: nbeeten
 */

#ifndef SRC_BUTTONS_H_
#define SRC_BUTTONS_H_

/**
 * @brief Initializes the buttons to be on port C
 *
 */
void initButtons();
/**
 * @brief Updates the global variable "button" with the status of all the the pins on port C
 */
void checkButtons();

#endif /* SRC_BUTTONS_H_ */

/*
 * ports.c
 *
 *  Created on: Jan 21, 2017
 *      Author: nbeeten
 */

#include "RBELib/RBELib.h"

/**
 * @brief Sets the direction (Input/Output) of the specified pins.
 *
 * @param port Port to set (A/B/C/D).
 * @param dir The direction of the pins going to be set (either 1 or 0).
 * @param numPins The number of pins that you are setting the
 * direction of.
 * @param ... Pins one after another
 *
 * @todo Create a way to set a port's pins to inputs or outputs.
 */
void setPinsDir(char port, int dir, char numPins, ...){
	if(port == 'a' || port == 'A'){

	}
}

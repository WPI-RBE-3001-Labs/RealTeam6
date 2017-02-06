/*
 * buttons.c
 *
 *  Created on: Feb 5, 2017
 *      Author: nbeeten
 */

#include "main.h"

/**
 * @brief inits the buttons on PORTB by setting all of PORTB pins to input
 */
void initButtons(){
	//sets all of PortC to be inputs
	DDRC &= 0b00000000;
}

/**
 * @brief sets the button global variable to be the button that was pressed.
 *
 * Checks starting at port 7 and works down
 */
void checkButtons(){
	if (PINC & 256){
		button = 7;

	}
	else if(PINC & 128){
		button = 6;

	}
	else if(PINC & 64){
		button = 5;

	}
	else if(PINC & 16){
		button = 4;
	}
	else{
		button = 10;
	}
}

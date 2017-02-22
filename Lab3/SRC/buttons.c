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
//	printf("button7:  %d  ", PINCbits._P7);
//	printf("button6:  %d  ", PINCbits._P6);
//	printf("button5:  %d  ", PINCbits._P5);
//	printf("button4:  %d  ", PINCbits._P4);
	if (!PINCbits._P7){
		button = 7;

	}
	else if(!PINCbits._P6){
		button = 6;

	}
	else if(!PINCbits._P5){
		button = 5;

	}
	else if(!PINCbits._P4){
		button = 4;
	}
	else{
		button = 0;
	}
}

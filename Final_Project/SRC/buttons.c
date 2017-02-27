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
	DDRD &= 0b00000000;
	PORTD |= 0b11110000;
}

/**
 * @brief sets the button global variable to be the button that was pressed.
 *
 * Checks starting at port 7 and works down
 */
void checkButtons(){
	//printf("button:  %d  \n\r", PINA);
//	printf("button6:  %d  ", PINAbits._P6);
//	printf("button5:  %d  ", PINAbits._P5);
//	printf("button4:  %d  ", PINAbits._P4);
	if (!PINDbits._P7){
		button = 7;

	}
	else if(!PINDbits._P6){
		button = 6;

	}
	else if(!PINDbits._P5){
		button = 5;

	}
	else if(!PINDbits._P4){
		button = 4;
	}
	else{
		button = 0;
	}
}

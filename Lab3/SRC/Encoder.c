/*
 * Encoder.c
 *
 *  Created on: Feb 13, 2017
 *      Author: jltai
 */

#include "main.h"
#include "RBELib/RBELib.h"

void initEncoder(char pos){

	genericSPIInit();

	//set SS to output
	DDRC |= pos == 'H' ? (1 << 5) : (1 << 4);
	//set SS high
	PORTC |= pos == 'H' ? (1 << 5) : (1 << 4);


	//clears the cntr register
	PORTC &= pos == 'H' ? ~(1 << 5) : ~(1 << 4);
	spiTransceive(CLR_CNTR);
	PORTC |= pos == 'H' ? (1 << 5) : (1 << 4);

	PORTC &= pos == 'H' ? ~(1 << 5) : ~(1 << 4);
	spiTransceive(WRITE_MDR0);
	spiTransceive(FOUR_QUADRATURE_COUNT|FREE_RUNNING|DISABLE_INDEX|ASYNCHRONOUS_INDEX|CLK_DIV_FACTOR1);
	PORTC |= pos == 'H' ? (1 << 5) : (1 << 4);
	PORTC &= pos == 'H' ? ~(1 << 5) : ~(1 << 4);
	spiTransceive(WRITE_MDR1);
	spiTransceive(NO_FLAGS|CNTR2_BYTE|ENABLE_CNT);
	PORTC |= pos == 'H' ? (1 << 5) : (1 << 4);
}


void initEncoders(){

	initEncoder('H');
	initEncoder('L');

}
int EncoderCounts( int __chan ){
	int encValue = 0;
	if(__chan == 0){
		//low link
		encValue = PINCbits._P5;
		return encValue;
	} else if(__chan == 1){
		//high link
		encValue = PINCbits._P4;
		return encValue;
	} else {
		return -1;
	}

}

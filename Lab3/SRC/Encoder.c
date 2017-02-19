/*
 * Encoder.c
 *
 *  Created on: Feb 13, 2017
 *      Author: jltai
 */

#include "main.h"
#include "RBELib/RBELib.h"

void initEncoder(char pos){
	//dont forget to init SPI
	//low encoder is dsub0 and high encoder is dsub1

	switch(pos){

	case 'H':
		DDRC |= (1 << 5);
		ENCODER_SS_1 = 0;
		spiTransceive(CLR_CNTR);
		ENCODER_SS_1 = 1;

		ENCODER_SS_1 = 0;
		spiTransceive(WRITE_MDR0);
		spiTransceive(FOUR_QUADRATURE_COUNT|FREE_RUNNING|DISABLE_INDEX);
		ENCODER_SS_1 = 1;

		ENCODER_SS_1 = 0;
		spiTransceive(WRITE_MDR1);
		spiTransceive(NO_FLAGS|CNTR2_BYTE|ENABLE_CNT);
		ENCODER_SS_1 = 1;
		break;

	case 'L':
		DDRC |= (1 << 4);
		ENCODER_SS_0 = 0;
		spiTransceive(CLR_CNTR);
		ENCODER_SS_0 = 1;

		ENCODER_SS_0 = 0;
		spiTransceive(WRITE_MDR0);
		spiTransceive(FOUR_QUADRATURE_COUNT|FREE_RUNNING|DISABLE_INDEX);
		ENCODER_SS_0 = 1;

		ENCODER_SS_0 = 0;
		spiTransceive(WRITE_MDR1);
		spiTransceive(NO_FLAGS|CNTR2_BYTE|ENABLE_CNT);
		ENCODER_SS_0 = 1;
		break;

	}




	//spiTransceive(0x20|0x00);
}

/**
 * @brief Initializes both of the encoders
 *
 */
void initEncoders(){

	initEncoder('H');
	initEncoder('L');

}

long EncoderCounts( char __chan ){
	long encValue = 0;
	long one, two, three, four;
	if (__chan != 'H' && __chan != 'L') {
		return -1; //Invalid channel
	}
	switch(__chan){

	case 'H':

		ENCODER_SS_1 = 0;
		spiTransceive(READ_CNTR);
		one = (long)spiTransceive(0) << 24;
		two = (long)spiTransceive(0) << 16;
		three = (long)spiTransceive(0) << 8;
		four = (long)spiTransceive(0) << 0;
		ENCODER_SS_1 = 1;
		printf(" %ld -- %ld --- %ld ----%ld",one, two, three, four);
		break;

	case 'L':
		ENCODER_SS_0 = 0;
		spiTransceive(READ_CNTR);
		one = (long)spiTransceive(0) << 24;
		two = (long)spiTransceive(0) << 16;
		three = (long)spiTransceive(0) << 8;
		four = (long)spiTransceive(0) << 0;
		ENCODER_SS_0 = 1;
		printf(" %ld -- %ld --- %ld ----%ld",one, two, three, four);
		break;


	}

	return encValue;
}

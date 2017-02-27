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
		DDRC |= (1 << 4);
		ENCODER_SS_1 = 0;
		spiTransceive(CLR_CNTR);
		ENCODER_SS_1 = 1;
		_delay_ms(1);
		ENCODER_SS_1 = 0;
		spiTransceive(WRITE_MDR0);
		spiTransceive(FOUR_QUADRATURE_COUNT|FREE_RUNNING|DISABLE_INDEX);
		ENCODER_SS_1 = 1;
		_delay_ms(1);
		ENCODER_SS_1 = 0;
		spiTransceive(WRITE_MDR1);
		spiTransceive(NO_FLAGS|CNTR2_BYTE|ENABLE_CNT);
		ENCODER_SS_1 = 1;
		break;

	case 'L':
		DDRC |= (1 << 5);
		ENCODER_SS_0 = 0;
		spiTransceive(CLR_CNTR);
		ENCODER_SS_0 = 1;
		_delay_ms(1);
		ENCODER_SS_0 = 0;
		spiTransceive(WRITE_MDR0);
		spiTransceive(FOUR_QUADRATURE_COUNT|FREE_RUNNING|DISABLE_INDEX);
		ENCODER_SS_0 = 1;
		_delay_ms(1);
		ENCODER_SS_0 = 0;
		spiTransceive(WRITE_MDR1);
		spiTransceive(NO_FLAGS|CNTR2_BYTE|ENABLE_CNT);
		ENCODER_SS_0 = 1;
		break;

	}




	//spiTransceive(0x20|0x00);
}


void initEncoders(){

	initEncoder('H');
	initEncoder('L');

}

int EncoderCounts( char __chan ){

	long one, two;
	one = 0;
	two = 0;

	if (__chan != 'H' && __chan != 'L') {
		return 0; //Invalid channel
	}
	switch(__chan){

	case 'H':
		ENCODER_SS_1 = 0;
		spiTransceive(READ_CNTR);

		one = spiTransceive(0) << 8;
		two = spiTransceive(0);
		ENCODER_SS_1 = 1;
		_delay_ms(1);
		ENCODER_SS_1 = 0;
		spiTransceive(CLR_CNTR);
		ENCODER_SS_1 = 1;
		break;

	case 'L':
		ENCODER_SS_0 = 0;
		spiTransceive(READ_CNTR);

		one = spiTransceive(0) << 8;
		two = spiTransceive(0);
		ENCODER_SS_0 = 1;
		_delay_ms(1);
		ENCODER_SS_0 = 0;
		spiTransceive(CLR_CNTR);
		ENCODER_SS_0 = 1;
		break;


	}

	return (one|two);
}

void calcEncoder(int link){
	switch(link){
	case 0://low link
		if(encoderOneFlag){
			encOne += EncoderCounts('L');
			encoderOneFlag = 0;
			PIDFlag = 0;
		}
		break;

	case 1://high link
		if(encoderTwoFlag){
			encTwo += EncoderCounts('H');
			encoderTwoFlag = 0;
			PIDFlag = 0;
		}
		break;
	}
}

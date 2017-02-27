/*
 * Accelerometer.c
 *
 *  Created on: Feb 13, 2017
 *      Author: jltai
 */

#include "main.h"
#include "RBELib/RBELib.h"
#include "Accelerometer.h"



int GetAccelerationH48C ( int __axis ){
	//this might have to be switched to 1 but we rollin with it for now
	DDRC &= (0<<2);

	if(firstAccelRead == 0){
		refReadX = 0;
		//chip select
		PORTCbits._P2 = 0;
		_delay_ms(1);
		PORTCbits._P2 = 1;
		_delay_ms(1);
		PORTCbits._P2 = 0;
		_delay_ms(1);
		spiTransceive(((1<<4)|(1<<3)|__axis)<<2);  //x 00001110  00111000

		refReadX = spiTransceive(0x00) << 4;
		refReadX |= spiTransceive(0x00) >> 4;

		PORTCbits._P2 = 1;

		firstAccelRead = 1;

	}

	unsigned int reading = 0;

	switch (__axis){
	case 0: //x
		PORTCbits._P2 = 0;
		_delay_ms(1);
		PORTCbits._P2 = 1;
		_delay_ms(1);
		PORTCbits._P2 = 0;
		_delay_ms(1);
		spiTransceive(((1<<4)|(1<<3)|__axis)<<2);  //x 00001110  00111000
		reading = (spiTransceive(0x00) << 4);
		reading |= (spiTransceive(0x00) >> 4);
		PORTCbits._P2 = 1;
		return(reading-refReadX);
		break;

	case 1: //y
		PORTCbits._P2 = 0;
		_delay_ms(1);
		PORTCbits._P2 = 1;
		_delay_ms(1);
		PORTCbits._P2 = 0;
		_delay_ms(1);
		spiTransceive(((1<<4)|(1<<3)|__axis)<<2);  //x 00001110  00111000
		reading = (spiTransceive(0x00) << 4);
		reading |= (spiTransceive(0x00) >> 4);
		PORTCbits._P2 = 1;
		return(reading-refReadX);
		break;

	case 2: //z
		PORTCbits._P2 = 0;
		_delay_ms(1);
		PORTCbits._P2 = 1;
		_delay_ms(1);
		PORTCbits._P2 = 0;
		_delay_ms(1);
		spiTransceive(((1<<4)|(1<<3)|__axis)<<2);  //x 00001110  00111000
		reading = (spiTransceive(0x00) << 4);
		reading |= (spiTransceive(0x00) >> 4);
		PORTCbits._P2 = 1;
		return(reading-refReadX);
		break;
	}
	return -1;

}

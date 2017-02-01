/*
 * SPI.c
 *
 *  Created on: Jan 29, 2017
 *      Author: jltai
 */

#include "main.h"

/**
 * @brief Initializes the SPI bus for communication with all of your
 * SPI devices.
 *
 * @todo Create the function that will allow you to initialize the SPI
 * in a mode compatible with all devices.  Do not forget to deassert all
 * of your SS lines!
 */
void initSPI(){
	/* Set MOSI and SCK output, all others input */
	DDRB = (1<<DDB6)|(1<<DDB7);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

/**
 * @brief Send and receive a byte out of the MOSI line.
 *
 * Please note that even if you do not want to receive any data back
 * from a SPI device, the SPI standard requires you still receive something
 * back even if it is junk data.
 *
 * @param data The byte to send down the SPI bus.
 * @return value The byte shifted in during transmit
 *
 * @todo Make a function that will send a byte of data through the SPI
 * and return whatever was sent back.
 */
unsigned char spiTransceive(BYTE data){
	/* Start transmission */
	///////////READ/////////
	BYTE dataIn = NULL;
	while(!(SPSR & (1<<SPIF)))
		;
	dataIn = SPDR;
	///////////WRITE////////
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)))
			;
	return dataIn;
}



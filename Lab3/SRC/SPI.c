/*
 * SPI.c
 *
 *  Created on: Jan 29, 2017
 *      Author: jltai
 */

#include "main.h"
#include "RBELib/RBELib.h"


/**
 * @brief Initializes the SPI bus for communication with all of your
 * SPI devices.
 *
 * @todo Create the function that will allow you to initialize the SPI
 * in a mode compatible with all devices.  Do not forget to deassert all
 * of your SS lines!
 */
void initSPI(){
	PRR = 0;

	DDRB |= (1 << DDB5) | (1 << DDB7) | (1 << DDB4); //MOSI SCK SS enable

	DDRD |= (1 << DDD4); //sets D4 as output

	PORTD |= (1 << PD4);//SS high to deselect

	DDRB &= ~(1 << DDB6);//MISO enable

	//DDRC |= (1 << DDC4) | ( 1<< DDC5);

	SPCR |= (1 << SPE) |  (1<<MSTR) | (1 << SPR1) | (1 << SPR0); // Enable SPI, set as master, set SCK freq, oscillation frequency/128

	SPSR &= ~(1 << SPI2X);


//	spiTransceive(0b01101111);
//	spiTransceive(0);
//	spiTransceive(0);
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
 */
unsigned char spiTransceive(BYTE data){

	/* Start transmission */
	///////////WRITE////////
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF))){
	//printf( "%s\n\r", "     STUUCCKKK   ");
	}
	///////////READ/////////
	unsigned char dataIn = 0;
	dataIn = SPDR;
	//printf( "%s\n\r", "     OUT   ");
	return dataIn;
}


